/*
 * QRDecomposition.cpp
 *
 *  Created on: 2017年4月25日
 *      Author: looke
 */


#include "QRDecomposition.h"
#include <iostream>
using namespace std;

QRDecomposition::QRDecomposition()
{};

QRDecomposition::QRDecomposition(BasicMatrix* input_Matrix)
{
	this->init(input_Matrix);
};

void QRDecomposition::init(BasicMatrix* input_Matrix)
{};

void QRDecomposition::reload(BasicMatrix* input_Matrix)
{};

BasicMatrix* QRDecomposition::getQMatrix()
{
	return this->p_QMatrix;
};

BasicMatrix* QRDecomposition::getQTMatrix()
{
	return this->p_QTMatrix;
};

BasicMatrix* QRDecomposition::getRMatrix()
{
	return this->p_OpMatrix;
};

BasicMatrix* QRDecomposition::getHouseholderMatrix()
{
	return this->p_householderMatrix;
};
/*
 * 根据OP矩阵的各列向量,计算Householder变换矩阵,逐步将OP矩阵对角化
 */
void QRDecomposition::calcQRMatrix()
{
	this->p_householderMatrix->resetMatrixToI();
	this->p_QMatrix->resetMatrixToI();
	this->p_QTMatrix->resetMatrixToI();
	int iterationMax = this->p_OpMatrix->rowNum-1;

	for(int i=0; i<iterationMax; i++)
	{
		generateHouseholderMatrix(i);
		updateMatrix();
	}

};

//生成HouseHolder变换矩阵 index表示当前迭代进行的对角线元素的索引
void QRDecomposition::generateHouseholderMatrix(int index)
{
	BasicVector *p_currentColumnVector = this->p_OpMatrix->getSubMatrixColumnVector(index,0);
	p_HouseholderTrans->reload(p_currentColumnVector);

	BasicMatrix* p_subHouseholderMatrix = p_HouseholderTrans->getHouseholderMatrixToE1(true);

	cout << "Sub Householder Matrix:" << endl;
	p_subHouseholderMatrix->printMatrix();
	//更新Householder矩阵
	this->p_householderMatrix->resetMatrixToI();
	//int m=0;
	//int n=0;
	for(int i=index, m=0;i<this->p_householderMatrix->rowNum; i++,m++)
	{
		//n=0;
		for(int j=index, n=0; j<this->p_householderMatrix->columnNum; j++,n++)
		{
			p_householderMatrix->setMatrixElement(i,j,p_subHouseholderMatrix->getMatrixElement(m,n));
			//n++;
		}
		//m++;
	}

};

/*
 * 计算出本次迭代的householder矩阵后,更新OP矩阵和Q矩阵
 */
void QRDecomposition::updateMatrix()
{
	//update op matrix
	this->p_Multiplier->reload(this->p_householderMatrix, this->p_OpMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_OpMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
	//this->p_OpMatrix->regularZeroElement();
	//update QT Matrix
	this->p_Multiplier->reload(this->p_householderMatrix, this->p_QTMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_QTMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
	//this->p_QTMatrix->regularZeroElement();
	//Update Q matrix
	this->p_Multiplier->reload(this->p_QMatrix, this->p_householderMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_QMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
	//this->p_QMatrix->regularZeroElement();


	cout << "OP Matrix After QR update:" << endl;
	this->p_OpMatrix->printMatrix();
	cout << "QT Matrix After QR update:" << endl;
	this->p_QTMatrix->printMatrix();
	cout << "Q Matrix After QR update:" << endl;
	this->p_QMatrix->printMatrix();
};
