/*
 * DynamicSingelShiftQRIteration.h
 *
 *  Created on: 2017��5��13��
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQRITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQRITERATION_H_

#include "..\eigen\basic\QR\SingleShiftQRIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixTransposer.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"

class DynamicSingleShiftQRIteration : public  SingleShiftQRIteration
{
public:
	DynamicSingleShiftQRIteration(BasicMatrix* p_intput_OpMatrix);

	void init(BasicMatrix* p_intput_OpMatrix);
	void reload(BasicMatrix* p_intput_OpMatrix);

protected:
	//��������
	DynamicMatrix opMatrix;

	//Hessenberg����
	DynamicMatrix opHessenbergMatrix;

	//Q ���� ��ʽ����
	DynamicMatrix QMatrix_Explicit;

	//Q ���� ��ʽ���� �ֲ� Q�����ҳ�OP����
	DynamicMatrix QMatrix_Implicit_Step;
	//QT ���� ��ʽ���� �ֲ� QT�������OP����
	DynamicMatrix QTMatrix_Implicit_Step;

	//Q ���� ��ʽ���� �ۺ� Q�����ҳ�OP����
	DynamicMatrix QMatrix_Implicit_Total;
	//QT ���� ��ʽ���� �ۺ� QT�������OP����
	DynamicMatrix QTMatrix_Implicit_Total;

	//QR�ֽ�
	DynamicQRDecomposition dQRDecomp;

	//hessen��ʽ��
	DynamicHessenbergFormular dHessenbergForm;

	//Givens�任��
	DynamicGivensTransformation dGivensTrans;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

	//ת����
	DynamicMatrixTransposer dTransposer;
};


#endif /* EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQRITERATION_H_ */
