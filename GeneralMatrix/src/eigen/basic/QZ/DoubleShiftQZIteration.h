/*
 * DoubleShiftQZIteration.h
 *
 *  Created on: 2017年5月29日
 *      Author: looke
 */

#ifndef EIGEN_BASIC_DOUBLESHIFTQZITERATION_H_
#define EIGEN_BASIC_DOUBLESHIFTQZITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\vector\basic\BasicVector.h"
#include "..\eigen\util\ABInverseCalculator.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "..\transformation\basic\HessenbergTriangleFormular.h"
//#include "..\transformation\basic\QZTriangleZeroChasing.h"
#include "..\transformation\basic\HouseholderTransformation.h"

class DoubleShiftQZIteration
{
public:
	DoubleShiftQZIteration();
	DoubleShiftQZIteration(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);

	virtual void init(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);
	virtual void reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);
	virtual ~DoubleShiftQZIteration(){};

	//生成H-T操作矩阵对
	void generateHessenTriangleOpMatrix();

	//Wilkinson位移QZ迭代 隐式 初始化
	void initForWilkinsonImplicitQZ();

	//Wilkinson双位移QZ迭代 隐式 -收尾
	void endForWilkinsonImplicitQZ();

	//Wilkinson位移QZ迭代 隐式 单轮迭代
	void wilkinson_IM_QZIteration_Step();
	//Wilkinson位移QZ迭代 隐式 单轮迭代对外接口
	void wilkinson_IM_QZIteration_Single();
	//Wilkinson位移QZ迭代 隐式 10次连续迭代
	void wilkinson_IM_QZIteration();

	//根据A*B^-1 矩阵最后2x2子矩阵 计算生成Wilkinson移位的trace & determinant
	void generateWilkinsonShift();

	//计算 A*B^-1 前两列元素
	void generateABinvFirst3x2();

	//计算 A*B^-1 双重移位后 第一列元素
	void generateABinvShiftedFirstColumn();

	//根据当前迭代进度，生成三角矩阵膨胀部位的元素
	void generateTriangleBulgeElement(int iterateNum);

	//将QZ子矩阵根据当前迭代进度,升级为全尺寸QZ矩阵
	void upgradeQSubMatrix(int iterateNum);
	void upgradeZSubMatrix(int iterateNum);
	//将2x2 Q子矩阵升级为 3x3 Q子矩阵 2x2位于右下
	void upgradeQMiniToSubMatrix_RightEnd();
	//将2x2 Z子矩阵升级为 3x3 Z子矩阵 2x2位于右下
	void upgradeZMiniToSubMatrix_RightEnd();
	//将2x2 Z子矩阵升级为 3x3 Z子矩阵 2x2位于左上
	void upgradeZMiniToSubMatrix_LeftTop();

	//使用Q矩阵左乘H-T矩阵对
	void updateHTMatrixByQ();
	//使用Z矩阵右乘H-T矩阵对
	void updateHTMatrixByZ();
	//更新综合转换矩阵Q/Z Total(将Step合并入Total)
	void updateQMatrix_Total();
	void updateZMatrix_Total();

	//获取Q/Z 综合转换矩阵
	BasicMatrix* getQMatrix_Total();
	BasicMatrix* getZMatrix_Total();
protected:
	//p+t 两个wilkinson位移值的和
	double trace;

	//p*t 两个wilkinson位移值的乘积
	double determinant;

	//A*B^-1 前两列元素
	double ABinv_11;
	double ABinv_12;
	double ABinv_21;
	double ABinv_22;
	double ABinv_32;

	// C = (AB^-1 -pI)*(AB^-1 -tI); 双步移位后的矩阵第一列
	double C11;
	double C21;
	double C31;

    //三角矩阵膨胀部分的元素
	double B_21;
	double B_22;
	double B_31;
	double B_32;
	double B_33;
	//操作矩阵
	BasicMatrix* p_OpMatrix_A;
	BasicMatrix* p_OpMatrix_B;

	//Hessenberg矩阵
	BasicMatrix* p_OpMatrix_Hessenberg;
	//Triangle矩阵
	BasicMatrix* p_OpMatrix_Triangle;

	//用于计算隐式双步QZ跌代单步转换矩阵Qi的向量---3维
	BasicVector* p_TransVectorForQStep_3;
	//用于计算隐式双步QZ跌代单步转换矩阵Qn-1的向量---2维
	BasicVector* p_TransVectorForQStep_2;

	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---3维
	BasicVector* p_TransVectorForZStep_3;
	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---2维
	BasicVector* p_TransVectorForZStep_2;

	//Q 全尺寸矩阵 隐式迭代 分步 Q用于左乘OP矩阵
	BasicMatrix* p_QMatrix_Implicit_Step;
	//Z 全尺寸矩阵 隐式迭代 分步 Z用于右乘OP矩阵
	BasicMatrix* p_ZMatrix_Implicit_Step;

	//Q 全尺寸矩阵 隐式迭代  总体Q用于左乘OP矩阵
	BasicMatrix* p_QMatrix_Implicit_Total;
	//Z 全尺寸矩阵 隐式迭代 总体Z用于右乘OP矩阵
	BasicMatrix* p_ZMatrix_Implicit_Total;

	//Qi 子矩阵 显式迭代 分步 Qi用于左乘OP矩阵 3x3
	BasicMatrix* p_QSubMatrix_Implicit_Step_3;
	//Qi 子矩阵 显式迭代 分步 Qn-1用于左乘OP矩阵 2x2
	BasicMatrix* p_QSubMatrix_Implicit_Step_2;

	//Zi 子矩阵 显式迭代 分步 QTi用于右乘OP矩阵 3x3
	BasicMatrix* p_ZSubMatrix_Implicit_Step_3;
	//Zi 子矩阵 显式迭代 分步 QT用于右乘OP矩阵 2x2
	BasicMatrix* p_ZSubMatrix_Implicit_Step_2;

	//hessenberg-triangle格式化
	HessenbergTriangleFormular* p_HessenbergTriangleFormular;


	//householder变换
	HouseholderTransformation* p_HouseholderTrans;

	//乘法器
	MatrixMultiplier* p_Multiplier;

	//AB^-1 元素计算器
	ABInverseCalculator* p_ABInvCalc;
};



#endif /* EIGEN_BASIC_DOUBLESHIFTQZITERATION_H_ */
