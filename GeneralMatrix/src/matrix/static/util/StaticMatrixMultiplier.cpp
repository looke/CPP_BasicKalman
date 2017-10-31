/*
 * StaticMatrixMultiplier.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#include <static/util/StaticMatrixMultiplier.h>
#include <iostream>
using namespace std;

StaticMatrixMultiplier::StaticMatrixMultiplier(BasicMatrix* leftOp, BasicMatrix* rightOp):MatrixMultiplier(leftOp, rightOp)
{
	this->init(leftOp, rightOp);
};

void StaticMatrixMultiplier::init(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	this->p_leftOpMatrix = leftOp;
	this->leftRow = leftOp->rowNum;
	this->leftColumn = leftOp->columnNum;

	this->p_rightOpMatrix = rightOp;
	this->rightRow = rightOp->rowNum;
	this->rightColumn = rightOp->columnNum;

	//this->MultiResult1515 = Static1515Matrix();
	//this->MultiResult1010 = Static1010Matrix();

	if(this->leftColumn == this->rightRow)
	{
		this->isLegalMultiply = true;

		this->MultiResult = StaticMatrix(leftRow,rightColumn);
		//this->MultiResult.init(leftRow,rightColumn);
		this->p_MultiResult = &this->MultiResult;
		//this->p_MultiResult = this->MultiResult.getCurrentMatrixPointer();

		/*
		//左操作矩阵15*10  右操作矩阵10*15 乘积结果矩阵15*15
		if(leftRow==15 && leftColumn==10 && rightRow==10 && rightColumn==15)
		{
			this->p_MultiResult = &this->MultiResult1515;
		}
		//左操作矩阵15*15  右操作矩阵15*15 乘积结果矩阵15*15
		if(leftRow==15 && leftColumn==15 && rightRow==15 && rightColumn==15)
		{
			this->p_MultiResult = &this->MultiResult1515;
		}

		//左操作矩阵10*15  右操作矩阵15*10 乘积结果矩阵10*10
		if(leftRow==10 && leftColumn==15 && rightRow==15 && rightColumn==10)
		{
			this->p_MultiResult = &this->MultiResult1010;
		}
		//左操作矩阵10*10  右操作矩阵10*10 乘积结果矩阵10*10
		if(leftRow==10 && leftColumn==10 && rightRow==10 && rightColumn==10)
		{
			this->p_MultiResult = &this->MultiResult1010;
		}
		*/
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
void StaticMatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
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
		this->p_MultiResult->resetMatrixToI();
		//this->MultiResult1515.resetMatrixToI();
		//this->MultiResult1010.resetMatrixToI();
	}
	else//如果重新装填的矩阵与当前初始化的矩阵行列数不同，则需要重新生成乘积结果矩阵
	{
		this->init(leftOp, rightOp);
	}
};


