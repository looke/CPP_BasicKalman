/*
 * DynamicMatrixCholeskyDecomposition.cpp
 *
 *  Created on: 2017��3��18��
 *      Author: looke
 */
#include <dynamic/util/DynamicMatrixCholeskyDecomposition.h>
#include <dynamic/DynamicMatrix.h>
#include <iostream>
#include "math.h"
#include <cmath>
using namespace std;

/*
 * ��ʼ�� Cholesky�ֽ�
 */
DynamicMatrixCholeskyDecomposition::DynamicMatrixCholeskyDecomposition(BasicMatrix* input_opMatrix):MatrixCholeskyDecomposition(input_opMatrix)
{

	this->init(input_opMatrix);

};

void DynamicMatrixCholeskyDecomposition::init(BasicMatrix* input_opMatrix)
{
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;

	//��ʼ�����������Լ��ֽ�������  �������󿽱��������ĸ���Ԫ�� �ֽ�����ʼ��Ϊȫ0����
	this->opMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_opMatrix = &this->opMatrix;

	this->DecompositionMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_DecompositionMatrix = &this->DecompositionMatrix;

	this->opMatrix.copyMatrixElementNoCheck(input_opMatrix);
	this->DecompositionMatrix.resetMatrixToZero();

};

void DynamicMatrixCholeskyDecomposition::reload(BasicMatrix* input_opMatrix)
{
	if(this->rowNumber==input_opMatrix->rowNum && this->columnNumber==input_opMatrix->columnNum)
	{
		this->opMatrix.copyMatrixElementNoCheck(input_opMatrix);
		this->DecompositionMatrix.resetMatrixToZero();
	}
	else
	{
		this->init(input_opMatrix);
	}
};

