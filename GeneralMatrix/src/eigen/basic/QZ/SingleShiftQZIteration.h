/*
 * SingleShiftQZIteration.h
 *
 *  Created on: 2017��5��26��
 *      Author: looke
 */

#ifndef EIGEN_BASIC_SINGLESHIFTQZITERATION_H_
#define EIGEN_BASIC_SINGLESHIFTQZITERATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "..\transformation\basic\HessenbergTriangleFormular.h"
//#include "..\transformation\basic\QZTriangleZeroChasing.h"
#include "..\transformation\basic\GivensTransformation.h"
#include "..\eigen\util\ABInverseCalculator.h"

class SingleShiftQZIteration
{
public:
	SingleShiftQZIteration();
	SingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	virtual void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	virtual void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	virtual ~SingleShiftQZIteration(){};

	//����H-T���������
	void generateHessenTriangleOpMatrix();

	//����B^-1���2�� ���ڼ��㵥��λ��ֵ
	//void generateBinvLastTwoRow();

	//����AB^-1 ���½�Ԫ��ֵ ���ڵ���λ��
	//double generateABinvLastOne();

	//��ʼ����ʽ����
	void initForImplicitQZ(double input_ShiftValue);

	//��ֵλ��QZ���� ��ʽ����
	void implicit_QZIteration_Step(double input_shiftValue);

	//��ֵλ��QZ���� ��ʽ
	void implicit_QZIteration(double input_shiftValue);

	//��ֵrayleigh��λ��QZ���� ��ʽ ���
	void rayleigh_Quotient_IM_QZIteration(int iterateNum);

	//��ֵrayleigh��λ��QZ���� ��ʽ ����
	void rayleigh_Quotient_IM_QZIteration_Step();

	//ʹ��Q�������H-T�����
	void updateHTMatrixByQ();
	//ʹ��Z�����ҳ�H-T�����
	void updateHTMatrixByZ();

	//�����ۺ�ת������Q/Z Total(��Step�ϲ���Total)
	void updateQZMatrix_Total();

	//��ȡQ/Z ����ת������
	BasicMatrix* getQMatrix_Total();
	BasicMatrix* getZMatrix_Total();
protected:
	//B^-1 �������Ԫ��
	//double Binv_n_1_n_1;
	//double Binv_n_1_n;
	//double Binv_n_n;

	//ԭʼ��������A
	BasicMatrix* p_OpMatrix_A;
	//ԭʼ��������B
	BasicMatrix* p_OpMatrix_B;

	//Hessenberg ��������A
	BasicMatrix* p_OpMatrix_Hessenberg;
	//Triangle ��������B
	BasicMatrix* p_OpMatrix_Triangle;

	//Z ���� ��ʽ���� �ֲ� Z�����ҳ�OP����
	BasicMatrix* p_ZMatrix_Implicit_Step;
	//Q ���� ��ʽ���� �ֲ� Q�������OP����
	BasicMatrix* p_QMatrix_Implicit_Step;

	//Z ���� ��ʽ���� �ۺ� Z�����ҳ�OP����
	BasicMatrix* p_ZMatrix_Implicit_Total;
	//Q ���� ��ʽ���� �ۺ� Q�������OP����
	BasicMatrix* p_QMatrix_Implicit_Total;

	//hessenberg-triangle��ʽ��
	HessenbergTriangleFormular* p_HessenbergTriangleFormular;

	//QZ-triangle 0Ԫ��λ
	//QZTriangleZeroChasing* p_QZTriangleZeroChasing;

	//Givens�任��
	GivensTransformation* p_GivensTrans;

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//AB^-1 Ԫ�ؼ�����
	ABInverseCalculator* p_ABInvCalc;
};



#endif /* EIGEN_BASIC_SINGLESHIFTQZITERATION_H_ */
