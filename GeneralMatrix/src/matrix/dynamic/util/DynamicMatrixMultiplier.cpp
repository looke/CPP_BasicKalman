/*
 * MatrixMultiplier.cpp
 *
 *  Created on: 2017��2��25��
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
 * ����װ��
 * ʹ���µ����Ҳ����������³�ʼ���˷���
 * ����µ����Ҳ����������������䣬�򲻻��������������������Խ�ʡ�ڴ濪��
 */
void DynamicMatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
{
	//�������װ��ľ����뵱ǰ��ʼ���ľ���������һ�£�����Ҫ�������ɳ˻�������󣬽�ԭ�˻���������������ü��ɣ������ڴ濪��
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
	else//�������װ��ľ����뵱ǰ��ʼ���ľ�����������ͬ������Ҫ�������ɳ˻��������
	{
		this->init(leftOp, rightOp);
	}
};


