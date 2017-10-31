/*
 * DynamicNormalEigenSolverForReal.h
 *
 *  Created on: 2017年5月23日
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICNORMALEIGENSOLVERFORREAL_H_
#define EIGEN_DYNAMIC_DYNAMICNORMALEIGENSOLVERFORREAL_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\eigen\basic\NormalEigenSolverForReal.h"
#include "..\eigen\dynamic\QR\DynamicDoubleShiftQRIteration.h"
#include "..\eigen\dynamic\QR\DynamicSingleShiftQRIteration.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"

class DynamicNormalEigenSolverForReal : public NormalEigenSolverForReal
{
public:
	//DynamicNormalEigenSolverForReal();
	DynamicNormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix);

	void init(BasicMatrix* p_input_OpMatrix);
	void reload(BasicMatrix* p_input_OpMatrix);

protected:
	//原始操作矩阵
	DynamicMatrix OpMatrix;

	//原始操作矩阵对应的特征值矩阵
	DynamicMatrix EigenValueMatrix;

	//原始操作Hessenberg矩阵
	DynamicMatrix OpHessenbergMatrix;

	//原始矩阵的单迭代变换矩阵
	DynamicMatrix QTMatrix_Iteration;
	DynamicMatrix QMatrix_Iteration;

	//原始矩阵的总体变换矩阵
	DynamicMatrix QTMatrix_Total;
	DynamicMatrix QMatrix_Total;

	//已降阶的 操作Hessenberg矩阵
	DynamicMatrix OpHessenbergMatrix_deflated;

	//已降阶矩阵的单迭代变换矩阵Q\QT
	DynamicMatrix QTMatrix_Deflated_Iteration;
	DynamicMatrix QMatrix_Deflated_Iteration;

	//最后一步针对对角线2x2矩阵块的操作
	DynamicMatrix LastStepMatrix_2x2;

	//双重步QR迭代器
	DynamicDoubleShiftQRIteration dDoubleShifeQR;

	//双重步QR迭代器
	DynamicSingleShiftQRIteration dSingleShifeQR;

	//hessen格式化
	DynamicHessenbergFormular dHessenbergForm;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//hessenberg降阶点查找
	HessenbergDeflation HessenbergDeflation;

	//测试总体转置矩阵的临时测试对象
	DynamicMatrix testForTemp_nxn;
	DynamicMatrixMultiplier testMulti;

};


#endif /* EIGEN_DYNAMIC_DYNAMICNORMALEIGENSOLVERFORREAL_H_ */
