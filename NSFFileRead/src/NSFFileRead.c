/*
 ============================================================================
 Name        : NSFFileRead.c
 Author      : Looke
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  short x,y;
} XPoint;


typedef struct
{
  struct pointstr *nextp;
  XPoint v;
} pointstr;

typedef struct
{
	pointstr ** polyHeaderList;
	int length;
} 	pointstr_linklist;

int countRowNumber(FILE* pFile)
{
	char buf;
    int rowNum = 0;

    //int hasNumber = 0;

    while(1)
    {
    	if(fread(&buf,sizeof(char),1,pFile)!=1)
    	{
    		break;
    	}
    	switch (buf)
    	{
    		//换行符
    		case 10:
    		{
    			//if(hasNumber)
    			//{
    				rowNum++;
    			//}
    			//hasNumber = 0;
    			break;
    		}
    		//数字
    		case 48:
    		case 49:
    		case 50:
    		case 51:
    		case 52:
    		case 53:
    		case 54:
    		case 55:
    		case 56:
    		case 57:
    		{
    			//hasNumber = 1;
    			break;
    		}
    	}
    }
    return rowNum;
}

void initRowSize(FILE* pFile, char** pRowPointers, int* pRowPointerSize, int rowNum)
{
	char buf;
    int rowCharNum = 0;
    char** pCurrent_RowPointers = pRowPointers;
    int* pCurrent_RowPointerSize = pRowPointerSize;

    //初始化每行的数据长度
    //int hasNumber = 0;
    rewind(pFile);
    while(1)
    {
    	if(fread(&buf,sizeof(char),1,pFile)!=1)
    	{
    		break;
    	}
    	switch (buf)
    	{
    		//换行符
    		case 10:
    		{
    			//对于有数据的行，进行数据收集
    			//if(hasNumber)
    			//{
    				*pCurrent_RowPointers = malloc(sizeof(char) * rowCharNum);
    				*pCurrent_RowPointerSize = rowCharNum;

    				pCurrent_RowPointers++;
    				pCurrent_RowPointerSize++;
    				//rowIndex++;
    			//}
				rowCharNum = 0;
				//hasNumber = 0;
    			break;
    		}
    		//数字
    		case 48:
    		case 49:
    		case 50:
    		case 51:
    		case 52:
    		case 53:
    		case 54:
    		case 55:
    		case 56:
    		case 57:
    		{
    			//hasNumber = 1;
    			rowCharNum++;
    			break;
    		}
    		default:
    		{
    			rowCharNum++;
    			break;
    		}
    	}
    }
}

void initRowContent(FILE* pFile, char** pRowPointers, int* pRowPointerSize, int rowNum)
{
	char buf;
    //int rowCharNum = 0;

    char** pCurrent_RowPointers = pRowPointers;
    char* pCurrent_RowContentIndex = *pCurrent_RowPointers;
    int* pCurrent_RowPointerSize = pRowPointerSize;

    int rowContentIndex = 0;
    //初始化每行的数据长度
    //int hasNumber = 0;
    while(1)
    {
    	if(fread(&buf,sizeof(char),1,pFile)!=1)
    	{
    		break;
    	}
    	switch (buf)
    	{
    		//换行符
    		case 10:
    		{
    			pCurrent_RowPointers++;
    			pCurrent_RowContentIndex = *pCurrent_RowPointers;

    			pCurrent_RowPointerSize++;

    			rowContentIndex = 0;
    			break;
    		}

    		default:
    		{
    			char* pChar = pCurrent_RowContentIndex + rowContentIndex;
    			*pChar = buf;
    			rowContentIndex++;

    			break;
    		}
    	}
    }
}

int isDataRow(char* p_rowPointer, int charSize)
{
	//需要跳过前面n个字符，判断是否属于保存数据的行
	int charToSkip = 9;

	char temp;
	for(int j=0;j<charSize; j++)
	{
		temp = *(p_rowPointer+j);

		//首字符不是空格的一定不是数据行
		if(0 ==j && temp != 32)
		{
			return 0;
		}

		//跳过前面的n个字符
		if(j < charToSkip)
		{
			continue;
		}

		//跳过前面的n+1个字符是数字就为数据行
		if(temp >= 48 && temp <= 57)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int countDataRowNumber(char** p_rowPointers, int* p_rowPointerSize, int rowNum)
{
	int dataRowNumber = 0;
	char* p_CurrentRowPointer = *p_rowPointers;

	for(int i=0; i<rowNum; i++)
	{
		p_CurrentRowPointer = *(p_rowPointers+i);
		int charSize = *(p_rowPointerSize+i);
		if(isDataRow(p_CurrentRowPointer, charSize))
		{
			dataRowNumber++;
		}
	}
	return dataRowNumber;
}

int countDataNumber(char* p_rowPointer, int charSize)
{
	//需要跳过前面n个字符，清点数据个数
	int charToSkip = 8;

	char temp;
	int dataNumber = 0;
	for(int j=charToSkip;j<charSize; j++)
	{
		temp = *(p_rowPointer+j);

		//首字符不是空格的一定不是数据行
		if(32 == temp)
		{
			dataNumber++;
		}
	}
	return dataNumber;
};

void initDataRowSize(char** p_rowPointers, int* p_rowPointerSize, int rowNum, int** p_dataRowPointers, int* p_dataRowPointerSize)
{
	char* p_CurrentRowPointer = *p_rowPointers;
	int** p_CurrentDataRowPointer = p_dataRowPointers;
	int* p_CurrentDataRowPointerSize = p_dataRowPointerSize;
	//int dataRowIndex = 0;
	int dataNum = 0;
	for(int i=0; i<rowNum; i++)
	{
		p_CurrentRowPointer = *(p_rowPointers+i);
		int charSize = *(p_rowPointerSize+i);
		if(isDataRow(p_CurrentRowPointer, charSize))
		{
			dataNum = countDataNumber(p_CurrentRowPointer, charSize);
			//为数据分配存储空间
			*p_CurrentDataRowPointer = malloc(sizeof(int) * dataNum);

			//记录数据数量
			*p_CurrentDataRowPointerSize = dataNum;

			p_CurrentDataRowPointer++;
			p_CurrentDataRowPointerSize++;
		}
	}
}
void steupDataRowContent(char* p_CurrentRowPointer, int charSize, int* p_CurrentDataRowPointer)
{
	char temp;
	int temp_int = 0;
	int charToSkip = 9;
	int dataIndex = 0;
	int hasData = 0;
	for(int j=charToSkip;j<charSize; j++)
	{
		temp = *(p_CurrentRowPointer+j);

		switch(temp)
		{
			case 32: //空格符
			{
				*(p_CurrentDataRowPointer + dataIndex) = temp_int;
				dataIndex++;
				temp_int = 0;
				hasData = 0;
				break;
			}
    		//数字
    		case 48:
    		case 49:
    		case 50:
    		case 51:
    		case 52:
    		case 53:
    		case 54:
    		case 55:
    		case 56:
    		case 57:
    		{
    			temp_int = 10*temp_int + temp - 48;
    			hasData = 1;
    			break;
    		}
		}
	}
	if(hasData)//最后还有剩余的数据没有抽取的话，抽取一次
	{
		*(p_CurrentDataRowPointer + dataIndex) = temp_int;
	}

}

/*
 * 判断是否独立数据行，根据第8列字符是“1”为独立数据，是“-”为关联数据
 *
 */
