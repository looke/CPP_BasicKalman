/*
 * DynamicDoubleShiftQZIteration.cpp
 *
 *  Created on: 2017年5月31日
 *      Author: looke
 */


#include "DynamicDoubleShiftQZIteration.h"

DynamicDoubleShiftQZIteration::DynamicDoubleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B):dMultiplier(p_intput_OpMatrix_A,p_intput_OpMatrix_A),dHessenbergTriangleFormular(p_intput_OpMatrix_A,p_intput_OpMatrix_B),dHouseholderTrans(),ABInvCalc()
{
	this->init(p_intput_OpMatrix_A, p_intput_OpMatrix_B);
};


void DynamicDoubleShiftQZIteration::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	//操作矩阵 nxn
	this->OpMatrix_A = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_A.copyMatrixElementNoCheck(p_intput_OpMatrix_A);
	this->p_OpMatrix_A = &OpMatrix_A;
	this->OpMatrix_B = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_B.copyMatrixElementNoCheck(p_intput_OpMatrix_B);
	this->p_OpMatrix_B = &OpMatrix_B;

	//Hessenberg矩阵 nxn
	this->OpMatrix_Hessenberg = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->OpMatrix_Hessenberg.resetMatrixToI();
	this->p_OpMatrix_Hessenberg = &OpMatrix_Hessenberg;
	//Triangle矩阵 nxn
	this->OpMatrix_Triangle = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->OpMatrix_Triangle.resetMatrixToI();
	this->p_OpMatrix_Triangle = &OpMatrix_Triangle;


	//用于计算隐式双步QZ跌代单步转换矩阵Qi的向量---3维
	this->TransVectorForQStep_3 = DynamicVector(3);
	this->p_TransVectorForQStep_3 = &TransVectorForQStep_3;
	//用于计算隐式双步QZ跌代单步转换矩阵Qn-1的向量---2维
	this->TransVectorForQStep_2 = DynamicVector(2);
	this->p_TransVectorForQStep_2 = &TransVectorForQStep_2;

	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---3维
	this->TransVectorForZStep_3 = DynamicVector(3);
	this->p_TransVectorForZStep_3 = &TransVectorForZStep_3;
	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---2维
	this->TransVectorForZStep_2 = DynamicVector(2);
	this->p_TransVectorForZStep_2 = &TransVectorForZStep_2;

	//Q 全尺寸矩阵 隐式迭代 分步 Q用于左乘OP矩阵  nxn
	this->QMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Step.resetMatrixToI();
	this->p_QMatrix_Implicit_Step = &QMatrix_Implicit_Step;

	//Z 全尺寸矩阵 隐式迭代 分步 Z用于右乘OP矩阵  nxn
	this->ZMatrix_Implicit_Step = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Step.resetMatrixToI();
	this->p_ZMatrix_Implicit_Step = &ZMatrix_Implicit_Step;

	//Q 全尺寸矩阵 隐式迭代  总体Q用于左乘OP矩阵  nxn
	this->QMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_A->rowNum, p_intput_OpMatrix_A->columnNum);
	this->QMatrix_Implicit_Total.resetMatrixToI();
	this->p_QMatrix_Implicit_Total = &QMatrix_Implicit_Total;

	//Z 全尺寸矩阵 隐式迭代 总体Z用于右乘OP矩阵  nxn
	this->ZMatrix_Implicit_Total = DynamicMatrix(p_intput_OpMatrix_B->rowNum, p_intput_OpMatrix_B->columnNum);
	this->ZMatrix_Implicit_Total.resetMatrixToI();
	this->p_ZMatrix_Implicit_Total = &ZMatrix_Implicit_Total;

	//Qi 子矩阵 显式迭代 分步 Qi用于左乘OP矩阵 3x3
	this->QSubMatrix_Implicit_Step_3 = DynamicMatrix(3,3);
	this->QSubMatrix_Implicit_Step_3.resetMatrixToI();
	this->p_QSubMatrix_Implicit_Step_3 = &QSubMatrix_Implicit_Step_3;

	//Qi 子矩阵 显式迭代 分步 Qn-1用于左乘OP矩阵 2x2
	this->QSubMatrix_Implicit_Step_2 = DynamicMatrix(2,2);
	this->QSubMatrix_Implicit_Step_2.resetMatrixToI();
	this->p_QSubMatrix_Implicit_Step_2 = &QSubMatrix_Implicit_Step_2;

	//Zi 子矩阵 显式迭代 分步 QTi用于右乘OP矩阵 3x3
	this->ZSubMatrix_Implicit_Step_3 = DynamicMatrix(3,3);
	this->ZSubMatrix_Implicit_Step_3.resetMatrixToI();
	this->p_ZSubMatrix_Implicit_Step_3 = &ZSubMatrix_Implicit_Step_3;

	//Zi 子矩阵 显式迭代 分步 QT用于右乘OP矩阵 2x2
	this->ZSubMatrix_Implicit_Step_2 = DynamicMatrix(2,2);
	this->ZSubMatrix_Implicit_Step_2.resetMatrixToI();
	this->p_ZSubMatrix_Implicit_Step_2 = &ZSubMatrix_Implicit_Step_2;

	//hessenberg-triangle格式化
	this->p_HessenbergTriangleFormular = &dHessenbergTriangleFormular;
	//householder变换
	this->p_HouseholderTrans = &dHouseholderTrans;
	//乘法器
	this->p_Multiplier = &dMultiplier;
	//A*B^-1 元素计算器
	this->p_ABInvCalc = &ABInvCalc;

	this->generateHessenTriangleOpMatrix();
};

void DynamicDoubleShiftQZIteration::reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	if(this->p_OpMatrix_A->rowNum == p_input_OpMatrix_A->rowNum && this->p_OpMatrix_A->columnNum == p_input_OpMatrix_A->columnNum
				&& this->p_OpMatrix_B->rowNum == p_input_OpMatrix_B->rowNum && this->p_OpMatrix_B->columnNum == p_input_OpMatrix_B->columnNum)
	{
		this->p_OpMatrix_A->copyMatrixElementNoCheck(p_input_OpMatrix_A);
		this->p_OpMatrix_B->copyMatrixElementNoCheck(p_input_OpMatrix_B);

		this->p_OpMatrix_Hessenberg->resetMatrixToI();
		this->p_OpMatrix_Triangle->resetMatrixToI();

		this->p_QMatrix_Implicit_Step->resetMatrixToI();
		this->p_ZMatrix_Implicit_Step->resetMatrixToI();

		this->p_QMatrix_Implicit_Total->resetMatrixToI();
		this->p_ZMatrix_Implicit_Total->resetMatrixToI();

		this->p_QSubMatrix_Implicit_Step_3->resetMatrixToI();
		this->p_QSubMatrix_Implicit_Step_2->resetMatrixToI();

		this->p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();
		this->p_ZSubMatrix_Implicit_Step_2->resetMatrixToI();

		this->generateHessenTriangleOpMatrix();
	}
	else
	{
		init(p_input_OpMatrix_A, p_input_OpMatrix_B);
	}
};
