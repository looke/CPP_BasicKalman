/*
 * DynamicMatrixMultiplier.h
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#ifndef DYNAMICMATRIXMULTIPLIER_H_
#define DYNAMICMATRIXMULTIPLIER_H_
#include "basic\util\MatrixMultiplier.h"
#include "dynamic\DynamicMatrix.h"
class DynamicMatrixMultiplier:public MatrixMultiplier
{
public:
	DynamicMatrixMultiplier(BasicMatrix* leftOp, BasicMatrix* rightOp);

	void reload(BasicMatrix* leftOp, BasicMatrix* rightOp);
	void init(BasicMatrix* leftOp, BasicMatrix* rightOp);
	~DynamicMatrixMultiplier() {};
protected:

	//DynamicMatrix leftOpMatrix;	//左操作数矩阵
	//DynamicMatrix rightOpMatrix;//右操作数矩阵

	DynamicMatrix MultiResult;
};

#endif /* DYNAMICMATRIXMULTIPLIER_H_ */
