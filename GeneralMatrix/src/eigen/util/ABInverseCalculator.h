/*
 * ABInverseCalculator.h
 *
 *  Created on: 2017年6月3日
 *      Author: looke
 */

#ifndef EIGEN_UTIL_ABINVERSECALCULATOR_H_
#define EIGEN_UTIL_ABINVERSECALCULATOR_H_

#include "..\matrix\basic\BasicMatrix.h"
class ABInverseCalculator
{
public:
	ABInverseCalculator();

	//计算B^-1最后三行
	void generateBinvLastThreeRow(BasicMatrix* p_OpMatrix_Tirangle);

	//计算B^-1最后二行
	void generateBinvLastTwoRow(BasicMatrix* p_OpMatrix_Triangle);

	//计算 A*B^-1 右下2x2子矩阵元素
	void generateABinvLast2x2(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle);

	//计算 A*B^-1 前两列元素
	void generateABinvFirst3x2(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle);

	//计算 A*B^-1 左上2x2子矩阵
	void generateABinvFirst2x2(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle);

	//计算AB^-1 右下角元素值 用于单步位移
	void generateABinvLastOne(BasicMatrix* p_OpMatrix_Hessenberg, BasicMatrix* p_OpMatrix_Triangle);

	double getABinv11() const
	{
		return ABinv_11;
	}

	double getABinv12() const
	{
		return ABinv_12;
	}

	double getABinv21() const
	{
		return ABinv_21;
	}

	double getABinv22() const
	{
		return ABinv_22;
	}

	double getABinv32() const
	{
		return ABinv_32;
	}

	double getABinv_N_1_N() const
	{
		return ABinv_n_1_n;
	}

	double getABinv_N_1_N_1() const
	{
		return ABinv_n_1_n_1;
	}

	double getABinv_N_N() const
	{
		return ABinv_n_n;
	}

	double getABinv_N_N_1() const
	{
		return ABinv_n_n_1;
	}

	double getBinv_N_1_N() const
	{
		return Binv_n_1_n;
	}

	double getBinv_N_1_N_1() const
	{
		return Binv_n_1_n_1;
	}

	double getBinv_N_2_N() const
	{
		return Binv_n_2_n;
	}

	double getBinv_N_2_N_1() const
	{
		return Binv_n_2_n_1;
	}

	double getBinv_N_2_N_2() const
	{
		return Binv_n_2_n_2;
	}

	double getBinv_N_N() const
	{
		return Binv_n_n;
	}

protected:

	//B^-1 最后3行
	double Binv_n_2_n_2;
	double Binv_n_2_n_1;
	double Binv_n_2_n;
	double Binv_n_1_n_1;
	double Binv_n_1_n;
	double Binv_n_n;

	//A*B^-1 右下2x2子矩阵元素
	double ABinv_n_1_n_1;
	double ABinv_n_1_n;
	double ABinv_n_n_1;
	double ABinv_n_n;

	//A*B^-1 前两列元素
	double ABinv_11;
	double ABinv_12;
	double ABinv_21;
	double ABinv_22;
	double ABinv_32;
};

#endif /* EIGEN_UTIL_ABINVERSECALCULATOR_H_ */
