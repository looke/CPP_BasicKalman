/*
 * ABInverseCalculator.cpp
 *
 *  Created on: 2017年6月3日
 *      Author: looke
 */

#include "ABInverseCalculator.h"

ABInverseCalculator::ABInverseCalculator()
{
	//B^-1 最后3行
	this->Binv_n_2_n_2 = 0;
	this->Binv_n_2_n_1 = 0;
	this->Binv_n_2_n = 0;
	this->Binv_n_1_n_1 = 0;
	this->Binv_n_1_n = 0;
	this->Binv_n_n = 0;

	//A*B^-1 右下2x2子矩阵元素
	this->ABinv_n_1_n_1 = 0;
	this->ABinv_n_1_n = 0;
	this->ABinv_n_n_1 = 0;
	this->ABinv_n_n = 0;

	//A*B^-1 前两列元素
	this->ABinv_11 = 0;
	this->ABinv_12 = 0;
	this->ABinv_21 = 0;
	this->ABinv_22 = 0;
	this->ABinv_32 = 0;
};

/*
 * 计算B^-1最后三行
 */
void ABInverseCalculator::generateBinvLastThreeRow(BasicMatrix* p_OpMatrix_Triangle)
{
	int n = p_OpMatrix_Triangle->rowNum - 1;
	double B_n_2_n_2  = p_OpMatrix_Triangle->getMatrixElement(n-2,n-2);
	double B_n_2_n_1 = p_OpMatrix_Triangle->getMatrixElement(n-2,n-1);
	double B_n_2_n = p_OpMatrix_Triangle->getMatrixElement(n-2,n);

	double B_n_1_n_1 = p_OpMatrix_Triangle->getMatrixElement(n-1,n-1);
	double B_n_1_n = p_OpMatrix_Triangle->getMatrixElement(n-1,n);

	double B_n_n = p_OpMatrix_Triangle->getMatrixElement(n,n);

	this->Binv_n_n = 1/B_n_n;

	this->Binv_n_1_n_1 = 1/B_n_1_n_1;
	this->Binv_n_1_n = 0 - B_n_1_n/(B_n_1_n_1 * B_n_n);

	this->Binv_n_2_n_2 = 1/B_n_2_n_2;
	this->Binv_n_2_n_1 = 0 - B_n_2_n_1/(B_n_2_n_2 * B_n_1_n_1);
	this->Binv_n_2_n = 0 - (Binv_n_2_n_2*B_n_2_n + Binv_n_2_n_1*B_n_1_n) * Binv_n_n;
};

/*
 * 计算B^-1最后二行
 */
void ABInverseCalculator::generateBinvLastTwoRow(BasicMatrix* p_OpMatrix_Triangle)
{
	int n = p_OpMatrix_Triangle->rowNum - 1;

	double B_n_1_n_1 = p_OpMatrix_Triangle->getMatrixElement(n-1,n-1);
	double B_n_1_n = p_OpMatrix_Triangle->getMatrixElement(n-1,n);

	double B_n_n = p_OpMatrix_Triangle->getMatrixElement(n,n);

	this->Binv_n_n = 1/B_n_n;

	this->Binv_n_1_n_1 = 1/B_n_1_n_1;
	this->Binv_n_1_n = 0 - B_n_1_n/(B_n_1_n_1 * B_n_n);
};

//计算 A*B^-1 左上2x2子矩阵
void ABInverseCalculator::generateABinvFirst2x2(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle)
{
	//A B各自矩阵的元素
	double a11,a12,a21,a22;
	double b11,b12,b22;

	a11 = p_OpMatrix_Hessenberg->getMatrixElement(0,0);
	a12 = p_OpMatrix_Hessenberg->getMatrixElement(0,1);
	a21 = p_OpMatrix_Hessenberg->getMatrixElement(1,0);
	a22 = p_OpMatrix_Hessenberg->getMatrixElement(1,1);

	b11 = p_OpMatrix_Triangle->getMatrixElement(0,0);
	b12 = p_OpMatrix_Triangle->getMatrixElement(0,1);
	b22 = p_OpMatrix_Triangle->getMatrixElement(1,1);

	//A*B^-1 前两列元素
	this->ABinv_11 = a11/b11;
	this->ABinv_12 = (a12*b11 - a11*b12)/(b11*b22);
	this->ABinv_21 = a21/b11;
	this->ABinv_22 = (a22*b11 - a21*b12)/(b11*b22);
};


/*
 * 计算 A*B^-1 前两列元素
 */
void ABInverseCalculator::generateABinvFirst3x2(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle)
{
	generateABinvFirst2x2(p_OpMatrix_Hessenberg, p_OpMatrix_Triangle);
	//A B各自矩阵的元素
	double a32;
	double b22;

	a32 = p_OpMatrix_Hessenberg->getMatrixElement(2,1);

	b22 = p_OpMatrix_Triangle->getMatrixElement(1,1);

	this->ABinv_32 = a32/b22;
};

/*
 * 计算 A*B^-1 右下2x2子矩阵元素
 */
void ABInverseCalculator::generateABinvLast2x2(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle)
{
	//首先需要计算B^-1最后三行
	generateBinvLastThreeRow(p_OpMatrix_Triangle);

	int n = p_OpMatrix_Hessenberg->rowNum - 1;

	double A_n_1_n_2 = p_OpMatrix_Hessenberg->getMatrixElement(n-1,n-2);
	double A_n_1_n_1 = p_OpMatrix_Hessenberg->getMatrixElement(n-1,n-1);
	double A_n_1_n = p_OpMatrix_Hessenberg->getMatrixElement(n-1,n);

	double A_n_n_1 = p_OpMatrix_Hessenberg->getMatrixElement(n,n-1);
	double A_n_n = p_OpMatrix_Hessenberg->getMatrixElement(n,n);

	this->ABinv_n_1_n_1 = A_n_1_n_2*Binv_n_2_n_1 + A_n_1_n_1*Binv_n_1_n_1;
	this->ABinv_n_1_n = A_n_1_n_2*Binv_n_2_n + A_n_1_n_1*Binv_n_1_n + A_n_1_n*Binv_n_n;

	this->ABinv_n_n_1 = A_n_n_1 * Binv_n_1_n_1;
	this->ABinv_n_n = A_n_n_1*Binv_n_1_n + A_n_n*Binv_n_n;
};

//计算AB^-1 右下角元素值 用于单步位移
void ABInverseCalculator::generateABinvLastOne(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle)
{
	//首先需要计算B^-1最后2行
	this->generateBinvLastTwoRow(p_OpMatrix_Triangle);

	int n = p_OpMatrix_Hessenberg->rowNum - 1;

	double A_n_n_1 = p_OpMatrix_Hessenberg->getMatrixElement(n,n-1);
	double A_n_n = p_OpMatrix_Hessenberg->getMatrixElement(n,n);

	this->ABinv_n_n = A_n_n_1*Binv_n_1_n + A_n_n*Binv_n_n;
};
