/*
 * SingelShiftQRIteration.h
 *
 *  Created on: 2017��5��13��
 *      Author: looke
 */

#ifndef EIGEN_BASIC_SINGLESHIFTQRITERATION_H_
#define EIGEN_BASIC_SINGLESHIFTQRITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixTransposer.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "..\transformation\basic\HessenbergFormular.h"
#include "..\transformation\basic\GivensTransformation.h"


class SingleShiftQRIteration
{
public:
	SingleShiftQRIteration();
	SingleShiftQRIteration(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~SingleShiftQRIteration(){};

	//������λ��QR���� ��ʽ
	void rayleigh_Quotient_EX_QRIteration();

	//������λ��QR���� ��ʽ 10�ε���
	void rayleigh_Quotient_IM_QRIteration();
	//������λ��QR���� ��ʽ ָ����������
	void rayleigh_Quotient_IM_QRIteration(int iterateNum);
	//������λ��QR���� ��ʽ ����
	void rayleigh_Quotient_IM_QRIteration_Step();

	//��ֵλ��QR���� ��ʽ
	void explicit_QRIteration(double input_shiftValue);
	//��ֵλ��QR���� ��ʽ����
	void explicit_QRIteration_Step(double input_shiftValue);

	//��ֵλ��QR���� ��ʽ
	void implicit_QRIteration(double input_shiftValue);
	//��ֵλ��QR���� ��ʽ����
	void implicit_QRIteration_Step(double input_shiftValue);

	//��ֵλ��QR���� ��ʽ ��ʼ��
	void initForImplicitQR(double input_shiftValue);

	//�����ۺ�ת������Q QT Total
	void updateQQTMatrix_Total_IM_QRIteration();

	//����hessenberg��������
	void generateHessenbergOpMatrix();

	BasicMatrix* getOpHessenbergMatrix();

	//��ȡ����ת������
	BasicMatrix* getQTMatrix_Total();
	BasicMatrix* getQMatrix_Total();

protected:

	//�Խ���ȫ��Ԫ�ؼ�ȥָ��ֵ
	//void diagonalSubtraction_Hessn(double subValue);
	//�Խ���ȫ��Ԫ�ؼ���ָ��ֵ
	//void diagonalAddition_Hessn(double addValue);



	//��ʽQR���� ����hessenberg��������
	void updateHessenbergOpMatrix_IM_QRIteration();

	//��������
	BasicMatrix* p_OpMatrix;

	//Hessenberg����
	BasicMatrix* p_OpHessenbergMatrix;

	//Q ���� ��ʽ����
	BasicMatrix* p_QMatrix_Explicit;

	//Q ���� ��ʽ���� �ֲ� Q�����ҳ�OP����
	BasicMatrix* p_QMatrix_Implicit_Step;
	//QT ���� ��ʽ���� �ֲ� QT�������OP����
	BasicMatrix* p_QTMatrix_Implicit_Step;

	//Q ���� ��ʽ���� �ۺ� Q�����ҳ�OP����
	BasicMatrix* p_QMatrix_Implicit_Total;
	//QT ���� ��ʽ���� �ۺ� QT�������OP����
	BasicMatrix* p_QTMatrix_Implicit_Total;

	//QR�ֽ�
	QRDecomposition* p_QRDecomp;

	//hessen��ʽ��
	HessenbergFormular* p_HessenbergForm;

	//Givens�任��
	GivensTransformation* p_GivensTrans;

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//ת����
	MatrixTransposer* p_Transposer;
};



#endif /* EIGEN_BASIC_SINGLESHIFTQRITERATION_H_ */
