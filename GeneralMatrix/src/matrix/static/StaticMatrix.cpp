/*
 * StaticMatrix.cpp
 *
 *  Created on: 2017年4月25日
 *      Author: looke
 */

#include <static/StaticMatrix.h>
#include <iostream>
#include "math.h"

using namespace std;

StaticMatrix::StaticMatrix()
{
	//this->precision = 0.0000000001;
	this->space = 20;
	this->rowNum = 1;
	this->columnNum = 1;
};

StaticMatrix::StaticMatrix(int inputRowNum, int inputColumnNum)
{
	initPrecision();
	this->space = 20;
	this->rowNum = inputRowNum;
	this->columnNum = inputColumnNum;
	for(int i=0; i<this->space; i++)
	{
		for(int j=0; j<this->space; j++)
		{
			this->matrixNxN[i][j] = 0;
		}
	}

	this->initMatrix();
};


void StaticMatrix::initMatrix()
{
	double tempValue = 1;
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			this->matrixNxN[i][j] = tempValue;
			tempValue++;
		}
	}

	//初始化行列向量对象
	this->columnVector = StaticVector(this->rowNum);

	this->rowVector = StaticVector(this->columnNum);

};

void StaticMatrix::setMatrixElement(int rNum, int cNum, double val)
{
	this->matrixNxN[rNum][cNum] = val;
};


double StaticMatrix::getMatrixElement(int rNum, int cNum)
{
	return this->matrixNxN[rNum][cNum];
};

/*
 * 获取矩阵指定元素的值(对元素值进行整形，小于精度的值直接返回0)
 */
double StaticMatrix::getMatrixElementRegulared(int rNum, int cNum, double lowEdge)
{
	if(fabs(this->matrixNxN[rNum][cNum]) < lowEdge)
	{
		return 0;
	}
	return this->matrixNxN[rNum][cNum];
};

void StaticMatrix::printMatrix()
{
	for(int i=0;i<this->rowNum;i++)
	{
		for(int j=0;j<this->columnNum;j++)
		{
			cout.width(10);
			cout<<this->matrixNxN[i][j]<<"\t";
		}
		cout<<endl;
	}
};

//交换行
void StaticMatrix::swapRow(int from, int to)
{
	if(from < this->rowNum && to < this->rowNum)
	{
		double temp[this->columnNum];

		for(int i=0; i < this->columnNum; i++)
		{
			temp[i] = matrixNxN[from][i];
		}

		for(int i=0; i < this->columnNum; i++)
		{
			matrixNxN[from][i] = matrixNxN[to][i];
		}

		for(int i=0; i < this->columnNum; i++)
		{
			matrixNxN[to][i] = temp[i];
		}
	}
	else
	{
		cout<<"Illegal row number." << endl;
	}
};

//交换列
void StaticMatrix::swapColumn(int from, int to)
{
	if(from < this->columnNum && to < this->columnNum)
	{
		double temp[this->rowNum];

		for(int i=0; i < this->rowNum; i++)
		{
			temp[i] = matrixNxN[i][from];
		}

		for(int i=0; i < this->rowNum; i++)
		{
			matrixNxN[i][from] = matrixNxN[i][to];
		}

		for(int i=0; i < this->rowNum; i++)
		{
			matrixNxN[i][to] = temp[i];
		}
	}
	else
	{
		cout<<"Illegal column number." << endl;
	}

};

//交换对角线主元
void StaticMatrix::swapDiagElement(int from, int to)
{
	if(from < this->columnNum && to < this->columnNum && from < this->rowNum && to < this->rowNum)
	{
		double temp;
		temp = matrixNxN[from][from];

		matrixNxN[from][from] = matrixNxN[to][to];
		matrixNxN[to][to] = temp;
	}
};

//将矩阵重置为单位矩阵
void StaticMatrix::resetMatrixToI()
{
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			if(i==j)
			{
				matrixNxN[i][j] = 1;
			}
			else
			{
				matrixNxN[i][j] = 0;
			}
		}
	}
};

//将矩阵重置为单位矩阵
void StaticMatrix::resetMatrixToZero()
{
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{

			matrixNxN[i][j] = 0;

		}
	}
};

//获取指定列向量
BasicVector* StaticMatrix::getColumnVector(int columnNo)
{
	int newColumnVectorDimension = this->rowNum ;
	this->columnVector.resetDimension(newColumnVectorDimension);

	for(int i=0; i<this->rowNum; i++)
	{
		columnVector.setElement(i,matrixNxN[i][columnNo]);

	}
	return &columnVector;
};

//获取指定行向量
BasicVector* StaticMatrix::getRowVector(int rowNo)
{
	int newRowVectorDimension = this->columnNum ;
	this->rowVector.resetDimension(newRowVectorDimension);

	for(int i=0; i<this->columnNum; i++)
	{
		rowVector.setElement(i,matrixNxN[rowNo][i]);
	}
	return &rowVector;
};


//获取对角线子矩阵指定列向量
BasicVector* StaticMatrix::getSubMatrixColumnVector(int subMatrixIndex, int columnNo)
{
	int newColumnVectorDimension = this->rowNum - subMatrixIndex;
	this->columnVector.resetDimension(newColumnVectorDimension);

	int index = 0;
	for(int i=subMatrixIndex; i<this->rowNum; i++)
	{
		columnVector.setElement(index,matrixNxN[i][subMatrixIndex+columnNo]);
		index++;
	}

	return &this->columnVector;
};

//获取对角线子矩阵指定行向量
BasicVector* StaticMatrix::getSubMatrixRowVector(int subMatrixIndex, int rowNo)
{
	int newRowVectorDimension = this->columnNum - subMatrixIndex;
	this->rowVector.resetDimension(newRowVectorDimension);
	int index = 0;
	for(int i=subMatrixIndex; i<this->columnNum; i++)
	{
		rowVector.setElement(index,matrixNxN[subMatrixIndex+rowNo][i]);
		index++;
	}
	return &this->rowVector;
};

//获取指定对角子矩阵hessenberg列向量
BasicVector* StaticMatrix::getSubMatrixHessenColumnVector(int subMatrixIndex)
{
	int newColumnVectorDimension = this->rowNum - subMatrixIndex - 1;
	this->columnVector.resetDimension(newColumnVectorDimension);

	int index = 0;
	for(int i=subMatrixIndex+1; i<this->rowNum; i++)
	{
		columnVector.setElement(index,matrixNxN[i][subMatrixIndex]);
		index++;
	}

	return &this->columnVector;
};
