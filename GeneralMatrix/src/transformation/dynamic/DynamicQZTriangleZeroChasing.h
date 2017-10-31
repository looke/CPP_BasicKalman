/*
 * DynamicQZTriangleZeroChasing.h
 *
 *  Created on: 2017年5月6日
 *      Author: looke
 */

#ifndef TRANSFORMATION_DYNAMIC_DYNAMICQZTRIANGLEZEROCHASING_H_
#define TRANSFORMATION_DYNAMIC_DYNAMICQZTRIANGLEZEROCHASING_H_

#include "..\transformation\basic\QZTriangleZeroChasing.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"

class DynamicQZTriangleZeroChasing : public QZTriangleZeroChasing
{
public:
	//DynamicHessenbergTriangleDeflation();
	DynamicQZTriangleZeroChasing(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);

	void init(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);
	void reload(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);


	//void resizeSubMatrix(int rowAndColumnNumber);
protected:


	DynamicMatrix opMatrix_A;
	DynamicMatrix opMatrix_B;

	DynamicMatrix givensMatrixFor_Q_total;
	DynamicMatrix givensMatrixFor_Z_total;

	DynamicMatrix givensMatrixFor_Q_iterate;
	DynamicMatrix givensMatrixFor_Z_iterate;

	DynamicMatrix givensMatrixFor_Q_step;
	DynamicMatrix givensMatrixFor_Z_step;

	DynamicMatrix opSubMatrix_A;
	DynamicMatrix opSubMatrix_B;

	DynamicMatrix givensSubMatrixFor_Q_step;
	DynamicMatrix givensSubMatrixFor_Z_step;

	//乘法器
	DynamicMatrixMultiplier dMultiplier;

	//Givens变换器
	DynamicGivensTransformation dGivensTrans;


};



#endif /* TRANSFORMATION_DYNAMIC_DYNAMICQZTRIANGLEZEROCHASING_H_ */
