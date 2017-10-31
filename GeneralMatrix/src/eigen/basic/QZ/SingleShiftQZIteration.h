/*
 * SingleShiftQZIteration.h
 *
 *  Created on: 2017年5月26日
 *      Author: looke
 */

#ifndef EIGEN_BASIC_SINGLESHIFTQZITERATION_H_
#define EIGEN_BASIC_SINGLESHIFTQZITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "..\transformation\basic\HessenbergTriangleFormular.h"
//#include "..\transformation\basic\QZTriangleZeroChasing.h"
#include "..\transformation\basic\GivensTransformation.h"
#include "..\eigen\util\ABInverseCalculator.h"

class SingleShiftQZIteration
{
public:
	SingleShiftQZIteration();
	SingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	virtual void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	virtual void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	virtual ~SingleShiftQZIteration(){};

	//生成H-T操作矩阵对
	void generateHessenTriangleOpMatrix();

	//计算B^-1最后2行 用于计算单步位移值
	//void generateBinvLastTwoRow();

	//计算AB^-1 右下角元素值 用于单步位移
	//double generateABinvLastOne();

	//初始化隐式迭代
	void initForImplicitQZ(double input_ShiftValue);

	//单值位移QZ迭代 隐式单步
	void implicit_QZIteration_Step(double input_shiftValue);

	//单值位移QZ迭代 隐式
	void implicit_QZIteration(double input_shiftValue);

	//单值rayleigh商位移QZ迭代 隐式 多次
	void rayleigh_Quotient_IM_QZIteration(int iterateNum);

	//单值rayleigh商位移QZ迭代 隐式 单步
	void rayleigh_Quotient_IM_QZIteration_Step();

	//使用Q矩阵左乘H-T矩阵对
	void updateHTMatrixByQ();
	//使用Z矩阵右乘H-T矩阵对
	void updateHTMatrixByZ();

	//更新综合转换矩阵Q/Z Total(将Step合并入Total)
	void updateQZMatrix_Total();

	//获取Q/Z 总体转换矩阵
	BasicMatrix* getQMatrix_Total();
	BasicMatrix* getZMatrix_Total();
protected:
	//B^-1 最后两行元素
	//double Binv_n_1_n_1;
	//double Binv_n_1_n;
	//double Binv_n_n;

	//原始操作矩阵A
	BasicMatrix* p_OpMatrix_A;
	//原始操作矩阵B
	BasicMatrix* p_OpMatrix_B;

	//Hessenberg 操作矩阵A
	BasicMatrix* p_OpMatrix_Hessenberg;
	//Triangle 操作矩阵B
	BasicMatrix* p_OpMatrix_Triangle;

	//Z 矩阵 隐式迭代 分步 Z用于右乘OP矩阵
	BasicMatrix* p_ZMatrix_Implicit_Step;
	//Q 矩阵 隐式迭代 分步 Q用于左乘OP矩阵
	BasicMatrix* p_QMatrix_Implicit_Step;

	//Z 矩阵 隐式迭代 综合 Z用于右乘OP矩阵
	BasicMatrix* p_ZMatrix_Implicit_Total;
	//Q 矩阵 隐式迭代 综合 Q用于左乘OP矩阵
	BasicMatrix* p_QMatrix_Implicit_Total;

	//hessenberg-triangle格式化
	HessenbergTriangleFormular* p_HessenbergTriangleFormular;

	//QZ-triangle 0元移位
	//QZTriangleZeroChasing* p_QZTriangleZeroChasing;

	//Givens变换器
	GivensTransformation* p_GivensTrans;

	//乘法器
	MatrixMultiplier* p_Multiplier;

	//AB^-1 元素计算器
	ABInverseCalculator* p_ABInvCalc;
};



#endif /* EIGEN_BASIC_SINGLESHIFTQZITERATION_H_ */
