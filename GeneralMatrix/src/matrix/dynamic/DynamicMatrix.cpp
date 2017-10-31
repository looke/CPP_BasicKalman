/*
 * DynamicMatrix.cpp
 *
 *  Created on: 2017��2��19��
 *      Author: looke
 */

#include "DynamicMatrix.h"
#include <iostream>
#include <malloc.h>
#include "math.h"

using namespace std;


DynamicMatrix::DynamicMatrix()
{
	//Ĭ��4x5����
	//this->rowNum = 4;
	//this->columnNum = 5;

	//this->initMatrix();
	//this->precision = 0.00000000000001;
};


DynamicMatrix::DynamicMatrix(int inputRowNum, int inputColumnNum):BasicMatrix(inputRowNum, inputColumnNum)
{
	initPrecision();
	this->space = 20;
	if(inputRowNum > 0 && inputColumnNum >0)
	{
		this->rowNum = inputRowNum;
		this->columnNum = inputColumnNum;
		//call the default constructor
		this->initMatrix();
	}
	else
	{
		cout<<"Illegal in put row/column numbers!" << endl;
		cout<<"Using default row/column number construct Matrix!" << endl;
		//DynamicMatrix();
	}
};

void DynamicMatrix::initMatrix()
{
	//matrixPointer = &matrix[0][0];


	this->matrixPointer = (double **) malloc(this->space*sizeof(double *));

	for(int i=0; i<this->space; i++)
	{
		this->matrixPointer[i] = (double *) malloc(this->space*sizeof(double));
	}

	double tempValue = 1;
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			this->matrixPointer[i][j] = tempValue;
			tempValue++;
		}
	}

	this->columnVector = DynamicVector(this->rowNum);
	this->rowVector = DynamicVector(this->columnNum);
};

void DynamicMatrix::printMatrix()
{
	//print each row
	for(int i=0;i<this->rowNum;i++)
	{
		for(int j=0;j<this->columnNum;j++)
		{
			cout.width(10);
			cout<<this->matrixPointer[i][j]<<"\t";
		}
		cout<<endl;
	}
};



void DynamicMatrix::setMatrixElement(int rNum, int cNum, double val)
{
	if(rNum < this->rowNum && cNum < this->columnNum)
	{
		this->matrixPointer[rNum][cNum] = val;
	}
};

double DynamicMatrix::getMatrixElement(int rNum, int cNum)
{
	return this->matrixPointer[rNum][cNum];
};

/*
 * ��ȡ����ָ��Ԫ�ص�ֵ(��Ԫ��ֵ�������Σ�С�ھ��ȵ�ֱֵ�ӷ���0)
 */
double DynamicMatrix::getMatrixElementRegulared(int rNum, int cNum, double lowEdge)
{
	if(fabs(this->matrixPointer[rNum][cNum]) < lowEdge)
	{
		return 0;
	}
	return this->matrixPointer[rNum][cNum];
};

/*
 * ����ָ������
 */
void DynamicMatrix::swapRow(int from, int to)
{
	if(from < this->rowNum && to < this->rowNum)
	{
		double temp[this->columnNum];

		for(int i=0; i < this->columnNum; i++)
		{
			temp[i] = matrixPointer[from][i];
		}

		for(int i=0; i < this->columnNum; i++)
		{
			matrixPointer[from][i] = matrixPointer[to][i];
		}

		for(int i=0; i < this->columnNum; i++)
		{
			matrixPointer[to][i] = temp[i];
		}
	}
	else
	{
		cout<<"Illegal row number." << endl;
	}
};

/*
 *����ָ������
 */
void DynamicMatrix::swapColumn(int from, int to)
{
	if(from < this->columnNum && to < this->columnNum)
	{
		double temp[this->rowNum];

		for(int i=0; i < this->rowNum; i++)
		{
			temp[i] = matrixPointer[i][from];
		}

		for(int i=0; i < this->rowNum; i++)
		{
			matrixPointer[i][from] = matrixPointer[i][to];
		}

		for(int i=0; i < this->rowNum; i++)
		{
			matrixPointer[i][to] = temp[i];
		}
	}
	else
	{
		cout<<"Illegal column number." << endl;
	}

};

//�����Խ�����Ԫ
void DynamicMatrix::swapDiagElement(int from, int to)
{
	if(from < this->columnNum && to < this->columnNum && from < this->rowNum && to < this->rowNum)
	{
		double temp;
		temp = matrixPointer[from][from];

		matrixPointer[from][from] = matrixPointer[to][to];
		matrixPointer[to][to] = temp;
	}
};

/*
 * ����������Ϊ��λ��
 */
void DynamicMatrix::resetMatrixToI()
{
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			if(i==j)
			{
				matrixPointer[i][j] = 1;
			}
			else
			{
				matrixPointer[i][j] = 0;
			}
		}
	}
};

/*
 * ����������Ϊ0��
 */
void DynamicMatrix::resetMatrixToZero()
{
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{

			matrixPointer[i][j] = 0;

		}
	}
};

//��ȡָ��������
BasicVector* DynamicMatrix::getColumnVector(int columnNo)
{
	int newColumnVectorDimension = this->rowNum ;
	this->columnVector.resetDimension(newColumnVectorDimension);

	for(int i=0; i<this->rowNum; i++)
	{
		columnVector.setElement(i,this->matrixPointer[i][columnNo]);
	}
	return &this->columnVector;
};

//��ȡָ��������
BasicVector* DynamicMatrix::getRowVector(int rowNo)
{
	int newRowVectorDimension = this->columnNum ;
	this->rowVector.resetDimension(newRowVectorDimension);

	for(int i=0; i<this->columnNum; i++)
	{
		rowVector.setElement(i,this->matrixPointer[rowNo][i]);
	}
	return &this->rowVector;
};

//��ȡָ��������
BasicVector* DynamicMatrix::getSubMatrixColumnVector(int subMatrixIndex, int columnNo)
{
	int newColumnVectorDimension = this->rowNum - subMatrixIndex;
	this->columnVector.resetDimension(newColumnVectorDimension);

	int index = 0;

	for(int i=subMatrixIndex; i<this->rowNum; i++)
	{
		columnVector.setElement(index,this->matrixPointer[i][subMatrixIndex+columnNo]);
		index++;
	}
	return &this->columnVector;
};

//��ȡָ��������
BasicVector* DynamicMatrix::getSubMatrixRowVector(int subMatrixIndex, int rowNo)
{
	int newRowVectorDimension = this->columnNum - subMatrixIndex;
	this->rowVector.resetDimension(newRowVectorDimension);
	int index = 0;
	for(int i=subMatrixIndex; i<this->columnNum; i++)
	{
		rowVector.setElement(index,this->matrixPointer[subMatrixIndex+rowNo][i]);
		index++;
	}
	return &this->rowVector;
};

//��ȡָ���Խ��Ӿ���hessenberg������
BasicVector* DynamicMatrix::getSubMatrixHessenColumnVector(int subMatrixIndex)
{
	int newColumnVectorDimension = this->rowNum - subMatrixIndex - 1;
	this->columnVector.resetDimension(newColumnVectorDimension);

	int index = 0;

	for(int i=subMatrixIndex+1; i<this->rowNum; i++)
	{
		columnVector.setElement(index,this->matrixPointer[i][subMatrixIndex]);
		index++;
	}
	return &this->columnVector;
};
