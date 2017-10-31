/*
 * MatrixMultiplier.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#include <dynamic/util/DynamicMatrixMultiplier.h>
#include <dynamic/DynamicMatrix.h>
#include <iostream>
using namespace std;

DynamicMatrixMultiplier::DynamicMatrixMultiplier(BasicMatrix* leftOp, BasicMatrix* rightOp):MatrixMultiplier(leftOp, rightOp)
{
	this->init(leftOp, rightOp);
};

void DynamicMatrixMultiplier::init(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	this->p_leftOpMatrix = leftOp;
	this->leftRow = leftOp->rowNum;
	this->leftColumn = leftOp->columnNum;

	this->p_rightOpMatrix = rightOp;
	this->rightRow = rightOp->rowNum;
	this->rightColumn = rightOp->columnNum;

	if(this->leftColumn == this->rightRow)
	{
		this->isLegalMultiply = true;
		this->MultiResult = DynamicMatrix(this->leftRow, this->rightColumn);
		this->p_MultiResult = &this->MultiResult;
	}
	else
	{
		this->isLegalMultiply = false;
	}
};

/*
 * 重新装填
 * 使用新的左右操作矩阵，重新初始化乘法器
 * 如果新的左右操作矩阵行列数不变，则不会重新申请操作结果矩阵，以节省内存开销
 */
void DynamicMatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	//如果重新装填的矩阵与当前初始化的矩阵行列数一致，则不需要重新生成乘积结果矩阵，将原乘积结果矩阵内容重置即可，降低内存开销
	if(	this->leftRow == leftOp->rowNum &&
		this->leftColumn == leftOp->columnNum &&
		this->rightRow == rightOp->rowNum &&
		this->rightColumn == rightOp->columnNum
	  )
	{
		this->p_leftOpMatrix = leftOp;
		this->p_rightOpMatrix = rightOp;
		this->MultiResult.resetMatrixToI();
	}
	else//如果重新装填的矩阵与当前初始化的矩阵行列数不同，则需要重新生成乘积结果矩阵
	{
		this->init(leftOp, rightOp);
	}
};


