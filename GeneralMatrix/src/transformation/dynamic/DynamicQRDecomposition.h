/*
 * DynamicQRDecomposition.h
 *
 *  Created on: 2017年4月27日
 *      Author: looke
 */

#ifndef TRANSFORMATION_DYNAMIC_DYNAMICQRDECOMPOSITION_H_
#define TRANSFORMATION_DYNAMIC_DYNAMICQRDECOMPOSITION_H_

#include "..\transformation\basic\QRDecomposition.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"

class DynamicQRDecomposition : public QRDecomposition
{
public:
	//DynamicQRDecomposition();
	DynamicQRDecomposition(BasicMatrix* input_Matrix);

	void init(BasicMatrix* input_Matrix);
	void reload(BasicMatrix* input_Matrix);

protected:
	//乘法器
	DynamicMatrixMultiplier Multiplier;

	//householder变换
	DynamicHouseholderTransformation HouseholderTrans;

	//操作矩阵，经过迭代后将变成上对角矩阵
	DynamicMatrix OpMatrix;

	//householder矩阵，每次迭代使用
	DynamicMatrix householderMatrix;

	//Q矩阵
	DynamicMatrix QMatrix;

	//Q矩阵的转置(逆矩阵)
	DynamicMatrix QTMatrix;
};



#endif /* TRANSFORMATION_DYNAMIC_DYNAMICQRDECOMPOSITION_H_ */
