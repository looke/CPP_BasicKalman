/*
 * MatrixMultiplier.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#include "MatrixMultiplier.h"
#include <iostream>
using namespace std;

MatrixMultiplier::MatrixMultiplier(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	this->init(leftOp, rightOp);
};

void MatrixMultiplier::init(BasicMatrix* leftOp, BasicMatrix* rightOp)
{

};
/*
void MatrixMultiplier::init(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	this->leftOpMatrix = leftOp;
	this->leftRow = leftOp->rowNum;
	this->leftColumn = leftOp->columnNum;

	this->rightOpMatrix = rightOp;
	this->rightRow = rightOp->rowNum;
	this->rightColumn = rightOp->columnNum;

	if(this->leftColumn == this->rightRow)
	{
		this->isLegalMultiply = true;
		this->MultiResult = DynamicMatrix(this->leftRow, this->rightColumn);
	}
	else
	{
		this->isLegalMultiply = false;
	}
};
*/
void MatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
{

};
/*
 * 重新装填
 * 使用新的左右操作矩阵，重新初始化乘法器
 * 如果新的左右操作矩阵行列数不变，则不会重新申请操作结果矩阵，以节省内存开销
 */
/*
void MatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	//如果重新装填的矩阵与当前初始化的矩阵行列数一致，则不需要重新生成乘积结果矩阵，将原乘积结果矩阵内容重置即可，降低内存开销
	if(	this->leftRow == leftOp->rowNum &&
		this->leftColumn == leftOp->columnNum &&
		this->rightRow == rightOp->rowNum &&
		this->rightColumn == rightOp->columnNum
	  )
	{
		this->leftOpMatrix = leftOp;
		this->rightOpMatrix = rightOp;
		this->MultiResult.resetMatrixToI();
	}
	else//如果重新装填的矩阵与当前初始化的矩阵行列数不同，则需要重新生成乘积结果矩阵
	{
		this->init(leftOp, rightOp);
	}
};
*/


BasicMatrix* MatrixMultiplier::getMultiplyResult()
{
	if(isLegalMultiply)
	{
		return this->p_MultiResult;
	}
	else
	{
		//当乘法不成立时返回空指针
		return 0;
	}
};

void MatrixMultiplier::multiplyCalc()
{
	if(isLegalMultiply)
	{
		double temp = 0.0;
		double leftOp = 0.0;
		double rightOp = 0.0;
		double multiTemp = 0.0;
		for(int i=0; i<this->leftRow; i++)
		{
			for(int j=0; j<this->rightColumn; j++)
			{
				temp=0;

				for(int k=0; k<this->leftColumn; k++ )
				{
					leftOp = p_leftOpMatrix->getMatrixElement(i,k);
					rightOp = p_rightOpMatrix->getMatrixElement(k,j);
					multiTemp = leftOp*rightOp;
					temp = temp + multiTemp;
				}
				p_MultiResult->setMatrixElement(i,j, temp);
			}
		}
	}
};


void MatrixMultiplier::printMultiplyResult()
{
	if(isLegalMultiply)
	{
		p_MultiResult->printMatrix();

	}
};
