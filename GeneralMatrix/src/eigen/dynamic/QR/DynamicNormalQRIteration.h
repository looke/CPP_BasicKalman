/*
 * DynamicNormalQRIteration.h
 *
 *  Created on: 2017��5��8��
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
	//��������
	DynamicMatrix opMatrix;

	//Hessenberg����
	DynamicMatrix opHessenbergMatrix;

	//Q ����
	DynamicMatrix qMatrix;

	//QR�ֽ�
	DynamicQRDecomposition QRDecomp;

	//hessen��ʽ��
	DynamicHessenbergFormular dHessenbergForm;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

};


#endif /* TRANSFORMATION_BASIC_DYNAMICNORMALQRITERATION_H_ */
