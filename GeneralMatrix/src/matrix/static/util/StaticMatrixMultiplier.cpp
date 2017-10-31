/*
 * StaticMatrixMultiplier.cpp
 *
 *  Created on: 2017��2��25��
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
		//���������15*10  �Ҳ�������10*15 �˻��������15*15
		if(leftRow==15 && leftColumn==10 && rightRow==10 && rightColumn==15)
		{
			this->p_MultiResult = &this->MultiResult1515;
		}
		//���������15*15  �Ҳ�������15*15 �˻��������15*15
		if(leftRow==15 && leftColumn==15 && rightRow==15 && rightColumn==15)
		{
			this->p_MultiResult = &this->MultiResult1515;
		}

		//���������10*15  �Ҳ�������15*10 �˻��������10*10
		if(leftRow==10 && leftColumn==15 && rightRow==15 && rightColumn==10)
		{
			this->p_MultiResult = &this->MultiResult1010;
		}
		//���������10*10  �Ҳ�������10*10 �˻��������10*10
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
 * ����װ��
 * ʹ���µ����Ҳ����������³�ʼ���˷���
 * ����µ����Ҳ����������������䣬�򲻻��������������������Խ�ʡ�ڴ濪��
 */
void StaticMatrixMultiplier::reload(BasicMatrix* leftOp, BasicMatrix* rightOp)
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
		this->p_MultiResult->resetMatrixToI();
		//this->MultiResult1515.resetMatrixToI();
		//this->MultiResult1010.resetMatrixToI();
	}
	else//�������װ��ľ����뵱ǰ��ʼ���ľ�����������ͬ������Ҫ�������ɳ˻��������
	{
		this->init(leftOp, rightOp);
	}
};


