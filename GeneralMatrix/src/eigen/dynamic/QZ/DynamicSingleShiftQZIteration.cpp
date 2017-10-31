/*
 * DynamicSingleShiftQZIteration.cpp
 *
 *  Created on: 2017��5��28��
 *      Author: looke
 */

#include "DynamicSingleShiftQZIteration.h"

DynamicSingleShiftQZIteration::DynamicSingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B):dMultiplier(p_intput_OpMatrix_A,p_intput_OpMatrix_A),dGivensTrans(),dQZTriangleZeroChasing(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dHessenbergTriangleFormular(p_intput_OpMatrix_A,p_intput_OpMatrix_B),ABInvCalc()
{
	this->init(p_intput_OpMatrix_A,p_intput_OpMatrix_B);
};


void DynamicSingleShiftQZIteration::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	//ԭʼ��������A
	this->OpMatrix_A = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_A.copyMatrixElementNoCheck(p_intput_OpMatrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;

	//ԭʼ��������B
	this->OpMatrix_B = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_B.copyMatrixElementNoCheck(p_intput_OpMatrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//Hessenberg ��������A
	this->OpMatrix_Hessenberg = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg.resetMatrixToI();
	this->p_OpMatrix_Hessenberg = &OpMatrix_Hessenberg;

	//Triangle ��������B
	this->OpMatrix_Triangle = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle.resetMatrixToI();
	this->p_OpMatrix_Triangle = &OpMatrix_Triangle;

	//Z ���� ��ʽ���� �ֲ� Z�����ҳ�OP����
	this->ZMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Step.resetMatrixToI();
	this->p_ZMatrix_Implicit_Step = &ZMatrix_Implicit_Step;

	//Q ���� ��ʽ���� �ֲ� Q�������OP����
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Step.resetMatrixToI();
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//Z ���� ��ʽ���� �ۺ� Z�����ҳ�OP����
	this->ZMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Total.resetMatrixToI();
	this->p_ZMatrix_Implicit_Total = &ZMatrix_Implicit_Total;

	//Q ���� ��ʽ���� �ۺ� Q�������OP����
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Total.resetMatrixToI();
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//hessenberg-triangle��ʽ��
	this->p_HessenbergTriangleFormular = &dHessenbergTriangleFormular;

	//QZ-triangle 0Ԫ��λ
	//this->p_QZTriangleZeroChasing = &dQZTriangleZeroChasing;

	//Givens�任��
	this->p_GivensTrans = &dGivensTrans;

	//�˷���
	this->p_Multiplier =  &dMultiplier;

	//A*B^-1 Ԫ�ؼ�����
	this->p_ABInvCalc = &ABInvCalc;
	//H-T��ʽ��
	this->generateHessenTriangleOpMatrix();
};

void DynamicSingleShiftQZIteration::reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	if(this->p_OpMatrix_A->rowNum == p_intput_OpMatrix_A->rowNum && this->p_OpMatrix_A->columnNum == p_intput_OpMatrix_A->columnNum
			&& this->p_OpMatrix_B->rowNum == p_intput_OpMatrix_B->rowNum && this->p_OpMatrix_B->columnNum == p_intput_OpMatrix_B->columnNum)
	{
		this->p_OpMatrix_A->copyMatrixElementNoCheck(p_intput_OpMatrix_A);
		this->p_OpMatrix_B->copyMatrixElementNoCheck(p_intput_OpMatrix_B);

		this->p_OpMatrix_Hessenberg->resetMatrixToI();
		this->p_OpMatrix_Triangle->resetMatrixToI();

		this->p_ZMatrix_Implicit_Step->resetMatrixToI();
		this->p_QMatrix_Implicit_Step->resetMatrixToI();

		this->p_ZMatrix_Implicit_Total->resetMatrixToI();
		this->p_QMatrix_Implicit_Total->resetMatrixToI();
		//H-T��ʽ��
		this->generateHessenTriangleOpMatrix();
	}
	else
	{
		this->init(p_intput_OpMatrix_A,p_intput_OpMatrix_B);
	}

};
