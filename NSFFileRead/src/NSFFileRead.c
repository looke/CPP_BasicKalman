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
    		//���з�
    		case 10:
    		{
    			//if(hasNumber)
    			//{
    				rowNum++;
    			//}
    			//hasNumber = 0;
    			break;
    		}
    		//����
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

    //��ʼ��ÿ�е����ݳ���
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
    		//���з�
    		case 10:
    		{
    			//���������ݵ��У����������ռ�
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
    		//����
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
    //��ʼ��ÿ�е����ݳ���
    //int hasNumber = 0;
    while(1)
    {
    	if(fread(&buf,sizeof(char),1,pFile)!=1)
    	{
    		break;
    	}
    	switch (buf)
    	{
    		//���з�
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
	//��Ҫ����ǰ��n���ַ����ж��Ƿ����ڱ������ݵ���
	int charToSkip = 9;

	char temp;
	for(int j=0;j<charSize; j++)
	{
		temp = *(p_rowPointer+j);

		//���ַ����ǿո��һ������������
		if(0 ==j && temp != 32)
		{
			return 0;
		}

		//����ǰ���n���ַ�
		if(j < charToSkip)
		{
			continue;
		}

		//����ǰ���n+1���ַ������־�Ϊ������
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
	//��Ҫ����ǰ��n���ַ���������ݸ���
	int charToSkip = 8;

	char temp;
	int dataNumber = 0;
	for(int j=charToSkip;j<charSize; j++)
	{
		temp = *(p_rowPointer+j);

		//���ַ����ǿո��һ������������
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
			//Ϊ���ݷ���洢�ռ�
			*p_CurrentDataRowPointer = malloc(sizeof(int) * dataNum);

			//��¼��������
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
			case 32: //�ո��
			{
				*(p_CurrentDataRowPointer + dataIndex) = temp_int;
				dataIndex++;
				temp_int = 0;
				hasData = 0;
				break;
			}
    		//����
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
	if(hasData)//�����ʣ�������û�г�ȡ�Ļ�����ȡһ��
	{
		*(p_CurrentDataRowPointer + dataIndex) = temp_int;
	}

}

/*
 * �ж��Ƿ���������У����ݵ�8���ַ��ǡ�1��Ϊ�������ݣ��ǡ�-��Ϊ��������
 *
 */
int isDataIndependent(char* p_CurrentRowPointer)
{
	//ȡ��8���ַ�����
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

		//����������еĻ�����Ҫ��ȡ����
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
		//��ǰ���Ƿ������־λ
		isCurrentDataIndependent = *(p_isDataIndependent+i);
		if(isCurrentDataIndependent)
		{
			polyIndex++;
		}
		int dataSize = *(p_dataRowPointerSize+i);
		//����һ������
		for(int j=0; j<dataSize; j = j+2)
		{

			p_NextPoly =  (pointstr*)malloc(sizeof(pointstr));
			p_NextPoly->v.x = *(p_CurrentDataRowPointer+j);
			p_NextPoly->v.y = *(p_CurrentDataRowPointer+j+1);
			p_NextPoly->nextp = 0;

			//���������е���Ԫ�ص�ַ��Ӧ��ֵ������ͷ
			if(j == 0 && isCurrentDataIndependent)
			{
				*(p_polyChain+polyIndex) = p_NextPoly;

			}

			//�Ƕ��������е���Ԫ�ص�ַ����Ҫ���ӵ�ǰһ������ڵ��nextָ��
			if(j == 0 && !isCurrentDataIndependent)
			{
				p_CurrentPoly->nextp = p_NextPoly;

			}

			//��������Ԫ�أ���Ҫ���ӵ�ǰһ������ڵ��nextָ��
			if(j!=0)
			{
				p_CurrentPoly->nextp = p_NextPoly;
			}

			//��ǰ�ڵ��ƶ�����һ��
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

    //������
    int rowNum = countRowNumber(pFile);
    //������
    char* rowPointers[rowNum];
    int rowPointerSize[rowNum];

    rewind(pFile);
    //��ʼ���������ݵ�size
    initRowSize(pFile, rowPointers, rowPointerSize, rowNum);

    //��ʼ��ÿ�е�����
    rewind(pFile);
    initRowContent(pFile, rowPointers, rowPointerSize, rowNum);

	fclose(pFile);

    int dataRowNum = countDataRowNumber(rowPointers,rowPointerSize,rowNum);
    //�����е�����
    int* dataRowPointers[dataRowNum];
    int dataRowPointerSize[dataRowNum];
    int isDataIndependent[dataRowNum];

    initDataRowSize(rowPointers,rowPointerSize,rowNum,dataRowPointers,dataRowPointerSize);
    initDataRowContent(rowPointers,rowPointerSize,rowNum,dataRowPointers,dataRowPointerSize,isDataIndependent);

    //ͳ�ƶ�������εĸ���
    int independentShapeNum = 0;
    for(int i=0;i<dataRowNum; i++)
    {
    	if(isDataIndependent[i])
    	{
    		independentShapeNum++;
    	}
    }

    //���� ��������εĸ��� ��������������
    pointstr** polyChain = malloc(independentShapeNum*sizeof(pointstr*));

    //�����ѽ����������ݹ������ε�����
    constructPolyChain(polyChain, dataRowPointers, dataRowPointerSize, isDataIndependent, dataRowNum);

    pointstr_linklist* p_polylist = (pointstr_linklist*)malloc(sizeof(pointstr_linklist));
    p_polylist->length = independentShapeNum;
    p_polylist->polyHeaderList = polyChain;
    return p_polylist;
}

int main(void)
{
	//�ļ�·�����ļ��������������·����Ҳ����д����·��
	char fileName[50] = "PattentTest_zp.nsf";

	//��������������ṹ�壬��������ͷ���������ͷ����
	pointstr_linklist* p_polyList = parseNSFFile(fileName);

	//����ͷ������Ҳ���Ƕ�������ε�����
	int independentShapeNum = p_polyList->length;

	//������������������ͷ�Լ�����������ݣ�����ӡ
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


