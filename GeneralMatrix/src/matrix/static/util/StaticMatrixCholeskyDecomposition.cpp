/*
 * StaticMatrixCholeskyDecomposition.cpp
 *
 *  Created on: 2017年3月18日
 *      Author: looke
 */
#include <static/util/StaticMatrixCholeskyDecomposition.h>
#include <iostream>
#include "math.h"
#include <cmath>
using namespace std;

/*
 * 初始化 Cholesky分解
 */
StaticMatrixCholeskyDecomposition::StaticMatrixCholeskyDecomposition(BasicMatrix* input_opMatrix):MatrixCholeskyDecomposition(input_opMatrix),opMatrix(),DecompositionMatrix()
{
	this->init(input_opMatrix);
};

void StaticMatrixCholeskyDecomposition::init(BasicMatrix* input_opMatrix)
{
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;

	//初始化操作矩阵以及分解结果矩阵  操作矩阵拷贝输入矩阵的各个元素 分解矩阵初始化为全0矩阵
	this->opMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_opMatrix = this->opMatrix.getCurrentMatrixPointer();
	this->p_opMatrix = &this->opMatrix;

	this->DecompositionMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_DecompositionMatrix = this->DecompositionMatrix.getCurrentMatrixPointer();
	this->p_DecompositionMatrix = &this->DecompositionMatrix;

	this->p_opMatrix->copyMatrixElementNoCheck(input_opMatrix);
	this->p_DecompositionMatrix->resetMatrixToZero();

};

void StaticMatrixCholeskyDecomposition::reload(BasicMatrix* input_opMatrix)
{
	if(this->rowNumber==input_opMatrix->rowNum && this->columnNumber==input_opMatrix->columnNum)
	{
		this->p_opMatrix->copyMatrixElementNoCheck(input_opMatrix);
		this->p_DecompositionMatrix->resetMatrixToZero();
	}
	else
	{
		this->init(input_opMatrix);
	}
};

