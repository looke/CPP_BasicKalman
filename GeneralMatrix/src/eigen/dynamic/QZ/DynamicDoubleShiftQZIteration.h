/*
 * DynamicDoubleShiftQZIteration.h
 *
 *  Created on: 2017��5��31��
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQZITERATION_H_
#define EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQZITERATION_H_

#include "..\eigen\basic\QZ\DoubleShiftQZIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"
#include "..\transformation\dynamic\DynamicHessenbergTriangleFormular.h"

class DynamicDoubleShiftQZIteration : public DoubleShiftQZIteration
{
public:

	DynamicDoubleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

protected:
	//�������� nxn
	DynamicMatrix OpMatrix_A;
	DynamicMatrix OpMatrix_B;

	//Hessenberg���� nxn
	DynamicMatrix OpMatrix_Hessenberg;
	//Triangle���� nxn
	DynamicMatrix OpMatrix_Triangle;

	//���ڼ�����ʽ˫��QZ��������ת������Qi������---3ά
	DynamicVector TransVectorForQStep_3;
	//���ڼ�����ʽ˫��QZ��������ת������Qn-1������---2ά
	DynamicVector TransVectorForQStep_2;

	//���ڼ�����ʽ˫��QZ��������ת������Zi������---3ά
	DynamicVector TransVectorForZStep_3;
	//���ڼ�����ʽ˫��QZ��������ת������Zi������---2ά
	DynamicVector TransVectorForZStep_2;

	//Q ȫ�ߴ���� ��ʽ���� �ֲ� Q�������OP����  nxn
	DynamicMatrix QMatrix_Implicit_Step;
	//Z ȫ�ߴ���� ��ʽ���� �ֲ� Z�����ҳ�OP����  nxn
	DynamicMatrix ZMatrix_Implicit_Step;

	//Q ȫ�ߴ���� ��ʽ����  ����Q�������OP����  nxn
	DynamicMatrix QMatrix_Implicit_Total;
	//Z ȫ�ߴ���� ��ʽ���� ����Z�����ҳ�OP����  nxn
	DynamicMatrix ZMatrix_Implicit_Total;

	//Qi �Ӿ��� ��ʽ���� �ֲ� Qi�������OP���� 3x3
	DynamicMatrix QSubMatrix_Implicit_Step_3;
	//Qi �Ӿ��� ��ʽ���� �ֲ� Qn-1�������OP���� 2x2
	DynamicMatrix QSubMatrix_Implicit_Step_2;

	//Zi �Ӿ��� ��ʽ���� �ֲ� QTi�����ҳ�OP���� 3x3
	DynamicMatrix ZSubMatrix_Implicit_Step_3;
	//Zi �Ӿ��� ��ʽ���� �ֲ� QT�����ҳ�OP���� 2x2
	DynamicMatrix ZSubMatrix_Implicit_Step_2;

	//hessenberg-triangle��ʽ��
	DynamicHessenbergTriangleFormular dHessenbergTriangleFormular;

	//QZ-triangle 0Ԫ��λ
	//QZTriangleZeroChasing* p_QZTriangleZeroChasing;

	//householder�任
	DynamicHouseholderTransformation dHouseholderTrans;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

	//AB^-1 Ԫ�ؼ�����
	ABInverseCalculator ABInvCalc;
};



#endif /* EIGEN_DYNAMIC_DYNAMICDOUBLESHIFTQZITERATION_H_ */
