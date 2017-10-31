/*
 * DynamicMatrixCholeskyDecomposition.cpp
 *
 *  Created on: 2017年3月18日
 *      Author: looke
 */
#include <dynamic/util/DynamicMatrixCholeskyDecomposition.h>
#include <dynamic/DynamicMatrix.h>
#include <iostream>
#include "math.h"
#include <cmath>
using namespace std;

/*
 * 初始化 Cholesky分解
 */
DynamicMatrixCholeskyDecomposition::DynamicMatrixCholeskyDecomposition(BasicMatrix* input_opMatrix):MatrixCholeskyDecomposition(input_opMatrix)
{

	this->init(input_opMatrix);

};

void DynamicMatrixCholeskyDecomposition::init(BasicMatrix* input_opMatrix)
{
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;

	//初始化操作矩阵以及分解结果矩阵  操作矩阵拷贝输入矩阵的各个元素 分解矩阵初始化为全0矩阵
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

