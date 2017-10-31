/*
 * DynamicDoubleShiftQRIteration.cpp
 *
 *  Created on: 2017年5月18日
 *      Author: looke
 */

#include "DynamicDoubleShiftQRIteration.h"

DynamicDoubleShiftQRIteration::DynamicDoubleShiftQRIteration(BasicMatrix* p_intput_OpMatrix):dMultiplier(p_intput_OpMatrix,p_intput_OpMatrix),dTransposer(p_intput_OpMatrix),dHessenbergForm(p_intput_OpMatrix),dGivensTrans(),dHouseholderTrans()
{
	this->init(p_intput_OpMatrix);
};

void DynamicDoubleShiftQRIteration::init(BasicMatrix* p_intput_OpMatrix)
{

	//操作矩阵
	this->opMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(p_intput_OpMatrix);
	this->p_OpMatrix = &opMatrix;

	//Hessenberg矩阵
	this->opHessenbergMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opHessenbergMatrix.resetMatrixToI();
	this->p_OpHessenbergMatrix = &opHessenbergMatrix;

	//生成转换矩阵的向量
	this->transVectorForQStep = DynamicVector(3);
	this->p_TransVectorForQStep = &transVectorForQStep;

	this->transVectorForQ_LastStep = DynamicVector(2);
	this->p_TransVectorForQ_LastStep = &transVectorForQ_LastStep;

	//Q 矩阵 显式迭代 分步 Q用于右乘OP矩阵 nxn
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//QT 矩阵 显式迭代 分步 QT用于左乘OP矩阵 nxn
	this->QTMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Step = &QTMatrix_Implicit_Step;

	//Q 矩阵 显式迭代 总体 Q用于右乘OP矩阵 nxn
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//QT 矩阵 显式迭代 总体 QT用于左乘OP矩阵 nxn
	this->QTMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QTMatrix_Implicit_Total = &QTMatrix_Implicit_Total;

	//Qi 子矩阵 显式迭代 分步 Q用于右乘OP矩阵 3x3
	this->QSubMatrix_Implicit_Step = DynamicMatrix(3,3);
	this->p_QSubMatrix_Implicit_Step = &QSubMatrix_Implicit_Step;

	//QTi 子矩阵 显式迭代 分步 QT用于左乘OP矩阵 3x3
	this->QTSubMatrix_Implicit_Step = DynamicMatrix(3,3);
	this->p_QTSubMatrix_Implicit_Step = &QTSubMatrix_Implicit_Step;

	//Qn-1 子矩阵 显式迭代 分步 Q用于右乘OP矩阵 2x2
	this->QSubMatrix_Implicit_LastStep = DynamicMatrix(2,2);
	this->p_QSubMatrix_Implicit_LastStep = &QSubMatrix_Implicit_LastStep;

	//QTn-1 子矩阵 显式迭代 分步 Q用于右乘OP矩阵 2x2
	this->QTSubMatrix_Implicit_LastStep = DynamicMatrix(2,2);
	this->p_QTSubMatrix_Implicit_LastStep = &QTSubMatrix_Implicit_LastStep;

	//hessen格式化
	this->p_HessenbergForm = &dHessenbergForm;

	//Givens变换器
	this->p_GivensTrans = &dGivensTrans;

	//householder变换
	this->p_HouseholderTrans = &dHouseholderTrans;

	//乘法器
	this->p_Multiplier = &dMultiplier;

	//转置器
	this->p_Transposer = &dTransposer;

	//操作矩阵转换为Hessenberg矩阵
	this->generateHessenbergOpMatrix();
};

void DynamicDoubleShiftQRIteration::reload(BasicMatrix* p_intput_OpMatrix)
{
	if(this->p_OpMatrix->rowNum == p_intput_OpMatrix->rowNum && this->p_OpMatrix->columnNum == p_intput_OpMatrix->columnNum)
	{
		this->p_OpMatrix->copyMatrixElementNoCheck(p_intput_OpMatrix);
		this->p_OpHessenbergMatrix->resetMatrixToI();
		//操作矩阵转换为Hessenberg矩阵
		this->generateHessenbergOpMatrix();
	}
	else
	{
		this->init(p_intput_OpMatrix);
	}
};

