/*
 * DynamicSingelShiftQRIteration.h
 *
 *  Created on: 2017年5月13日
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQRITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQRITERATION_H_

#include "..\eigen\basic\QR\SingleShiftQRIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixTransposer.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"

class DynamicSingleShiftQRIteration : public  SingleShiftQRIteration
{
public:
	DynamicSingleShiftQRIteration(BasicMatrix* p_intput_OpMatrix);

	void init(BasicMatrix* p_intput_OpMatrix);
	void reload(BasicMatrix* p_intput_OpMatrix);

protected:
	//操作矩阵
	DynamicMatrix opMatrix;

	//Hessenberg矩阵
	DynamicMatrix opHessenbergMatrix;

	//Q 矩阵 显式迭代
	DynamicMatrix QMatrix_Explicit;

	//Q 矩阵 显式迭代 分步 Q用于右乘OP矩阵
	DynamicMatrix QMatrix_Implicit_Step;
	//QT 矩阵 显式迭代 分步 QT用于左乘OP矩阵
	DynamicMatrix QTMatrix_Implicit_Step;

	//Q 矩阵 显式迭代 综合 Q用于右乘OP矩阵
	DynamicMatrix QMatrix_Implicit_Total;
	//QT 矩阵 显式迭代 综合 QT用于左乘OP矩阵
	DynamicMatrix QTMatrix_Implicit_Total;

	//QR分解
	DynamicQRDecomposition dQRDecomp;

	//hessen格式化
	DynamicHessenbergFormular dHessenbergForm;

	//Givens变换器
	DynamicGivensTransformation dGivensTrans;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//转置器
	DynamicMatrixTransposer dTransposer;
};


#endif /* EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQRITERATION_H_ */
