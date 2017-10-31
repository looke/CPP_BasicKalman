/*
 * DynamicSingleShiftQZIteration.h
 *
 *  Created on: 2017��5��28��
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQZITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQZITERATION_H_

#include "..\eigen\basic\QZ\SingleShiftQZIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\transformation\dynamic\DynamicHessenbergTriangleFormular.h"
#include "..\transformation\dynamic\DynamicGivensTransformation.h"
#include "..\transformation\dynamic\DynamicQZTriangleZeroChasing.h"


class DynamicSingleShiftQZIteration : public SingleShiftQZIteration
{
public:
	DynamicSingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);


protected:

	//ԭʼ��������A
	DynamicMatrix OpMatrix_A;
	//ԭʼ��������B
	DynamicMatrix OpMatrix_B;

	//Hessenberg ��������A
	DynamicMatrix OpMatrix_Hessenberg;
	//Triangle ��������B
	DynamicMatrix OpMatrix_Triangle;

	//Z ���� ��ʽ���� �ֲ� Z�����ҳ�OP����
	DynamicMatrix ZMatrix_Implicit_Step;
	//Q ���� ��ʽ���� �ֲ� Q�������OP����
	DynamicMatrix QMatrix_Implicit_Step;

	//Z ���� ��ʽ���� �ۺ� Z�����ҳ�OP����
	DynamicMatrix ZMatrix_Implicit_Total;
	//Q ���� ��ʽ���� �ۺ� Q�������OP����
	DynamicMatrix QMatrix_Implicit_Total;

	//hessenberg-triangle��ʽ��
	DynamicHessenbergTriangleFormular dHessenbergTriangleFormular;

	//QZ-triangle 0Ԫ��λ
	DynamicQZTriangleZeroChasing dQZTriangleZeroChasing;

	//Givens�任��
	DynamicGivensTransformation dGivensTrans;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

	//AB^-1 Ԫ�ؼ�����
	ABInverseCalculator ABInvCalc;
};

#endif /* EIGEN_DYNAMIC_DYNAMICSINGLESHIFTQZITERATION_H_ */
