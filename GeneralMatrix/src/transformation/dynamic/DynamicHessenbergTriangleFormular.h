/*
 * DynamicHessenbergTriangleFormular.h
 *
 *  Created on: 2017��4��28��
 *      Author: looke
 */

#ifndef TRANSFORMATION_DYNAMIC_DYNAMICHESSENBERGTRIANGLEFORMULAR_H_
#define TRANSFORMATION_DYNAMIC_DYNAMICHESSENBERGTRIANGLEFORMULAR_H_

#include "..\transformation\basic\HessenbergTriangleFormular.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"

class DynamicHessenbergTriangleFormular : public HessenbergTriangleFormular
{
public:
	DynamicHessenbergTriangleFormular(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);

	void init(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);
	void reload(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);

protected:
	DynamicMatrix OpMatrix_A;
	DynamicMatrix OpMatrix_B;

	//Hessenberg����A
	DynamicMatrix OpHessenbergMatrix_A;
	//�����Ƿ���B
	DynamicMatrix OpTriangleMatrix_B;

	DynamicMatrix QMatrix_Total;
	DynamicMatrix ZMatrix_Total;

	DynamicMatrix QMatrix_Step;
	DynamicMatrix ZMatrix_Step;

	DynamicMatrixMultiplier dMultiplier;
	DynamicGivensTransformation dGivensTrans;

	//QR�ֽ�
	DynamicQRDecomposition dQRDecomp;

};

#endif /* TRANSFORMATION_DYNAMIC_DYNAMICHESSENBERGTRIANGLEFORMULAR_H_ */
