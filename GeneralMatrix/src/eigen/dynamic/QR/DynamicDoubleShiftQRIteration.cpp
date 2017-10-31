/*
 * DynamicDoubleShiftQRIteration.cpp
 *
 *  Created on: 2017��5��18��
 *      Author: looke
 */

#include "DynamicDoubleShiftQRIteration.h"

DynamicDoubleShiftQRIteration::DynamicDoubleShiftQRIteration(BasicMatrix* p_intput_OpMatrix):dMultiplier(p_intput_OpMatrix,p_intput_OpMatrix),dTransposer(p_intput_OpMatrix),dHessenbergForm(p_intput_OpMatrix),dGivensTrans(),dHouseholderTrans()
{
	this->init(p_intput_OpMatrix);
};

void DynamicDoubleShiftQRIteration::init(BasicMatrix* p_intput_OpMatrix)
{

	//��������
	this->opMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(p_intput_OpMatrix);
	this->p_OpMatrix = &opMatrix;

	//Hessenberg����
	this->opHessenbergMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opHessenbergMatrix.resetMatrixToI();
	this->p_OpHessenbergMatrix = &opHessenbergMatrix;

	//����ת�����������
	this->transVectorForQStep = DynamicVector(3);
	this->p_TransVectorForQStep = &transVectorForQStep;

	this->transVectorForQ_LastStep = DynamicVector(2);
	this->p_TransVectorForQ_LastStep = &transVectorForQ_LastStep;

	//Q ���� ��ʽ���� �ֲ� Q�����ҳ�OP���� nxn
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//QT ���� ��ʽ���� �ֲ� QT�������OP���� nxn
	this->QTMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Step = &QTMatrix_Implicit_Step;

	//Q ���� ��ʽ���� ���� Q�����ҳ�OP���� nxn
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//QT ���� ��ʽ���� ���� QT�������OP���� nxn
	this->QTMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Total = &QTMatrix_Implicit_Total;

	//Qi �Ӿ��� ��ʽ���� �ֲ� Q�����ҳ�OP���� 3x3
	this->QSubMatrix_Implicit_Step = DynamicMatrix(3,3);
	this->p_QSubMatrix_Implicit_Step = &QSubMatrix_Implicit_Step;

	//QTi �Ӿ��� ��ʽ���� �ֲ� QT�������OP���� 3x3
	this->QTSubMatrix_Implicit_Step = DynamicMatrix(3,3);
	this->p_QTSubMatrix_Implicit_Step = &QTSubMatrix_Implicit_Step;

	//Qn-1 �Ӿ��� ��ʽ���� �ֲ� Q�����ҳ�OP���� 2x2
	this->QSubMatrix_Implicit_LastStep = DynamicMatrix(2,2);
	this->p_QSubMatrix_Implicit_LastStep = &QSubMatrix_Implicit_LastStep;

	//QTn-1 �Ӿ��� ��ʽ���� �ֲ� Q�����ҳ�OP���� 2x2
	this->QTSubMatrix_Implicit_LastStep = DynamicMatrix(2,2);
	this->p_QTSubMatrix_Implicit_LastStep = &QTSubMatrix_Implicit_LastStep;

	//hessen��ʽ��
	this->p_HessenbergForm = &dHessenbergForm;

	//Givens�任��
	this->p_GivensTrans = &dGivensTrans;

	//householder�任
	this->p_HouseholderTrans = &dHouseholderTrans;

	//�˷���
	this->p_Multiplier = &dMultiplier;

	//ת����
	this->p_Transposer = &dTransposer;

	//��������ת��ΪHessenberg����
	this->generateHessenbergOpMatrix();
};

void DynamicDoubleShiftQRIteration::reload(BasicMatrix* p_intput_OpMatrix)
{
	if(this->p_OpMatrix->rowNum == p_intput_OpMatrix->rowNum && this->p_OpMatrix->columnNum == p_intput_OpMatrix->columnNum)
	{
		this->p_OpMatrix->copyMatrixElementNoCheck(p_intput_OpMatrix);
		this->p_OpHessenbergMatrix->resetMatrixToI();
		//��������ת��ΪHessenberg����
		this->generateHessenbergOpMatrix();
	}
	else
	{
		this->init(p_intput_OpMatrix);
	}
};

