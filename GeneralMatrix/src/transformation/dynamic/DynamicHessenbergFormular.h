/*
 * DynamicHessenbergFormular.h
 *
 *  Created on: 2017��5��8��
 *      Author: looke
 */

#ifndef TRANSFORMATION_DYNAMIC_DYNAMICHESSENBERGFORMULAR_H_
#define TRANSFORMATION_DYNAMIC_DYNAMICHESSENBERGFORMULAR_H_

#include "..\transformation\basic\HessenbergFormular.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"

class DynamicHessenbergFormular : public HessenbergFormular
{

public:
	//DynamicHessenbergFormular();
	DynamicHessenbergFormular(BasicMatrix* p_InputOpMatrix);

	void init(BasicMatrix* p_InputOpMatrix);
	void reload(BasicMatrix* p_InputOpMatrix);
	void resizeSubMatrix(int rowAndColumnNumber);

protected:
	DynamicMatrix opMatrix;

	DynamicMatrix preTransMatrix;
	DynamicMatrix afterTransMatrix;

	DynamicMatrix transMatrix;
	DynamicMatrix subTransMatrix;

	//Householder�任
	DynamicHouseholderTransformation dHouseholderTrans;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;
};


#endif /* TRANSFORMATION_DYNAMIC_DYNAMICHESSENBERGFORMULAR_H_ */
