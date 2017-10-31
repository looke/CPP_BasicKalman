/*
 * DynamicDoubleShiftQRIteration.h
 *
 *  Created on: 2017��5��18��
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQRITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQRITERATION_H_

#include "..\eigen\basic\QR\DoubleShiftQRIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\dynamic\util\DynamicMatrixTransposer.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"


class DynamicDoubleShiftQRIteration:public DoubleShiftQRIteration
{
public:

	DynamicDoubleShiftQRIteration(BasicMatrix* p_intput_OpMatrix);

	void init(BasicMatrix* p_intput_OpMatrix);
	void reload(BasicMatrix* p_intput_OpMatrix);

protected:

	//��������
	DynamicMatrix opMatrix;

	//Hessenberg����
	DynamicMatrix opHessenbergMatrix;

	//����ת�����������
	DynamicVector transVectorForQStep;
	DynamicVector transVectorForQ_LastStep;

	//Q ���� ��ʽ���� �ֲ� Q�����ҳ�OP���� nxn
	DynamicMatrix QMatrix_Implicit_Step;
	//QT ���� ��ʽ���� �ֲ� QT�������OP���� nxn
	DynamicMatrix QTMatrix_Implicit_Step;

	//Q ���� ��ʽ���� ���� Q�����ҳ�OP���� nxn
	DynamicMatrix QMatrix_Implicit_Total;
	//QT ���� ��ʽ���� ���� QT�������OP���� nxn
	DynamicMatrix QTMatrix_Implicit_Total;

	//Qi �Ӿ��� ��ʽ���� �ֲ� Q�����ҳ�OP���� 3x3
	DynamicMatrix QSubMatrix_Implicit_Step;
	//Qn-1 �Ӿ��� ��ʽ���� �ֲ� Q�����ҳ�OP���� 2x2
	DynamicMatrix QSubMatrix_Implicit_LastStep;

	//QTi �Ӿ��� ��ʽ���� �ֲ� QT�������OP���� 3x3
	DynamicMatrix QTSubMatrix_Implicit_Step;
	//QTn-1 �Ӿ��� ��ʽ���� �ֲ� Q�����ҳ�OP���� 2x2
	DynamicMatrix QTSubMatrix_Implicit_LastStep;


	//QR�ֽ�
	//DynamicQRDecomposition dQRDecomp;

	//hessen��ʽ��
	DynamicHessenbergFormular dHessenbergForm;

	//Givens�任��
	DynamicGivensTransformation dGivensTrans;

	//Householder�任��
	DynamicHouseholderTransformation dHouseholderTrans;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

	//ת����
	DynamicMatrixTransposer dTransposer;
};

#endif /* EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQRITERATION_H_ */
