/*
 * DynamicSingleShiftQZIteration.h
 *
 *  Created on: 2017年5月28日
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQZITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQZITERATION_H_

#include "..\eigen\basic\QZ\SingleShiftQZIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\transformation\dynamic\DynamicHessenbergTriangleFormular.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"
#include "..\transformation\dynamic\DynamicQZTriangleZeroChasing.h"


class DynamicSingleShiftQZIteration : public SingleShiftQZIteration
{
public:
	DynamicSingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);


protected:

	//原始操作矩阵A
	DynamicMatrix OpMatrix_A;
	//原始操作矩阵B
	DynamicMatrix OpMatrix_B;

	//Hessenberg 操作矩阵A
	DynamicMatrix OpMatrix_Hessenberg;
	//Triangle 操作矩阵B
	DynamicMatrix OpMatrix_Triangle;

	//Z 矩阵 隐式迭代 分步 Z用于右乘OP矩阵
	DynamicMatrix ZMatrix_Implicit_Step;
	//Q 矩阵 隐式迭代 分步 Q用于左乘OP矩阵
	DynamicMatrix QMatrix_Implicit_Step;

	//Z 矩阵 隐式迭代 综合 Z用于右乘OP矩阵
	DynamicMatrix ZMatrix_Implicit_Total;
	//Q 矩阵 隐式迭代 综合 Q用于左乘OP矩阵
	DynamicMatrix QMatrix_Implicit_Total;

	//hessenberg-triangle格式化
	DynamicHessenbergTriangleFormular dHessenbergTriangleFormular;

	//QZ-triangle 0元移位
	DynamicQZTriangleZeroChasing dQZTriangleZeroChasing;

	//Givens变换器
	DynamicGivensTransformation dGivensTrans;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//AB^-1 元素计算器
	ABInverseCalculator ABInvCalc;
};

#endif /* EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQZITERATION_H_ */
