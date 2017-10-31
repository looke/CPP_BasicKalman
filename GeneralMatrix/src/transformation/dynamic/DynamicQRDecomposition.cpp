/*
 * DynamicQRDecomposition.cpp
 *
 *  Created on: 2017年4月27日
 *      Author: looke
 */

#include "DynamicQRDecomposition.h"

//DynamicQRDecomposition::DynamicQRDecomposition()
//{};

DynamicQRDecomposition::DynamicQRDecomposition(BasicMatrix* input_Matrix):Multiplier(input_Matrix,input_Matrix),HouseholderTrans()
{
	this->init(input_Matrix);
};


void DynamicQRDecomposition::init(BasicMatrix* input_Matrix)
{
	//操作矩阵
	this->OpMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->OpMatrix.copyMatrixElementNoCheck(input_Matrix);
	this->p_OpMatrix = &OpMatrix;

	//householder矩阵，每次迭代使用
	this->householderMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->p_householderMatrix = &householderMatrix;

	//Q矩阵
	this->QMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->p_QMatrix = &QMatrix;

	//Q矩阵的转置(逆矩阵)
	this->QTMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->p_QTMatrix = &QTMatrix;

	//乘法器
	this->p_Multiplier = &this->Multiplier;

	//Householder变换器
	this->p_HouseholderTrans = &this->HouseholderTrans;
};

/*
 * 重新加载新的操作矩阵
 */
void DynamicQRDecomposition::reload(BasicMatrix* input_Matrix)
{
	//重新加载的矩阵与原矩阵行列数相同
	if(OpMatrix.rowNum == input_Matrix->rowNum && OpMatrix.columnNum == input_Matrix->columnNum)
	{
		this->OpMatrix.copyMatrixElementNoCheck(input_Matrix);
		this->householderMatrix.resetMatrixToI();
		this->QMatrix.resetMatrixToI();
		this->QTMatrix.resetMatrixToI();
	}
	else
	{
		this->init(input_Matrix);
	}

};
