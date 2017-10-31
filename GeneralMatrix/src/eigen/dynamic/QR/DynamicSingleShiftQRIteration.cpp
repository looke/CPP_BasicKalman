/*
 * DynamicSingelShiftQRIteration.cpp
 *
 *  Created on: 2017年5月13日
 *      Author: looke
 */

#include "..\eigen\dynamic\QR\DynamicSingleShiftQRIteration.h"

DynamicSingleShiftQRIteration::DynamicSingleShiftQRIteration(BasicMatrix* p_intput_OpMatrix):dMultiplier(p_intput_OpMatrix,p_intput_OpMatrix),dTransposer(p_intput_OpMatrix),dQRDecomp(p_intput_OpMatrix),dHessenbergForm(p_intput_OpMatrix),dGivensTrans()
{
	this->init(p_intput_OpMatrix);
};

void DynamicSingleShiftQRIteration::init(BasicMatrix* p_intput_OpMatrix)
{
	//操作矩阵
	this->opMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(p_intput_OpMatrix);
	this->p_OpMatrix = &opMatrix;

	//Hessenberg矩阵
	this->opHessenbergMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_OpHessenbergMatrix = &opHessenbergMatrix;

	//Q 矩阵 显式迭代
	this->QMatrix_Explicit = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Explicit = &QMatrix_Explicit;

	//Q 矩阵 显式迭代 分步 Q用于右乘OP矩阵
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//QT 矩阵 显式迭代 分步 QT用于左乘OP矩阵
	this->QTMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Step = &QTMatrix_Implicit_Step;

	//Q 矩阵 显式迭代 综合 Q用于右乘OP矩阵
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//QT 矩阵 显式迭代 综合 QT用于左乘OP矩阵
	this->QTMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Total = &QTMatrix_Implicit_Total;
	//QR分解
	this->p_QRDecomp = &dQRDecomp;

	//hessen格式化
	this->p_HessenbergForm = &dHessenbergForm;

	//Givens变换器
	this->p_GivensTrans = &dGivensTrans;

	//乘法器
	this->p_Multiplier = &dMultiplier;

	//转置器
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


