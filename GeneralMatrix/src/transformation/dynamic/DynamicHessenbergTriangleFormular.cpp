/*
 * DynamicHessenbergTriangleFormular.cpp
 *
 *  Created on: 2017年4月28日
 *      Author: looke
 */

#include "DynamicHessenbergTriangleFormular.h"

DynamicHessenbergTriangleFormular::DynamicHessenbergTriangleFormular(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B):dMultiplier(input_Matrix_A,input_Matrix_A),dGivensTrans(),dQRDecomp(input_Matrix_B)
{
	this->init(input_Matrix_A, input_Matrix_B);
};

void DynamicHessenbergTriangleFormular::init(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B)
{
	this->OpMatrix_A = DynamicMatrix(input_Matrix_A->rowNum, input_Matrix_A->columnNum);
	OpMatrix_A.copyMatrixElementNoCheck(input_Matrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;

	this->OpMatrix_B = DynamicMatrix(input_Matrix_B->rowNum, input_Matrix_B->columnNum);
	OpMatrix_B.copyMatrixElementNoCheck(input_Matrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//Hessenberg方阵A
	this->OpHessenbergMatrix_A = DynamicMatrix(input_Matrix_A->rowNum, input_Matrix_A->columnNum);
	OpHessenbergMatrix_A.resetMatrixToI();
	this->p_OpHessenbergMatrix_A = &OpHessenbergMatrix_A;

	//上三角方阵B
	this->OpTriangleMatrix_B = DynamicMatrix(input_Matrix_B->rowNum, input_Matrix_B->columnNum);
	OpTriangleMatrix_B.resetMatrixToI();
	this->p_OpTriangleMatrix_B = &OpTriangleMatrix_B;

	this->QMatrix_Total = DynamicMatrix(input_Matrix_A->rowNum, input_Matrix_A->columnNum);
	QMatrix_Total.resetMatrixToI();
	this->p_QMatrix_Total = &QMatrix_Total;

	this->ZMatrix_Total = DynamicMatrix(input_Matrix_B->rowNum, input_Matrix_B->columnNum);;
	ZMatrix_Total.resetMatrixToI();
	this->p_ZMatrix_Total = &ZMatrix_Total;

	this->QMatrix_Step = DynamicMatrix(input_Matrix_A->rowNum, input_Matrix_A->columnNum);
	QMatrix_Step.resetMatrixToI();
	this->p_QMatrix_Step = &QMatrix_Step;

	this->ZMatrix_Step = DynamicMatrix(input_Matrix_B->rowNum, input_Matrix_B->columnNum);;
	ZMatrix_Step.resetMatrixToI();
	this->p_ZMatrix_Step = &ZMatrix_Step;

	this->p_Multiplier = &this->dMultiplier;
	this->p_GivensTrans = &this->dGivensTrans;
	this->p_QRDecomp = &this->dQRDecomp;
};

void DynamicHessenbergTriangleFormular::reload(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B)
{
	if(this->OpMatrix_A.rowNum == input_Matrix_A->rowNum && this->OpMatrix_A.columnNum == input_Matrix_A->columnNum)
	{
		OpMatrix_A.copyMatrixElementNoCheck(input_Matrix_A);
		OpMatrix_B.copyMatrixElementNoCheck(input_Matrix_B);
		QMatrix_Total.resetMatrixToI();
		ZMatrix_Total.resetMatrixToI();
	}
	else
	{
		this->init(input_Matrix_A, input_Matrix_B);
	}
};
