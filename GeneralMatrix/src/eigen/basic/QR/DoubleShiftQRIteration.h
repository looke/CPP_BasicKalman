/*
 * DoubleShiftQRIteration.h
 *
 *  Created on: 2017��5��17��
 *      Author: looke
 */

#ifndef EIGEN_BASIC_DOUBLESHIFTQRITERATION_H_
#define EIGEN_BASIC_DOUBLESHIFTQRITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixTransposer.h"
#include "..\vector\basic\BasicVector.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "..\transformation\basic\HessenbergFormular.h"
#include "..\transformation\basic\GivensTransformation.h"
#include "..\transformation\basic\HouseholderTransformation.h"

class DoubleShiftQRIteration
{
public:
	DoubleShiftQRIteration();
	DoubleShiftQRIteration(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~DoubleShiftQRIteration(){};

	//Wilkinson˫λ��QR����  ��ʽ
	//void wilkinson_EX_QRIteration();

	//Wilkinson˫λ��QR���� ��ʽ
	void wilkinson_IM_QRIteration();
	//��Ϊ�����ӿڵ���ʹ��
	void wilkinson_IM_QRIteration_Single();

	BasicMatrix* getOpHessenbergMatrix();

	//��ȡ����ת������
	BasicMatrix* getQTMatrix_Total();
	BasicMatrix* getQMatrix_Total();

	//Wilkinson˫λ��QR���� ��ʽ -����
	void wilkinson_IM_QRIteration_Step();

	//Wilkinsonλ��QR���� ��ʽ ��ʼ��
	void initForWilkinsonImplicitQR();

	//Wilkinson˫λ��QR���� ��ʽ -��β
	void endForWilkinsonImplicitQR();

	//����hessenberg��������
	void generateHessenbergOpMatrix();

	//����hessenberg�������2x2�Ӿ��� ��������
	void generateWilkinsonShift();

	//B = (A-pI)*(A-tI); ����hessenberg���� ����˫����λ��ľ����һ��
	void generateBMatrixFirstColumn();

	//��Q�Ӿ�����ݵ�ǰ��������,����Ϊȫ�ߴ�Q����
	void upgradeQQTSubMatrix(int iterateNum);

	//��Qn-1�Ӿ���,����Ϊȫ�ߴ�Q����
	void upgradeQQTLastSubMatrix();

	//��ʽQR���� ����hessenberg��������
	void updateHessenbergOpMatrix_IM_QRIteration();

	//��ʽQR���� ��������ת������Q QT
	void updateTotalQQT();


protected:

	//p+t ����wilkinsonλ��ֵ�ĺ�
	double trace;

	//p*t ����wilkinsonλ��ֵ�ĳ˻�
	double determinant;

	// B = (A-pI)*(A-tI); ˫����λ��ľ����һ��
	double b11;
	double b21;
	double b31;

	//��������
	BasicMatrix* p_OpMatrix;

	//Hessenberg����
	BasicMatrix* p_OpHessenbergMatrix;

	//���ڼ�����ʽ˫��QR��������ת������Qi������---3ά
	BasicVector* p_TransVectorForQStep;
	//���ڼ�����ʽ˫��QR��������ת������Qn-1������---2ά
	BasicVector* p_TransVectorForQ_LastStep;

	//Q ���� ��ʽ���� �ֲ� Q�����ҳ�OP����
	BasicMatrix* p_QMatrix_Implicit_Step;
	//QT ���� ��ʽ���� �ֲ� QT�������OP����
	BasicMatrix* p_QTMatrix_Implicit_Step;

	//Q ���� ��ʽ����  ����Q�����ҳ�OP����
	BasicMatrix* p_QMatrix_Implicit_Total;
	//QT ���� ��ʽ���� ����QT�������OP����
	BasicMatrix* p_QTMatrix_Implicit_Total;


	//Qi �Ӿ��� ��ʽ���� �ֲ� Qi�����ҳ�OP���� 3x3
	BasicMatrix* p_QSubMatrix_Implicit_Step;

	//Qn-1 �Ӿ��� ��ʽ���� �ֲ� Qn-1�����ҳ�OP���� 2x2
	BasicMatrix* p_QSubMatrix_Implicit_LastStep;

	//QTi �Ӿ��� ��ʽ���� �ֲ� QTi�������OP���� 3x3
	BasicMatrix* p_QTSubMatrix_Implicit_Step;

	//QTn-1 �Ӿ��� ��ʽ���� �ֲ� QT�������OP���� 2x2
	BasicMatrix* p_QTSubMatrix_Implicit_LastStep;

	//QR�ֽ�
	//QRDecomposition* p_QRDecomp;

	//hessen��ʽ��
	HessenbergFormular* p_HessenbergForm;

	//Givens�任��
	GivensTransformation* p_GivensTrans;

	//householder�任
	HouseholderTransformation* p_HouseholderTrans;

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//ת����
	MatrixTransposer* p_Transposer;

};



#endif /* EIGEN_BASIC_DOUBLESHIFTQRITERATION_H_ */
