/*
 * DynamicSingelShiftQRIteration.cpp
 *
 *  Created on: 2017��5��13��
 *      Author: looke
 */

#include "..\eigen\dynamic\QR\DynamicSingleShiftQRIteration.h"

DynamicSingleShiftQRIteration::DynamicSingleShiftQRIteration(BasicMatrix* p_intput_OpMatrix):dMultiplier(p_intput_OpMatrix,p_intput_OpMatrix),dTransposer(p_intput_OpMatrix),dQRDecomp(p_intput_OpMatrix),dHessenbergForm(p_intput_OpMatrix),dGivensTrans()
{
	this->init(p_intput_OpMatrix);
};

void DynamicSingleShiftQRIteration::init(BasicMatrix* p_intput_OpMatrix)
{
	//��������
	this->opMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(p_intput_OpMatrix);
	this->p_OpMatrix = &opMatrix;

	//Hessenberg����
	this->opHessenbergMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_OpHessenbergMatrix = &opHessenbergMatrix;

	//Q ���� ��ʽ����
	this->QMatrix_Explicit = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Explicit = &QMatrix_Explicit;

	//Q ���� ��ʽ���� �ֲ� Q�����ҳ�OP����
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//QT ���� ��ʽ���� �ֲ� QT�������OP����
	this->QTMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Step = &QTMatrix_Implicit_Step;

	//Q ���� ��ʽ���� �ۺ� Q�����ҳ�OP����
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//QT ���� ��ʽ���� �ۺ� QT�������OP����
	this->QTMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Total = &QTMatrix_Implicit_Total;
	//QR�ֽ�
	this->p_QRDecomp = &dQRDecomp;

	//hessen��ʽ��
	this->p_HessenbergForm = &dHessenbergForm;

	//Givens�任��
	this->p_GivensTrans = &dGivensTrans;

	//�˷���
	this->p_Multiplier = &dMultiplier;

	//ת����
	this->p_Transposer = &dTransposer;

	this->generateHessenbergOpMatrix();

};

void DynamicSingleShiftQRIteration::reload(BasicMatrix* p_intput_OpMatrix)
{
	if(this->p_OpMatrix->rowNum == p_intput_OpMatrix->rowNum && this->p_OpMatrix->columnNum == p_intput_OpMatrix->columnNum)
	{
		this->p_OpMatrix->copyMatrixElementNoCheck(p_intput_OpMatrix);

		this->p_OpHessenbergMatrix->resetMatrixToI();
		this->p_QMatrix_Explicit->resetMatrixToI();
		this->p_QMatrix_Implicit_Step->resetMatrixToI();
		this->p_QTMatrix_Implicit_Step->resetMatrixToI();

		this->generateHessenbergOpMatrix();
	}
	else
	{
		this->init(p_intput_OpMatrix);
	}
};


