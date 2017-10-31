/*
 * DynamicGeneralizedEigenSolverForReal.h
 *
 *  Created on: 2017年6月2日
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICGENERALIZEDEIGENSOLVERFORREAL_H_
#define EIGEN_DYNAMIC_DYNAMICGENERALIZEDEIGENSOLVERFORREAL_H_
#include "..\eigen\basic\GeneralizedEigenSolverForReal.h"
#include "..\eigen\dynamic\QZ\DynamicDoubleShiftQZIteration.h"
#include "..\eigen\dynamic\QZ\DynamicSingleShiftQZIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"
#include "..\transformation\dynamic\DynamicHessenbergTriangleFormular.h"
#include "..\transformation\dynamic\DynamicQZTriangleZeroChasing.h"


class DynamicGeneralizedEigenSolverForReal:public GeneralizedEigenSolverForReal
{
public:
	//DynamicGeneralizedEigenSolverForReal();
	DynamicGeneralizedEigenSolverForReal(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

protected:
	//原始操作矩阵
	DynamicMatrix OpMatrix_A;
	DynamicMatrix OpMatrix_B;

	//原始操作Hessenberg矩阵
	DynamicMatrix OpMatrix_Hessenberg;
	//原始操作Triangle矩阵
	DynamicMatrix OpMatrix_Triangle;

	//原始矩阵的全维度单迭代变换矩阵
	DynamicMatrix QMatrix_Iteration;
	DynamicMatrix ZMatrix_Iteration;

	//原始矩阵的全维度总体变换矩阵
	DynamicMatrix QMatrix_Total;
	DynamicMatrix ZMatrix_Total;

	//已降阶的 操作Hessenberg矩阵
	DynamicMatrix OpMatrix_Hessenberg_deflated;
	//已降阶的 操作Triangle矩阵
	DynamicMatrix OpMatrix_Triangle_deflated;

	//已降阶矩阵的单迭代变换矩阵Q\Z
	DynamicMatrix QMatrix_Deflated_Iteration;
	DynamicMatrix ZMatrix_Deflated_Iteration;

	//最后一步针对对角线2x2矩阵块的操作
	DynamicMatrix LastStepMatrix_2x2_Hessenberg;
	DynamicMatrix LastStepMatrix_2x2_Triangle;

	//双重步QZ迭代器
	DynamicDoubleShiftQZIteration dDoubleShifeQZ;

	//单步QR迭代器
	DynamicSingleShiftQZIteration dSingleShifeQZ;

	//hessenberg-triangle格式化
	DynamicHessenbergTriangleFormular dHessenbergTriangleFormular;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//hessenberg降阶点查找器
	HessenbergDeflation dHessenbergDeflation;

	//QZ-triangle 0元移位
	DynamicQZTriangleZeroChasing dQZTriangleZeroChasing;

	//AB^-1 元素计算器
	ABInverseCalculator ABInvCalc;

	//测试总体转置矩阵的临时测试对象
	DynamicMatrix testForTemp_A_nxn;
	DynamicMatrix testForTemp_B_nxn;
	DynamicMatrixMultiplier testMulti;
};



#endif /* EIGEN_DYNAMIC_DYNAMICGENERALIZEDEIGENSOLVERFORREAL_H_ */