int isDataIndependent(char* p_CurrentRowPointer)
{
	//取第8个字符出来
	if(*(p_CurrentRowPointer+7) == 49)
		return 1;
	else
		return 0;
}

void initDataRowContent(char** p_rowPointers, int* p_rowPointerSize, int rowNum, int** p_dataRowPointers, int* p_dataRowPointerSize, int* p_dataIsIndependent)
{
	char* p_CurrentRowPointer = *p_rowPointers;
	int* p_CurrentDataRowPointer = *p_dataRowPointers;
	int* p_CurrentDataIndependentPointer = p_dataIsIndependent;
	int dataRowIndex = 0;

	for(int i=0; i<rowNum; i++)
	{
		p_CurrentRowPointer = *(p_rowPointers+i);
		int charSize = *(p_rowPointerSize+i);

		//如果是数据行的话，需要提取数据
		if(isDataRow(p_CurrentRowPointer, charSize))
		{
			p_CurrentDataRowPointer = *(p_dataRowPointers+dataRowIndex);
			steupDataRowContent(p_CurrentRowPointer, charSize, p_CurrentDataRowPointer);

			p_CurrentDataIndependentPointer = p_dataIsIndependent+dataRowIndex;
			*p_CurrentDataIndependentPointer = isDataIndependent(p_CurrentRowPointer);

			dataRowIndex++;
		}
	}
}

