/*
 * DynamicNormalEigenSolverForReal.cpp
 *
 *  Created on: 2017��5��23��
 *      Author: looke
 */

#include "DynamicNormalEigenSolverForReal.h"

DynamicNormalEigenSolverForReal::DynamicNormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix):dMultiplier(p_input_OpMatrix,p_input_OpMatrix),dHessenbergForm(p_input_OpMatrix),dDoubleShifeQR(p_input_OpMatrix),dSingleShifeQR(p_input_OpMatrix),HessenbergDeflation(),testMulti(p_input_OpMatrix,p_input_OpMatrix)
{
	this->init(p_input_OpMatrix);
};

void DynamicNormalEigenSolverForReal::init(BasicMatrix* p_input_OpMatrix)
{
	//ԭʼ��������
	this->OpMatrix = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->OpMatrix.copyMatrixElementNoCheck(p_input_OpMatrix);
	this->p_OpMatrix = &OpMatrix;

	//ԭʼ���������Ӧ������ֵ����
	this->EigenValueMatrix = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->EigenValueMatrix.resetMatrixToI();
	this->p_EigenValueMatrix = &EigenValueMatrix;

	//ԭʼ����Hessenberg����
	this->OpHessenbergMatrix = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->OpHessenbergMatrix.resetMatrixToI();
	this->p_OpHessenbergMatrix = &OpHessenbergMatrix;

	//ԭʼ����ĵ������任����
	this->QTMatrix_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QTMatrix_Iteration.resetMatrixToI();
	this->p_QTMatrix_Iteration = &QTMatrix_Iteration;

	this->QMatrix_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QMatrix_Iteration.resetMatrixToI();
	this->p_QMatrix_Iteration = &QMatrix_Iteration;

	//ԭʼ���������任����
	this->QTMatrix_Total = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QTMatrix_Total.resetMatrixToI();
	this->p_QTMatrix_Total = &QTMatrix_Total;

	this->QMatrix_Total = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QMatrix_Total.resetMatrixToI();
	this->p_QMatrix_Total = &QMatrix_Total;


	//�ѽ��׵� ����Hessenberg����
	this->OpHessenbergMatrix_deflated = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->OpHessenbergMatrix_deflated.resetMatrixToI();
	this->p_OpHessenbergMatrix_deflated = &OpHessenbergMatrix_deflated;

	//�ѽ��׾���ĵ������任����Q\QT
	this->QTMatrix_Deflated_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QTMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_QTMatrix_Deflated_Iteration = &QTMatrix_Deflated_Iteration;

	this->QMatrix_Deflated_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_QMatrix_Deflated_Iteration = &QMatrix_Deflated_Iteration;

	//���һ����ԶԽ���2x2�����Ĳ���
	this->LastStepMatrix_2x2 = DynamicMatrix(2,2);
	this->p_LastStepMatrix_2x2 = &LastStepMatrix_2x2;

	this->p_Multiplier = &dMultiplier;
	this->p_DoubleShifeQR = &dDoubleShifeQR;
	this->p_SingleShifeQR = &dSingleShifeQR;
	this->p_HessenbergForm = &dHessenbergForm;
	this->p_HessenbergDeflation = &HessenbergDeflation;

	//��������ת�þ������ʱ���Զ���
	this->testForTemp_nxn = DynamicMatrix(this->p_OpMatrix->rowNum, this->p_OpMatrix->columnNum);
	this->p_testForTemp_nxn = &testForTemp_nxn;
	this->p_testMulti = &testMulti;
};

void DynamicNormalEigenSolverForReal::reload(BasicMatrix* p_input_OpMatrix)
{
	if(this->p_OpMatrix->rowNum == p_input_OpMatrix->rowNum && this->p_OpMatrix->columnNum == p_input_OpMatrix->columnNum)
	{
		this->p_OpMatrix->copyMatrixElementNoCheck(p_input_OpMatrix);

		this->p_EigenValueMatrix->resetMatrixToI();
		this->p_OpHessenbergMatrix->resetMatrixToI();

		this->p_QTMatrix_Iteration->resetMatrixToI();
		this->p_QMatrix_Iteration->resetMatrixToI();

		this->p_QTMatrix_Total->resetMatrixToI();
		this->p_QMatrix_Total->resetMatrixToI();

		this->p_OpHessenbergMatrix_deflated->resizeMatrix(p_input_OpMatrix->rowNum,p_input_OpMatrix->columnNum);
		this->p_OpHessenbergMatrix_deflated->resetMatrixToI();

		this->p_QTMatrix_Deflated_Iteration->resizeMatrix(p_input_OpMatrix->rowNum,p_input_OpMatrix->columnNum);
		this->p_QTMatrix_Deflated_Iteration->resetMatrixToI();

		this->p_QMatrix_Deflated_Iteration->resizeMatrix(p_input_OpMatrix->rowNum,p_input_OpMatrix->columnNum);
		this->p_QMatrix_Deflated_Iteration->resetMatrixToI();

		this->p_LastStepMatrix_2x2->resetMatrixToI();
	}
	else
	{
		init(p_input_OpMatrix);
	}
};
