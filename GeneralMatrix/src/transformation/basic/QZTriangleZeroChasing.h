/*
 * QZTriangleZeroChasing.h
 * QZ��,B���� ���Խ���0Ԫ�½�
 * �������Ǿ���B�����Խ���0Ԫ�½������Խ������½�
 *
 * ����˼·:
 * ���������Ӿ���������У����ȴ�ԭ����(n��)��ʼ������ҵ����Խ���0Ԫ����һ����Ԫ�ϵ�����
 * Ȼ�������n-1���Ӿ������ͬ���Ĳ�����ֱ���޷��ҵ����Խ���0Ԫ
 *
 *
 *  Created on: 2017��4��28��
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_QZTRIANGLEZEROCHASING_H_
#define TRANSFORMATION_BASIC_QZTRIANGLEZEROCHASING_H_

//#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "..\transformation\basic\GivensTransformation.h"

class QZTriangleZeroChasing
{
public:
	QZTriangleZeroChasing();
	QZTriangleZeroChasing(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);

	//����Ԫ
	void deflate();

	BasicMatrix* getOpMatrix_A();
	BasicMatrix* getOpMatrix_B();

	BasicMatrix* getGivensMatrix_Q_Total();
	BasicMatrix* getGivensMatrix_Z_Total();

	BasicMatrix* getGivensMatrix_Q_Iterate();
	BasicMatrix* getGivensMatrix_Z_Iterate();

	BasicMatrix* getGivensMatrix_Q_Step();
	BasicMatrix* getGivensMatrix_Z_Step();

	BasicMatrix* getOpSubMatrix_A();
	BasicMatrix* getOpSubMatrix_B();

	BasicMatrix* getGivensSubMatrix_Q_Step();
	BasicMatrix* getGivensSubMatrix_Z_Step();

	virtual void init(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);
	virtual void reload(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);
	virtual ~QZTriangleZeroChasing(){};


	//���ݵ�ǰ�������� ���������Ӿ���
	void generateSubMatrix(int iterateNum);

	//����������,��A�Ӿ������� Z�任����
	void generateGivensSubMatrixForA(int index);

	//����������,��B�Ӿ������� G�任����
	void generateGivensSubMatrixForB(int index);

	//��A�Ӿ������� Z�任���� ʹ��A�Ӿ������һ�еĽǴ����Խ�ԪΪ0
	void generateGivensSubMatrixForA_last();


	//��Givens�任�Ӿ���������Ϊȫά�ȱ任����
	void upgradeGivensSubMatrix_Q();
	void upgradeGivensSubMatrix_Z();

	//���µ�������Givens�任����
	void updateGivensMatrix_Iterate_Q();
	void updateGivensMatrix_Iterate_Z();

	//���������ۺ�Givens�任����
	void updateGivensMatrix_Total_Q();
	void updateGivensMatrix_Total_Z();

	//ʹ��G�Ӿ������A�Ӳ�������
	void updateSubOpMatrix_A_By_Q();
	//ʹ��Z�Ӿ������A�Ӳ�������
	void updateSubOpMatrix_A_By_Z();
	//ʹ��G�Ӿ������B�Ӳ�������
	void updateSubOpMatrix_B_By_Q();
	//ʹ��Z�Ӿ������B�Ӳ�������
	void updateSubOpMatrix_B_By_Z();

	//ʹ��G�������A��������
	void updateOpMatrix_A_By_Q();
	//ʹ��Z�������A��������
	void updateOpMatrix_A_By_Z();
	//ʹ��G�������B��������
	void updateOpMatrix_B_By_Q();
	//ʹ��Z�������B��������
	void updateOpMatrix_B_By_Z();

	//���ݵ���������¶����Ӿ���������
	void resizeSubMatrix(int rowAndColumnNumber);


protected:
	//��0Ԫ���µľ���ײ�����
	int deflate_End_New;
	//ԭʼ����A Hessenberg
	BasicMatrix* p_OpMatrix_A;
	//ԭʼ����B ������
	BasicMatrix* p_OpMatrix_B;

	//��Givens�任����G-�����ۺϾ���
	BasicMatrix* p_GivensMatrixFor_Q_total;
	//��Givens�任����Z-�����ۺϾ���
	BasicMatrix* p_GivensMatrixFor_Z_total;

	//��Givens�任����G-�������̾���
	BasicMatrix* p_GivensMatrixFor_Q_iterate;
	//��Givens�任����Z-�������̾���
	BasicMatrix* p_GivensMatrixFor_Z_iterate;

	//��Givens�任����G-�������̾���
	BasicMatrix* p_GivensMatrixFor_Q_step;
	//��Givens�任����Z-�������̾���
	BasicMatrix* p_GivensMatrixFor_Z_step;


	//����A�Ӿ���
	BasicMatrix* p_OpSubMatrix_A;
	//����B�Ӿ���
	BasicMatrix* p_OpSubMatrix_B;

	//��Givens�任�Ӿ���G-�������̾���
	BasicMatrix* p_GivensSubMatrixFor_Q_step;
	//��Givens�任�Ӿ���Z-�������̾���
	BasicMatrix* p_GivensSubMatrixFor_Z_step;

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//Givens�任��
	GivensTransformation* p_GivensTrans;


};

#endif /* TRANSFORMATION_BASIC_QZTRIANGLEZEROCHASING_H_ */
