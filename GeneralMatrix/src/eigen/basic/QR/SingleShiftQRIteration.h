/*
 * SingelShiftQRIteration.h
 *
 *  Created on: 2017年5月13日
 *      Author: looke
 */

#ifndef EIGEN_BASIC_SINGLESHIFTQRITERATION_H_
#define EIGEN_BASIC_SINGLESHIFTQRITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixTransposer.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "..\transformation\basic\HessenbergFormular.h"
#include "..\transformation\basic\GivensTransformation.h"


class SingleShiftQRIteration
{
public:
	SingleShiftQRIteration();
	SingleShiftQRIteration(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~SingleShiftQRIteration(){};

	//瑞利商位移QR迭代 显式
	void rayleigh_Quotient_EX_QRIteration();

	//瑞利商位移QR迭代 隐式 10次迭代
	void rayleigh_Quotient_IM_QRIteration();
	//瑞利商位移QR迭代 隐式 指定迭代次数
	void rayleigh_Quotient_IM_QRIteration(int iterateNum);
	//瑞利商位移QR迭代 隐式 单步
	void rayleigh_Quotient_IM_QRIteration_Step();

	//单值位移QR迭代 显式
	void explicit_QRIteration(double input_shiftValue);
	//单值位移QR迭代 显式单步
	void explicit_QRIteration_Step(double input_shiftValue);

	//单值位移QR迭代 隐式
	void implicit_QRIteration(double input_shiftValue);
	//单值位移QR迭代 隐式单步
	void implicit_QRIteration_Step(double input_shiftValue);

	//单值位移QR迭代 隐式 初始化
	void initForImplicitQR(double input_shiftValue);

	//更新综合转换矩阵Q QT Total
	void updateQQTMatrix_Total_IM_QRIteration();

	//生成hessenberg操作矩阵
	void generateHessenbergOpMatrix();

	BasicMatrix* getOpHessenbergMatrix();

	//获取总体转换矩阵
	BasicMatrix* getQTMatrix_Total();
	BasicMatrix* getQMatrix_Total();

protected:

	//对角线全部元素减去指定值
	//void diagonalSubtraction_Hessn(double subValue);
	//对角线全部元素加上指定值
	//void diagonalAddition_Hessn(double addValue);



	//隐式QR迭代 更新hessenberg操作矩阵
	void updateHessenbergOpMatrix_IM_QRIteration();

	//操作矩阵
	BasicMatrix* p_OpMatrix;

	//Hessenberg矩阵
	BasicMatrix* p_OpHessenbergMatrix;

	//Q 矩阵 显式迭代
	BasicMatrix* p_QMatrix_Explicit;

	//Q 矩阵 隐式迭代 分步 Q用于右乘OP矩阵
	BasicMatrix* p_QMatrix_Implicit_Step;
	//QT 矩阵 隐式迭代 分步 QT用于左乘OP矩阵
	BasicMatrix* p_QTMatrix_Implicit_Step;

	//Q 矩阵 隐式迭代 综合 Q用于右乘OP矩阵
	BasicMatrix* p_QMatrix_Implicit_Total;
	//QT 矩阵 隐式迭代 综合 QT用于左乘OP矩阵
	BasicMatrix* p_QTMatrix_Implicit_Total;

	//QR分解
	QRDecomposition* p_QRDecomp;

	//hessen格式化
	HessenbergFormular* p_HessenbergForm;

	//Givens变换器
	GivensTransformation* p_GivensTrans;

	//乘法器
	MatrixMultiplier* p_Multiplier;

	//转置器
	MatrixTransposer* p_Transposer;
};



#endif /* EIGEN_BASIC_SINGLESHIFTQRITERATION_H_ */
