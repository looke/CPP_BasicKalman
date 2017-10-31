/*
 * NormalQRIteration.h
 *
 *  Created on: 2017��5��8��
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
	//��������
	BasicMatrix* p_OpMatrix;

	//Hessenberg����
	BasicMatrix* p_OpHessenbergMatrix;

	//Q ����
	BasicMatrix* p_QMatrix;

	//QR�ֽ�
	QRDecomposition* p_QRDecomp;

	//hessen��ʽ��
	HessenbergFormular* p_HessenbergForm;

	//�˷���
	MatrixMultiplier* p_Multiplier;
};



#endif /* TRANSFORMATION_BASIC_NORMALQRITERATION_H_ */
