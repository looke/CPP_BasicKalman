/*
 * DynamicQRDecomposition.cpp
 *
 *  Created on: 2017��4��27��
 *      Author: looke
 */

#include "DynamicQRDecomposition.h"

//DynamicQRDecomposition::DynamicQRDecomposition()
//{};

DynamicQRDecomposition::DynamicQRDecomposition(BasicMatrix* input_Matrix):Multiplier(input_Matrix,input_Matrix),HouseholderTrans()
{
	this->init(input_Matrix);
};


void DynamicQRDecomposition::init(BasicMatrix* input_Matrix)
{
	//��������
	this->OpMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->OpMatrix.copyMatrixElementNoCheck(input_Matrix);
	this->p_OpMatrix = &OpMatrix;

	//householder����ÿ�ε���ʹ��
	this->householderMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->p_householderMatrix = &householderMatrix;

	//Q����
	this->QMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->p_QMatrix = &QMatrix;

	//Q�����ת��(�����)
	this->QTMatrix = DynamicMatrix(input_Matrix->rowNum, input_Matrix->columnNum);
	this->p_QTMatrix = &QTMatrix;

	//�˷���
	this->p_Multiplier = &this->Multiplier;

	//Householder�任��
	this->p_HouseholderTrans = &this->HouseholderTrans;
};

/*
 * ���¼����µĲ�������
 */
void DynamicQRDecomposition::reload(BasicMatrix* input_Matrix)
{
	//���¼��صľ�����ԭ������������ͬ
	if(OpMatrix.rowNum == input_Matrix->rowNum && OpMatrix.columnNum == input_Matrix->columnNum)
	{
		this->OpMatrix.copyMatrixElementNoCheck(input_Matrix);
		this->householderMatrix.resetMatrixToI();
		this->QMatrix.resetMatrixToI();
		this->QTMatrix.resetMatrixToI();
	}
	else
	{
		this->init(input_Matrix);
	}

};
