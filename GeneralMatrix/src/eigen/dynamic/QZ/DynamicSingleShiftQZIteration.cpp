/*
 * DynamicSingleShiftQZIteration.cpp
 *
 *  Created on: 2017年5月28日
 *      Author: looke
 */

#include "DynamicSingleShiftQZIteration.h"

DynamicSingleShiftQZIteration::DynamicSingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B):dMultiplier(p_intput_OpMatrix_A,p_intput_OpMatrix_A),dGivensTrans(),dQZTriangleZeroChasing(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dHessenbergTriangleFormular(p_intput_OpMatrix_A,p_intput_OpMatrix_B),ABInvCalc()
{
	this->init(p_intput_OpMatrix_A,p_intput_OpMatrix_B);
};


void DynamicSingleShiftQZIteration::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	//原始操作矩阵A
	this->OpMatrix_A = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_A.copyMatrixElementNoCheck(p_intput_OpMatrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;

	//原始操作矩阵B
	this->OpMatrix_B = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_B.copyMatrixElementNoCheck(p_intput_OpMatrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//Hessenberg 操作矩阵A
	this->OpMatrix_Hessenberg = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg.resetMatrixToI();
	this->p_OpMatrix_Hessenberg = &OpMatrix_Hessenberg;

	//Triangle 操作矩阵B
	this->OpMatrix_Triangle = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle.resetMatrixToI();
	this->p_OpMatrix_Triangle = &OpMatrix_Triangle;

	//Z 矩阵 隐式迭代 分步 Z用于右乘OP矩阵
	this->ZMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Step.resetMatrixToI();
	this->p_ZMatrix_Implicit_Step = &ZMatrix_Implicit_Step;

	//Q 矩阵 隐式迭代 分步 Q用于左乘OP矩阵
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Step.resetMatrixToI();
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//Z 矩阵 隐式迭代 综合 Z用于右乘OP矩阵
	this->ZMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Total.resetMatrixToI();
	this->p_ZMatrix_Implicit_Total = &ZMatrix_Implicit_Total;

	//Q 矩阵 隐式迭代 综合 Q用于左乘OP矩阵
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Total.resetMatrixToI();
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//hessenberg-triangle格式化
	this->p_HessenbergTriangleFormular = &dHessenbergTriangleFormular;

	//QZ-triangle 0元移位
	//this->p_QZTriangleZeroChasing = &dQZTriangleZeroChasing;

	//Givens变换器
	this->p_GivensTrans = &dGivensTrans;

	//乘法器
	this->p_Multiplier =  &dMultiplier;

	//A*B^-1 元素计算器
	this->p_ABInvCalc = &ABInvCalc;
	//H-T格式化
	this->generateHessenTriangleOpMatrix();
};

void DynamicSingleShiftQZIteration::reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	if(this->p_OpMatrix_A->rowNum == p_intput_OpMatrix_A->rowNum && this->p_OpMatrix_A->columnNum == p_intput_OpMatrix_A->columnNum
			&& this->p_OpMatrix_B->rowNum == p_intput_OpMatrix_B->rowNum && this->p_OpMatrix_B->columnNum == p_intput_OpMatrix_B->columnNum)
	{
		this->p_OpMatrix_A->copyMatrixElementNoCheck(p_intput_OpMatrix_A);
		this->p_OpMatrix_B->copyMatrixElementNoCheck(p_intput_OpMatrix_B);

		this->p_OpMatrix_Hessenberg->resetMatrixToI();
		this->p_OpMatrix_Triangle->resetMatrixToI();

		this->p_ZMatrix_Implicit_Step->resetMatrixToI();
		this->p_QMatrix_Implicit_Step->resetMatrixToI();

		this->p_ZMatrix_Implicit_Total->resetMatrixToI();
		this->p_QMatrix_Implicit_Total->resetMatrixToI();
		//H-T格式化
		this->generateHessenTriangleOpMatrix();
	}
	else
	{
		this->init(p_intput_OpMatrix_A,p_intput_OpMatrix_B);
	}

};
