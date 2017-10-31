/*
 * DynamicGeneralizedEigenSolverForReal.h
 *
 *  Created on: 2017��6��2��
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICGENERALIZEDEIGENSOLVERFORREAL_H_
#define EIGEN_DYNAMIC_DYNAMICGENERALIZEDEIGENSOLVERFORREAL_H_
#include "..\eigen\basic\GeneralizedEigenSolverForReal.h"
#include "..\eigen\dynamic\QZ\DynamicDoubleShiftQZIteration.h"
#include "..\eigen\dynamic\QZ\DynamicSingleShiftQZIteration.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\transformation\dynamic\DynamicHouseholderTransformation.h"
#include "..\transformation\dynamic\DynamicHessenbergTriangleFormular.h"
#include "..\transformation\dynamic\DynamicQZTriangleZeroChasing.h"


class DynamicGeneralizedEigenSolverForReal:public GeneralizedEigenSolverForReal
{
public:
	//DynamicGeneralizedEigenSolverForReal();
	DynamicGeneralizedEigenSolverForReal(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

	void init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);
	void reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B);

protected:
	//ԭʼ��������
	DynamicMatrix OpMatrix_A;
	DynamicMatrix OpMatrix_B;

	//ԭʼ����Hessenberg����
	DynamicMatrix OpMatrix_Hessenberg;
	//ԭʼ����Triangle����
	DynamicMatrix OpMatrix_Triangle;

	//ԭʼ�����ȫά�ȵ������任����
	DynamicMatrix QMatrix_Iteration;
	DynamicMatrix ZMatrix_Iteration;

	//ԭʼ�����ȫά������任����
	DynamicMatrix QMatrix_Total;
	DynamicMatrix ZMatrix_Total;

	//�ѽ��׵� ����Hessenberg����
	DynamicMatrix OpMatrix_Hessenberg_deflated;
	//�ѽ��׵� ����Triangle����
	DynamicMatrix OpMatrix_Triangle_deflated;

	//�ѽ��׾���ĵ������任����Q\Z
	DynamicMatrix QMatrix_Deflated_Iteration;
	DynamicMatrix ZMatrix_Deflated_Iteration;

	//���һ����ԶԽ���2x2�����Ĳ���
	DynamicMatrix LastStepMatrix_2x2_Hessenberg;
	DynamicMatrix LastStepMatrix_2x2_Triangle;

	//˫�ز�QZ������
	DynamicDoubleShiftQZIteration dDoubleShifeQZ;

	//����QR������
	DynamicSingleShiftQZIteration dSingleShifeQZ;

	//hessenberg-triangle��ʽ��
	DynamicHessenbergTriangleFormular dHessenbergTriangleFormular;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

	//hessenberg���׵������
	HessenbergDeflation dHessenbergDeflation;

	//QZ-triangle 0Ԫ��λ
	DynamicQZTriangleZeroChasing dQZTriangleZeroChasing;

	//AB^-1 Ԫ�ؼ�����
	ABInverseCalculator ABInvCalc;

	//��������ת�þ������ʱ���Զ���
	DynamicMatrix testForTemp_A_nxn;
	DynamicMatrix testForTemp_B_nxn;
	DynamicMatrixMultiplier testMulti;
};



#endif /* EIGEN_DYNAMIC_DYNAMICGENERALIZEDEIGENSOLVERFORREAL_H_ */
