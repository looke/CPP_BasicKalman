/*
 * MatrixMultiplier.cpp
 *
 *  Created on: 2017��2��25��
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
 * ����װ��
 * ʹ���µ����Ҳ����������³�ʼ���˷���
 * ����µ����Ҳ����������������䣬�򲻻��������������������Խ�ʡ�ڴ濪��
 */
/*
void MatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	//�������װ��ľ����뵱ǰ��ʼ���ľ���������һ�£�����Ҫ�������ɳ˻�������󣬽�ԭ�˻���������������ü��ɣ������ڴ濪��
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
	else//�������װ��ľ����뵱ǰ��ʼ���ľ�����������ͬ������Ҫ�������ɳ˻��������
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
		//���˷�������ʱ���ؿ�ָ��
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
