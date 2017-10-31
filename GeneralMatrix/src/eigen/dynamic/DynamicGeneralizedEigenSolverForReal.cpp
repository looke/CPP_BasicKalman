/*
 * DynamicGeneralizedEigenSolverForReal.cpp
 *
 *  Created on: 2017��6��2��
 *      Author: looke
 */

#include "DynamicGeneralizedEigenSolverForReal.h"

DynamicGeneralizedEigenSolverForReal::DynamicGeneralizedEigenSolverForReal(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B):dDoubleShifeQZ(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dSingleShifeQZ(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dQZTriangleZeroChasing(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dHessenbergDeflation(),dMultiplier(p_intput_OpMatrix_A,p_intput_OpMatrix_A),dHessenbergTriangleFormular(p_intput_OpMatrix_A,p_intput_OpMatrix_B),ABInvCalc(),testMulti(p_intput_OpMatrix_A,p_intput_OpMatrix_A)
{
	this->init(p_intput_OpMatrix_A, p_intput_OpMatrix_B);
};

void DynamicGeneralizedEigenSolverForReal::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	//ԭʼ��������
	this->OpMatrix_A = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_A.copyMatrixElementNoCheck(p_intput_OpMatrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;

	this->OpMatrix_B = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_B.copyMatrixElementNoCheck(p_intput_OpMatrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//ԭʼ����Hessenberg����
	this->OpMatrix_Hessenberg = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg.resetMatrixToI();
	this->p_OpMatrix_Hessenberg = &OpMatrix_Hessenberg;

	//ԭʼ����Triangle����
	this->OpMatrix_Triangle = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle.resetMatrixToI();
	this->p_OpMatrix_Triangle = &OpMatrix_Triangle;

	//ԭʼ�����ȫά�ȵ������任����
	this->QMatrix_Iteration = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Iteration.resetMatrixToI();
	this->p_QMatrix_Iteration = &QMatrix_Iteration;

	this->ZMatrix_Iteration = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Iteration.resetMatrixToI();
	this->p_ZMatrix_Iteration = &ZMatrix_Iteration;

	//ԭʼ�����ȫά������任����
	this->QMatrix_Total = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Total.resetMatrixToI();
	this->p_QMatrix_Total = &QMatrix_Total;

	this->ZMatrix_Total = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Total.resetMatrixToI();
	this->p_ZMatrix_Total = &ZMatrix_Total;

	//�ѽ��׵� ����Hessenberg����
	this->OpMatrix_Hessenberg_deflated = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg_deflated.resetMatrixToI();
	this->p_OpMatrix_Hessenberg_deflated = &OpMatrix_Hessenberg_deflated;
	//�ѽ��׵� ����Triangle����
	this->OpMatrix_Triangle_deflated = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle_deflated.resetMatrixToI();
	this->p_OpMatrix_Triangle_deflated = &OpMatrix_Triangle_deflated;
	//�ѽ��׾���ĵ������任����Q\Z
	this->QMatrix_Deflated_Iteration = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_QMatrix_Deflated_Iteration = &QMatrix_Deflated_Iteration;

	this->ZMatrix_Deflated_Iteration = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_ZMatrix_Deflated_Iteration = &ZMatrix_Deflated_Iteration;

	//���һ����ԶԽ���2x2�����Ĳ���
	this->LastStepMatrix_2x2_Hessenberg = DynamicMatrix(2,2);
	this->p_LastStepMatrix_2x2_Hessenberg = &LastStepMatrix_2x2_Hessenberg;
	this->LastStepMatrix_2x2_Triangle = DynamicMatrix(2,2);
	this->p_LastStepMatrix_2x2_Triangle = &LastStepMatrix_2x2_Triangle;

	//˫�ز�QZ������
	this->p_DoubleShifeQZ = &dDoubleShifeQZ;
	//����QR������
	this->p_SingleShifeQZ = &dSingleShifeQZ;
	//hessenberg-triangle��ʽ��
	this->p_HessenbergTriangleFormular = &dHessenbergTriangleFormular;
	//�˷���
	this->p_Multiplier = &dMultiplier;
	//hessenberg���׵������
	this->p_HessenbergDeflation = &dHessenbergDeflation;
	//QZ-triangle 0Ԫ��λ
	this->p_QZTriangleZeroChasing = &dQZTriangleZeroChasing;
	//A*B^-1 Ԫ�ؼ�����
	this->p_ABInvCalc = &ABInvCalc;

	//��������ת�þ������ʱ���Զ���
	this->testForTemp_A_nxn = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->p_testForTemp_A_nxn = &testForTemp_A_nxn;
	this->testForTemp_B_nxn = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->p_testForTemp_B_nxn = &testForTemp_B_nxn;

	this->p_testMulti = &testMulti;
};

void DynamicGeneralizedEigenSolverForReal::reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	if(this->p_OpMatrix_A->rowNum == p_input_OpMatrix_A->rowNum && this->p_OpMatrix_A->columnNum == p_input_OpMatrix_A->columnNum
				&& this->p_OpMatrix_B->rowNum == p_input_OpMatrix_B->rowNum && this->p_OpMatrix_B->columnNum == p_input_OpMatrix_B->columnNum)
	{
		this->p_OpMatrix_A->copyMatrixElementNoCheck(p_input_OpMatrix_A);
		this->p_OpMatrix_B->copyMatrixElementNoCheck(p_input_OpMatrix_B);

		this->p_OpMatrix_Hessenberg->resetMatrixToI();
		this->p_OpMatrix_Triangle->resetMatrixToI();

		this->p_QMatrix_Iteration->resetMatrixToI();
		this->p_ZMatrix_Iteration->resetMatrixToI();

		this->p_QMatrix_Total->resetMatrixToI();
		this->p_ZMatrix_Total->resetMatrixToI();

		this->p_OpMatrix_Hessenberg_deflated->resizeMatrix(p_input_OpMatrix_A->rowNum,p_input_OpMatrix_A->columnNum);
		this->p_OpMatrix_Hessenberg_deflated->resetMatrixToI();

		this->p_OpMatrix_Triangle_deflated->resizeMatrix(p_input_OpMatrix_B->rowNum,p_input_OpMatrix_B->columnNum);
		this->p_OpMatrix_Triangle_deflated->resetMatrixToI();

		this->p_QMatrix_Deflated_Iteration->resizeMatrix(p_input_OpMatrix_A->rowNum,p_input_OpMatrix_A->columnNum);
		this->p_QMatrix_Deflated_Iteration->resetMatrixToI();

		this->p_ZMatrix_Deflated_Iteration->resizeMatrix(p_input_OpMatrix_B->rowNum,p_input_OpMatrix_B->columnNum);
		this->p_ZMatrix_Deflated_Iteration->resetMatrixToI();
	}
	else
	{
		init(p_input_OpMatrix_A, p_input_OpMatrix_B);
	}
};
