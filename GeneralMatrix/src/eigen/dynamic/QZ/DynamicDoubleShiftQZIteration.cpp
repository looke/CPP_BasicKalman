/*
 * DynamicDoubleShiftQZIteration.cpp
 *
 *  Created on: 2017��5��31��
 *      Author: looke
 */


#include "DynamicDoubleShiftQZIteration.h"

DynamicDoubleShiftQZIteration::DynamicDoubleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B):dMultiplier(p_intput_OpMatrix_A,p_intput_OpMatrix_A),dHessenbergTriangleFormular(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dHouseholderTrans(),ABInvCalc()
{
	this->init(p_intput_OpMatrix_A, p_intput_OpMatrix_B);
};


void DynamicDoubleShiftQZIteration::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	//�������� nxn
	this->OpMatrix_A = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_A.copyMatrixElementNoCheck(p_intput_OpMatrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;
	this->OpMatrix_B = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_B.copyMatrixElementNoCheck(p_intput_OpMatrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//Hessenberg���� nxn
	this->OpMatrix_Hessenberg = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg.resetMatrixToI();
	this->p_OpMatrix_Hessenberg = &OpMatrix_Hessenberg;
	//Triangle���� nxn
	this->OpMatrix_Triangle = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle.resetMatrixToI();
	this->p_OpMatrix_Triangle = &OpMatrix_Triangle;


	//���ڼ�����ʽ˫��QZ��������ת������Qi������---3ά
	this->TransVectorForQStep_3 = DynamicVector(3);
	this->p_TransVectorForQStep_3 = &TransVectorForQStep_3;
	//���ڼ�����ʽ˫��QZ��������ת������Qn-1������---2ά
	this->TransVectorForQStep_2 = DynamicVector(2);
	this->p_TransVectorForQStep_2 = &TransVectorForQStep_2;

	//���ڼ�����ʽ˫��QZ��������ת������Zi������---3ά
	this->TransVectorForZStep_3 = DynamicVector(3);
	this->p_TransVectorForZStep_3 = &TransVectorForZStep_3;
	//���ڼ�����ʽ˫��QZ��������ת������Zi������---2ά
	this->TransVectorForZStep_2 = DynamicVector(2);
	this->p_TransVectorForZStep_2 = &TransVectorForZStep_2;

	//Q ȫ�ߴ���� ��ʽ���� �ֲ� Q�������OP����  nxn
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Step.resetMatrixToI();
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//Z ȫ�ߴ���� ��ʽ���� �ֲ� Z�����ҳ�OP����  nxn
	this->ZMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Step.resetMatrixToI();
	this->p_ZMatrix_Implicit_Step = &ZMatrix_Implicit_Step;

	//Q ȫ�ߴ���� ��ʽ����  ����Q�������OP����  nxn
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Total.resetMatrixToI();
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//Z ȫ�ߴ���� ��ʽ���� ����Z�����ҳ�OP����  nxn
	this->ZMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Total.resetMatrixToI();
	this->p_ZMatrix_Implicit_Total = &ZMatrix_Implicit_Total;

	//Qi �Ӿ��� ��ʽ���� �ֲ� Qi�������OP���� 3x3
	this->QSubMatrix_Implicit_Step_3 = DynamicMatrix(3,3);
	this->QSubMatrix_Implicit_Step_3.resetMatrixToI();
	this->p_QSubMatrix_Implicit_Step_3 = &QSubMatrix_Implicit_Step_3;

	//Qi �Ӿ��� ��ʽ���� �ֲ� Qn-1�������OP���� 2x2
	this->QSubMatrix_Implicit_Step_2 = DynamicMatrix(2,2);
	this->QSubMatrix_Implicit_Step_2.resetMatrixToI();
	this->p_QSubMatrix_Implicit_Step_2 = &QSubMatrix_Implicit_Step_2;

	//Zi �Ӿ��� ��ʽ���� �ֲ� QTi�����ҳ�OP���� 3x3
	this->ZSubMatrix_Implicit_Step_3 = DynamicMatrix(3,3);
	this->ZSubMatrix_Implicit_Step_3.resetMatrixToI();
	this->p_ZSubMatrix_Implicit_Step_3 = &ZSubMatrix_Implicit_Step_3;

	//Zi �Ӿ��� ��ʽ���� �ֲ� QT�����ҳ�OP���� 2x2
	this->ZSubMatrix_Implicit_Step_2 = DynamicMatrix(2,2);
	this->ZSubMatrix_Implicit_Step_2.resetMatrixToI();
	this->p_ZSubMatrix_Implicit_Step_2 = &ZSubMatrix_Implicit_Step_2;

	//hessenberg-triangle��ʽ��
	this->p_HessenbergTriangleFormular = &dHessenbergTriangleFormular;
	//householder�任
	this->p_HouseholderTrans = &dHouseholderTrans;
	//�˷���
	this->p_Multiplier = &dMultiplier;
	//A*B^-1 Ԫ�ؼ�����
	this->p_ABInvCalc = &ABInvCalc;

	this->generateHessenTriangleOpMatrix();
};

void DynamicDoubleShiftQZIteration::reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	if(this->p_OpMatrix_A->rowNum == p_input_OpMatrix_A->rowNum && this->p_OpMatrix_A->columnNum == p_input_OpMatrix_A->columnNum
				&& this->p_OpMatrix_B->rowNum == p_input_OpMatrix_B->rowNum && this->p_OpMatrix_B->columnNum == p_input_OpMatrix_B->columnNum)
	{
		this->p_OpMatrix_A->copyMatrixElementNoCheck(p_input_OpMatrix_A);
		this->p_OpMatrix_B->copyMatrixElementNoCheck(p_input_OpMatrix_B);

		this->p_OpMatrix_Hessenberg->resetMatrixToI();
		this->p_OpMatrix_Triangle->resetMatrixToI();

		this->p_QMatrix_Implicit_Step->resetMatrixToI();
		this->p_ZMatrix_Implicit_Step->resetMatrixToI();

		this->p_QMatrix_Implicit_Total->resetMatrixToI();
		this->p_ZMatrix_Implicit_Total->resetMatrixToI();

		this->p_QSubMatrix_Implicit_Step_3->resetMatrixToI();
		this->p_QSubMatrix_Implicit_Step_2->resetMatrixToI();

		this->p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();
		this->p_ZSubMatrix_Implicit_Step_2->resetMatrixToI();

		this->generateHessenTriangleOpMatrix();
	}
	else
	{
		init(p_input_OpMatrix_A, p_input_OpMatrix_B);
	}
};
