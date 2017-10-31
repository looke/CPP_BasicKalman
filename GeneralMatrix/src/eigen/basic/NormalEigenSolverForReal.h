/*
 * NormalEigenSolverForReal.h
 *
 *  Created on: 2017��5��20��
 *      Author: looke
 */

#ifndef EIGEN_BASIC_NORMALEIGENSOLVERFORREAL_H_
#define EIGEN_BASIC_NORMALEIGENSOLVERFORREAL_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\eigen\basic\QR\DoubleShiftQRIteration.h"
#include "..\eigen\basic\QR\SingleShiftQRIteration.h"
#include "..\transformation\util\HessenbergDeflation.h"

class NormalEigenSolverForReal
{
public:
	NormalEigenSolverForReal();
	NormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~NormalEigenSolverForReal(){};

	//���Ҳ����½��׵�
	//bool findNewDeflationPoint();

	//���ݽ��׵� ���ɽ��׵�Hessenberg����
	void generateDeflatedHessenbergMatrix();

	//���ѽ��׵ı任���� ������Ϊȫ�ߴ�任����
	void upgradeDeflatedQQTMatrix();

	//���������任���� �ϲ���Ϊ����任����
	void updateQQTMatrixTotal();

	//����ԭʼhessenberg��������
	void generateHessenbergOpMatrix();

	//����ԭʼhessenberg��������
	void updateHessenbergOpMatrix();

	//��������ֵ
	void calcEigenValue();

	//��ʼ������ֵ������ؾ���
	void initEigenCalcMatrix();

	//��������ж��߼�
	bool hasFinishedIteration();

	//2x2�Խǿ��Ƿ�Ϊ��������ֵ�ж�
	bool isDiagonalBlockComplexEigen(BasicMatrix* p_Input_OpMatrix);

	//������Ϊ�Խǿ��Ժ����һ�����������Խ����ϵ�2x2�Խǿ���������ǻ�
	void lastStepIteration(int startIndex);

	BasicMatrix* getEigenValueMatrix();
	BasicMatrix* getOpHessenbergMatrix();

	BasicMatrix* getQTMatrix_Iteration();
	BasicMatrix* getQMatrix_Iteration();

	BasicMatrix* getQTMatrix_Total();
	BasicMatrix* getQMatrix_Total();

	BasicMatrix* getOpHessenbergMatrix_deflated();

	BasicMatrix* getQTMatrix_Deflated_Iteration();
	BasicMatrix* getQMatrix_Deflated_Iteration();

	//���Դ�ӡ��QT_Total * OP * Q
	void showQTOPxQ();
protected:

	//�����������ָʾ����ʼ��Ϊ0
	int deflationStart;
	//�����յ�����ָʾ����ʼ��Ϊn-1
	int deflationEnd;

	//ԭʼ��������
	BasicMatrix* p_OpMatrix;

	//ԭʼ���������Ӧ������ֵ����
	BasicMatrix* p_EigenValueMatrix;

	//ԭʼ����Hessenberg����
	BasicMatrix* p_OpHessenbergMatrix;

	//ԭʼ����ĵ������任���� QTΪ��˾��� QΪ�ҳ˾���
	BasicMatrix* p_QTMatrix_Iteration;
	BasicMatrix* p_QMatrix_Iteration;

	//ԭʼ���������任���� QTΪ��˾��� QΪ�ҳ˾���
	BasicMatrix* p_QTMatrix_Total;
	BasicMatrix* p_QMatrix_Total;

	//�ѽ��׵� ����Hessenberg����
	BasicMatrix* p_OpHessenbergMatrix_deflated;

	//�ѽ��׾���ĵ������任����Q\QT
	BasicMatrix* p_QTMatrix_Deflated_Iteration;
	BasicMatrix* p_QMatrix_Deflated_Iteration;

	//���һ����ԶԽ���2x2�����Ĳ���
	BasicMatrix* p_LastStepMatrix_2x2;

	//˫�ز�QR������
	DoubleShiftQRIteration* p_DoubleShifeQR;

	//����QR������
	SingleShiftQRIteration* p_SingleShifeQR;

	//hessen��ʽ��
	HessenbergFormular* p_HessenbergForm;

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//hessenberg���׵������
	HessenbergDeflation* p_HessenbergDeflation;

	//��������ת�þ������ʱ���Զ���
	BasicMatrix* p_testForTemp_nxn;
	MatrixMultiplier* p_testMulti;
};



#endif /* EIGEN_BASIC_NORMALEIGENSOLVERFORREAL_H_ */
