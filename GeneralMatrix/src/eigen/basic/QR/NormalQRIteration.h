/*
 * NormalQRIteration.h
 *
 *  Created on: 2017年5月8日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_NORMALQRITERATION_H_
#define TRANSFORMATION_BASIC_NORMALQRITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "..\transformation\basic\HessenbergFormular.h"

class NormalQRIteration
{
public:
	NormalQRIteration();
	NormalQRIteration(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~NormalQRIteration(){};

	void QRIteration(int itNum);

protected:
	//操作矩阵
	BasicMatrix* p_OpMatrix;

	//Hessenberg矩阵
	BasicMatrix* p_OpHessenbergMatrix;

	//Q 矩阵
	BasicMatrix* p_QMatrix;

	//QR分解
	QRDecomposition* p_QRDecomp;

	//hessen格式化
	HessenbergFormular* p_HessenbergForm;

	//乘法器
	MatrixMultiplier* p_Multiplier;
};



#endif /* TRANSFORMATION_BASIC_NORMALQRITERATION_H_ */
