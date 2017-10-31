/*
 * DynamicDoubleShiftQZIteration.h
 *
 *  Created on: 2017年5月31日
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQZITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQZITERATION_H_

#include "..\eigen\basic\QZ\DoubleShiftQZIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"
#include "..\transformation\dynamic\DynamicHessenbergTriangleFormular.h"

class DynamicDoubleShiftQZIteration : public DoubleShiftQZIteration
{
public:

	DynamicDoubleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

protected:
	//操作矩阵 nxn
	DynamicMatrix OpMatrix_A;
	DynamicMatrix OpMatrix_B;

	//Hessenberg矩阵 nxn
	DynamicMatrix OpMatrix_Hessenberg;
	//Triangle矩阵 nxn
	DynamicMatrix OpMatrix_Triangle;

	//用于计算隐式双步QZ跌代单步转换矩阵Qi的向量---3维
	DynamicVector TransVectorForQStep_3;
	//用于计算隐式双步QZ跌代单步转换矩阵Qn-1的向量---2维
	DynamicVector TransVectorForQStep_2;

	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---3维
	DynamicVector TransVectorForZStep_3;
	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---2维
	DynamicVector TransVectorForZStep_2;

	//Q 全尺寸矩阵 隐式迭代 分步 Q用于左乘OP矩阵  nxn
	DynamicMatrix QMatrix_Implicit_Step;
	//Z 全尺寸矩阵 隐式迭代 分步 Z用于右乘OP矩阵  nxn
	DynamicMatrix ZMatrix_Implicit_Step;

	//Q 全尺寸矩阵 隐式迭代  总体Q用于左乘OP矩阵  nxn
	DynamicMatrix QMatrix_Implicit_Total;
	//Z 全尺寸矩阵 隐式迭代 总体Z用于右乘OP矩阵  nxn
	DynamicMatrix ZMatrix_Implicit_Total;

	//Qi 子矩阵 显式迭代 分步 Qi用于左乘OP矩阵 3x3
	DynamicMatrix QSubMatrix_Implicit_Step_3;
	//Qi 子矩阵 显式迭代 分步 Qn-1用于左乘OP矩阵 2x2
	DynamicMatrix QSubMatrix_Implicit_Step_2;

	//Zi 子矩阵 显式迭代 分步 QTi用于右乘OP矩阵 3x3
	DynamicMatrix ZSubMatrix_Implicit_Step_3;
	//Zi 子矩阵 显式迭代 分步 QT用于右乘OP矩阵 2x2
	DynamicMatrix ZSubMatrix_Implicit_Step_2;

	//hessenberg-triangle格式化
	DynamicHessenbergTriangleFormular dHessenbergTriangleFormular;

	//QZ-triangle 0元移位
	//QZTriangleZeroChasing* p_QZTriangleZeroChasing;

	//householder变换
	DynamicHouseholderTransformation dHouseholderTrans;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//AB^-1 元素计算器
	ABInverseCalculator ABInvCalc;
};



#endif /* EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQZITERATION_H_ */
