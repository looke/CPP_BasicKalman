/*
 * GeneralizedEigenSolverForReal.h
 *
 *  Created on: 2017��6��1��
 *      Author: looke
 */

#ifndef EIGEN_BASIC_GENERALIZEDEIGENSOLVERFORREAL_H_
#define EIGEN_BASIC_GENERALIZEDEIGENSOLVERFORREAL_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\eigen\basic\QZ\DoubleShiftQZIteration.h"
#include "..\eigen\basic\QZ\SingleShiftQZIteration.h"
#include "..\transformation\util\HessenbergDeflation.h"
#include "..\transformation\basic\QZTriangleZeroChasing.h"
class GeneralizedEigenSolverForReal
{
public:
	GeneralizedEigenSolverForReal();
	GeneralizedEigenSolverForReal(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);

	virtual void init(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);
	virtual void reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);
	virtual ~GeneralizedEigenSolverForReal(){};

	//����ԭʼhessenberg-Triangle��������
	void generateHTOpMatrix();

	//���ݽ��׵� ���ɽ��׵�Hessenberg-Tirangle����
	void generateDeflatedHTMatrixPair();

	//���ѽ��׵ı任���� ������Ϊȫ�ߴ�任����
	void upgradeDeflatedQZMatrix();

	//���������任���� �ϲ���Ϊ����任����
	void updateQZMatrixTotal();

	//ʹ��Q�������H-T�����
	void updateHTMatrixByQ();
	//ʹ��Z�����ҳ�H-T�����
	void updateHTMatrixByZ();

	//��������ֵ
	void calcEigenValue();

	//��ʼ������ֵ������ؾ���
	void initEigenCalcMatrix();

	//��������ж��߼�
	bool hasFinishedIteration();

	//H-T����� ����2x2�Խǿ��Ƿ�Ϊ��������ֵ�ж�
	bool isDiagonalBlockComplexEigen(BasicMatrix* p_Input_OpMatrix_A, BasicMatrix* p_Input_OpMatrix_B);

	//������Ϊ�Խǿ��Ժ����һ�����������Խ����ϵ�2x2�Խǿ���������ǻ�
	void lastStepIteration(int startIndex);

	//��ȡH-T�����
	BasicMatrix* getHessenbergMatrix();
	BasicMatrix* getTriangleMatrix();

	//��ȡQ\Z �ۺ�ת������
	BasicMatrix* getQMatrix_Total();
	BasicMatrix* getZMatrix_Total();

	//���Դ�ӡ��Q_Total * OP * Z_Total
	void showQxOPxZ();

protected:
	//�����������ָʾ����ʼ��Ϊ0
	int deflationStart;
	//�����յ�����ָʾ����ʼ��Ϊn-1
	int deflationEnd;

	//ԭʼ��������
	BasicMatrix* p_OpMatrix_A;
	BasicMatrix* p_OpMatrix_B;

	//ԭʼ����Hessenberg����
	BasicMatrix* p_OpMatrix_Hessenberg;
	//ԭʼ����Triangle����
	BasicMatrix* p_OpMatrix_Triangle;

	//ԭʼ�����ȫά�ȵ������任����
	BasicMatrix* p_QMatrix_Iteration;
	BasicMatrix* p_ZMatrix_Iteration;

	//ԭʼ�����ȫά������任����
	BasicMatrix* p_QMatrix_Total;
	BasicMatrix* p_ZMatrix_Total;

	//�ѽ��׵� ����Hessenberg����
	BasicMatrix* p_OpMatrix_Hessenberg_deflated;
	//�ѽ��׵� ����Triangle����
	BasicMatrix* p_OpMatrix_Triangle_deflated;

	//�ѽ��׾���ĵ������任����Q\Z
	BasicMatrix* p_QMatrix_Deflated_Iteration;
	BasicMatrix* p_ZMatrix_Deflated_Iteration;

	//���һ����ԶԽ���2x2�����Ĳ���
	BasicMatrix* p_LastStepMatrix_2x2_Hessenberg;
	BasicMatrix* p_LastStepMatrix_2x2_Triangle;

	//˫�ز�QZ������
	DoubleShiftQZIteration* p_DoubleShifeQZ;

	//����QR������
	SingleShiftQZIteration* p_SingleShifeQZ;

	//hessenberg-triangle��ʽ��
	HessenbergTriangleFormular* p_HessenbergTriangleFormular;

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//hessenberg���׵������
	HessenbergDeflation* p_HessenbergDeflation;

	//QZ-triangle 0Ԫ��λ
	QZTriangleZeroChasing* p_QZTriangleZeroChasing;

	//AB^-1 Ԫ�ؼ�����
	ABInverseCalculator* p_ABInvCalc;

	//��������ת�þ������ʱ���Զ���
	BasicMatrix* p_testForTemp_A_nxn;
	BasicMatrix* p_testForTemp_B_nxn;
	MatrixMultiplier* p_testMulti;

};



#endif /* EIGEN_BASIC_GENERALIZEDEIGENSOLVERFORREAL_H_ */
