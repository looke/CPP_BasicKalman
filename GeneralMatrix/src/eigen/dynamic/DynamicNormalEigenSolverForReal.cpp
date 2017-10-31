/*
 * DynamicNormalEigenSolverForReal.cpp
 *
 *  Created on: 2017年5月23日
 *      Author: looke
 */

#include "DynamicNormalEigenSolverForReal.h"

DynamicNormalEigenSolverForReal::DynamicNormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix):dMultiplier(p_input_OpMatrix,p_input_OpMatrix),dHessenbergForm(p_input_OpMatrix),dDoubleShifeQR(p_input_OpMatrix),dSingleShifeQR(p_input_OpMatrix),HessenbergDeflation(),testMulti(p_input_OpMatrix,p_input_OpMatrix)
{
	this->init(p_input_OpMatrix);
};

void DynamicNormalEigenSolverForReal::init(BasicMatrix* p_input_OpMatrix)
{
	//原始操作矩阵
	this->OpMatrix = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->OpMatrix.copyMatrixElementNoCheck(p_input_OpMatrix);
	this->p_OpMatrix = &OpMatrix;

	//原始操作矩阵对应的特征值矩阵
	this->EigenValueMatrix = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->EigenValueMatrix.resetMatrixToI();
	this->p_EigenValueMatrix = &EigenValueMatrix;

	//原始操作Hessenberg矩阵
	this->OpHessenbergMatrix = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->OpHessenbergMatrix.resetMatrixToI();
	this->p_OpHessenbergMatrix = &OpHessenbergMatrix;

	//原始矩阵的单迭代变换矩阵
	this->QTMatrix_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QTMatrix_Iteration.resetMatrixToI();
	this->p_QTMatrix_Iteration = &QTMatrix_Iteration;

	this->QMatrix_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QMatrix_Iteration.resetMatrixToI();
	this->p_QMatrix_Iteration = &QMatrix_Iteration;

	//原始矩阵的总体变换矩阵
	this->QTMatrix_Total = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QTMatrix_Total.resetMatrixToI();
	this->p_QTMatrix_Total = &QTMatrix_Total;

	this->QMatrix_Total = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QMatrix_Total.resetMatrixToI();
	this->p_QMatrix_Total = &QMatrix_Total;


	//已降阶的 操作Hessenberg矩阵
	this->OpHessenbergMatrix_deflated = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->OpHessenbergMatrix_deflated.resetMatrixToI();
	this->p_OpHessenbergMatrix_deflated = &OpHessenbergMatrix_deflated;

	//已降阶矩阵的单迭代变换矩阵Q\QT
	this->QTMatrix_Deflated_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QTMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_QTMatrix_Deflated_Iteration = &QTMatrix_Deflated_Iteration;

	this->QMatrix_Deflated_Iteration = DynamicMatrix(p_input_OpMatrix->rowNum, p_input_OpMatrix->columnNum);
	this->QMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_QMatrix_Deflated_Iteration = &QMatrix_Deflated_Iteration;

	//最后一步针对对角线2x2矩阵块的操作
	this->LastStepMatrix_2x2 = DynamicMatrix(2,2);
	this->p_LastStepMatrix_2x2 = &LastStepMatrix_2x2;

	this->p_Multiplier = &dMultiplier;
	this->p_DoubleShifeQR = &dDoubleShifeQR;
	this->p_SingleShifeQR = &dSingleShifeQR;
	this->p_HessenbergForm = &dHessenbergForm;
	this->p_HessenbergDeflation = &HessenbergDeflation;

	//测试总体转置矩阵的临时测试对象
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
