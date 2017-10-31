/*
 * DynamicGeneralizedEigenSolverForReal.cpp
 *
 *  Created on: 2017年6月2日
 *      Author: looke
 */

#include "DynamicGeneralizedEigenSolverForReal.h"

DynamicGeneralizedEigenSolverForReal::DynamicGeneralizedEigenSolverForReal(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B):dDoubleShifeQZ(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dSingleShifeQZ(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dQZTriangleZeroChasing(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dHessenbergDeflation(),dMultiplier(p_intput_OpMatrix_A,p_intput_OpMatrix_A),dHessenbergTriangleFormular(p_intput_OpMatrix_A,p_intput_OpMatrix_B),ABInvCalc(),testMulti(p_intput_OpMatrix_A,p_intput_OpMatrix_A)
{
	this->init(p_intput_OpMatrix_A, p_intput_OpMatrix_B);
};

void DynamicGeneralizedEigenSolverForReal::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	//原始操作矩阵
	this->OpMatrix_A = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_A.copyMatrixElementNoCheck(p_intput_OpMatrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;

	this->OpMatrix_B = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_B.copyMatrixElementNoCheck(p_intput_OpMatrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//原始操作Hessenberg矩阵
	this->OpMatrix_Hessenberg = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg.resetMatrixToI();
	this->p_OpMatrix_Hessenberg = &OpMatrix_Hessenberg;

	//原始操作Triangle矩阵
	this->OpMatrix_Triangle = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle.resetMatrixToI();
	this->p_OpMatrix_Triangle = &OpMatrix_Triangle;

	//原始矩阵的全维度单迭代变换矩阵
	this->QMatrix_Iteration = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Iteration.resetMatrixToI();
	this->p_QMatrix_Iteration = &QMatrix_Iteration;

	this->ZMatrix_Iteration = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Iteration.resetMatrixToI();
	this->p_ZMatrix_Iteration = &ZMatrix_Iteration;

	//原始矩阵的全维度总体变换矩阵
	this->QMatrix_Total = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Total.resetMatrixToI();
	this->p_QMatrix_Total = &QMatrix_Total;

	this->ZMatrix_Total = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Total.resetMatrixToI();
	this->p_ZMatrix_Total = &ZMatrix_Total;

	//已降阶的 操作Hessenberg矩阵
	this->OpMatrix_Hessenberg_deflated = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg_deflated.resetMatrixToI();
	this->p_OpMatrix_Hessenberg_deflated = &OpMatrix_Hessenberg_deflated;
	//已降阶的 操作Triangle矩阵
	this->OpMatrix_Triangle_deflated = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle_deflated.resetMatrixToI();
	this->p_OpMatrix_Triangle_deflated = &OpMatrix_Triangle_deflated;
	//已降阶矩阵的单迭代变换矩阵Q\Z
	this->QMatrix_Deflated_Iteration = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_QMatrix_Deflated_Iteration = &QMatrix_Deflated_Iteration;

	this->ZMatrix_Deflated_Iteration = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Deflated_Iteration.resetMatrixToI();
	this->p_ZMatrix_Deflated_Iteration = &ZMatrix_Deflated_Iteration;

	//最后一步针对对角线2x2矩阵块的操作
	this->LastStepMatrix_2x2_Hessenberg = DynamicMatrix(2,2);
	this->p_LastStepMatrix_2x2_Hessenberg = &LastStepMatrix_2x2_Hessenberg;
	this->LastStepMatrix_2x2_Triangle = DynamicMatrix(2,2);
	this->p_LastStepMatrix_2x2_Triangle = &LastStepMatrix_2x2_Triangle;

	//双重步QZ迭代器
	this->p_DoubleShifeQZ = &dDoubleShifeQZ;
	//单步QR迭代器
	this->p_SingleShifeQZ = &dSingleShifeQZ;
	//hessenberg-triangle格式化
	this->p_HessenbergTriangleFormular = &dHessenbergTriangleFormular;
	//乘法器
	this->p_Multiplier = &dMultiplier;
	//hessenberg降阶点查找器
	this->p_HessenbergDeflation = &dHessenbergDeflation;
	//QZ-triangle 0元移位
	this->p_QZTriangleZeroChasing = &dQZTriangleZeroChasing;
	//A*B^-1 元素计算器
	this->p_ABInvCalc = &ABInvCalc;

	//测试总体转置矩阵的临时测试对象
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
