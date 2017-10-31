/*
 * DynamicDoubleShiftQRIteration.h
 *
 *  Created on: 2017年5月18日
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQRITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQRITERATION_H_

#include "..\eigen\basic\QR\DoubleShiftQRIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\dynamic\util\DynamicMatrixTransposer.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"


class DynamicDoubleShiftQRIteration:public DoubleShiftQRIteration
{
public:

	DynamicDoubleShiftQRIteration(BasicMatrix* p_intput_OpMatrix);

	void init(BasicMatrix* p_intput_OpMatrix);
	void reload(BasicMatrix* p_intput_OpMatrix);

protected:

	//操作矩阵
	DynamicMatrix opMatrix;

	//Hessenberg矩阵
	DynamicMatrix opHessenbergMatrix;

	//生成转换矩阵的向量
	DynamicVector transVectorForQStep;
	DynamicVector transVectorForQ_LastStep;

	//Q 矩阵 显式迭代 分步 Q用于右乘OP矩阵 nxn
	DynamicMatrix QMatrix_Implicit_Step;
	//QT 矩阵 显式迭代 分步 QT用于左乘OP矩阵 nxn
	DynamicMatrix QTMatrix_Implicit_Step;

	//Q 矩阵 显式迭代 总体 Q用于右乘OP矩阵 nxn
	DynamicMatrix QMatrix_Implicit_Total;
	//QT 矩阵 显式迭代 总体 QT用于左乘OP矩阵 nxn
	DynamicMatrix QTMatrix_Implicit_Total;

	//Qi 子矩阵 显式迭代 分步 Q用于右乘OP矩阵 3x3
	DynamicMatrix QSubMatrix_Implicit_Step;
	//Qn-1 子矩阵 显式迭代 分步 Q用于右乘OP矩阵 2x2
	DynamicMatrix QSubMatrix_Implicit_LastStep;

	//QTi 子矩阵 显式迭代 分步 QT用于左乘OP矩阵 3x3
	DynamicMatrix QTSubMatrix_Implicit_Step;
	//QTn-1 子矩阵 显式迭代 分步 Q用于右乘OP矩阵 2x2
	DynamicMatrix QTSubMatrix_Implicit_LastStep;


	//QR分解
	//DynamicQRDecomposition dQRDecomp;

	//hessen格式化
	DynamicHessenbergFormular dHessenbergForm;

	//Givens变换器
	DynamicGivensTransformation dGivensTrans;

	//Householder变换器
	DynamicHouseholderTransformation dHouseholderTrans;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//转置器
	DynamicMatrixTransposer dTransposer;
};

#endif /* EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQRITERATION_H_ */
