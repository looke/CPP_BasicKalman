/*
 * DynamicQRDecomposition.h
 *
 *  Created on: 2017��4��27��
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
	//�˷���
	DynamicMatrixMultiplier Multiplier;

	//householder�任
	DynamicHouseholderTransformation HouseholderTrans;

	//�������󣬾��������󽫱���϶ԽǾ���
	DynamicMatrix OpMatrix;

	//householder����ÿ�ε���ʹ��
	DynamicMatrix householderMatrix;

	//Q����
	DynamicMatrix QMatrix;

	//Q�����ת��(�����)
	DynamicMatrix QTMatrix;
};



#endif /* TRANSFORMATION_DYNAMIC_DYNAMICQRDECOMPOSITION_H_ */
