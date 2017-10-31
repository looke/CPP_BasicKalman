/*
 * DynamicNormalQRIteration.h
 *
 *  Created on: 2017年5月8日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_DYNAMICNORMALQRITERATION_H_
#define TRANSFORMATION_BASIC_DYNAMICNORMALQRITERATION_H_

#include "..\eigen\basic\QR\NormalQRIteration.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"

class DynamicNormalQRIteration : public NormalQRIteration
{
public:
	DynamicNormalQRIteration(BasicMatrix* p_intput_OpMatrix);

	void init(BasicMatrix* p_intput_OpMatrix);
	void reload(BasicMatrix* p_intput_OpMatrix);

protected:
	//操作矩阵
	DynamicMatrix opMatrix;

	//Hessenberg矩阵
	DynamicMatrix opHessenbergMatrix;

	//Q 矩阵
	DynamicMatrix qMatrix;

	//QR分解
	DynamicQRDecomposition QRDecomp;

	//hessen格式化
	DynamicHessenbergFormular dHessenbergForm;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

};


#endif /* TRANSFORMATION_BASIC_DYNAMICNORMALQRITERATION_H_ */