void constructPolyChain(pointstr **p_polyChain, int** p_dataRowPointers, int* p_dataRowPointerSize, int* p_isDataIndependent, int dataRowNum)
{
	pointstr* p_CurrentPoly = *p_polyChain;
	pointstr* p_NextPoly;

	//int dataRowIndex = 0;
	int isCurrentDataIndependent;
	int* p_CurrentDataRowPointer;

	int polyIndex = -1;

	for(int i=0; i<dataRowNum; i++)
	{
		p_CurrentDataRowPointer = *(p_dataRowPointers+i);
		//当前行是否独立标志位
		isCurrentDataIndependent = *(p_isDataIndependent+i);
		if(isCurrentDataIndependent)
		{
			polyIndex++;
		}
		int dataSize = *(p_dataRowPointerSize+i);
		//构造一行数据
		for(int j=0; j<dataSize; j = j+2)
		{

			p_NextPoly =  (pointstr*)malloc(sizeof(pointstr));
			p_NextPoly->v.x = *(p_CurrentDataRowPointer+j);
			p_NextPoly->v.y = *(p_CurrentDataRowPointer+j+1);
			p_NextPoly->nextp = 0;

			//独立数据行的首元素地址，应赋值给链表头
			if(j == 0 && isCurrentDataIndependent)
			{
				*(p_polyChain+polyIndex) = p_NextPoly;

			}

			//非独立数据行的首元素地址，需要附加到前一个链表节点的next指针
			if(j == 0 && !isCurrentDataIndependent)
			{
				p_CurrentPoly->nextp = p_NextPoly;

			}

			//若不是首元素，需要附加到前一个链表节点的next指针
			if(j!=0)
			{
				p_CurrentPoly->nextp = p_NextPoly;
			}

			//当前节点移动至下一个
			p_CurrentPoly = p_NextPoly;
		}
	}

}

pointstr_linklist* parseNSFFile(char* fileDir)
{
	FILE *pFile=fopen(fileDir,"r");
    if(pFile==NULL)
    {
        fprintf(stderr,"Cannot open file.\n");
        return 0;
    }

    //行数量
    int rowNum = countRowNumber(pFile);
    //行数据
    char* rowPointers[rowNum];
    int rowPointerSize[rowNum];

    rewind(pFile);
    //初始化各行数据的size
    initRowSize(pFile, rowPointers, rowPointerSize, rowNum);

    //初始化每行的内容
    rewind(pFile);
    initRowContent(pFile, rowPointers, rowPointerSize, rowNum);

	fclose(pFile);

    int dataRowNum = countDataRowNumber(rowPointers,rowPointerSize,rowNum);
    //数据行的数据
    int* dataRowPointers[dataRowNum];
    int dataRowPointerSize[dataRowNum];
    int isDataIndependent[dataRowNum];

    initDataRowSize(rowPointers,rowPointerSize,rowNum,dataRowPointers,dataRowPointerSize);
    initDataRowContent(rowPointers,rowPointerSize,rowNum,dataRowPointers,dataRowPointerSize,isDataIndependent);

    //统计独立多边形的个数
    int independentShapeNum = 0;
    for(int i=0;i<dataRowNum; i++)
    {
    	if(isDataIndependent[i])
    	{
    		independentShapeNum++;
    	}
    }

    //根据 独立多边形的个数 建立点链表数组
    pointstr** polyChain = malloc(independentShapeNum*sizeof(pointstr*));

    //根据已解析出的数据构造多边形点链表
    constructPolyChain(polyChain, dataRowPointers, dataRowPointerSize, isDataIndependent, dataRowNum);

    pointstr_linklist* p_polylist = (pointstr_linklist*)malloc(sizeof(pointstr_linklist));
    p_polylist->length = independentShapeNum;
    p_polylist->polyHeaderList = polyChain;
    return p_polylist;
}

int main(void)
{
	//文件路径及文件名，可以是相对路径，也可以写绝对路径
	char fileName[50] = "PattentTest_zp.nsf";

	//解析出来的链表结构体，包括链表头数组和链表头数量
	pointstr_linklist* p_polyList = parseNSFFile(fileName);

	//链表头数量，也就是独立多边形的数量
	int independentShapeNum = p_polyList->length;

	//遍历解析出来的链表头以及链表里的数据，并打印
	for(int i=0;i<independentShapeNum; i++)
	{
		printf("Data Chain index: ");
		printf("%d",i);
		printf("\n");
		pointstr* p_currentPoint = *(p_polyList->polyHeaderList+i);

		while(1)
		{
			printf("%d", p_currentPoint->v.x);
			printf(" ");
			printf("%d", p_currentPoint->v.y);
			printf(" ");
			if(p_currentPoint->nextp != 0)
			{
				p_currentPoint = p_currentPoint->nextp;
			}
			else
				break;
		}
		printf("\n");
	}

	return EXIT_SUCCESS;


}


