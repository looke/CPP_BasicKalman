/*
 * DynamicNormalEigenSolverForReal.h
 *
 *  Created on: 2017��5��23��
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICNORMALEIGENSOLVERFORREAL_H_
#define EIGEN_DYNAMIC_DYNAMICNORMALEIGENSOLVERFORREAL_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\eigen\basic\NormalEigenSolverForReal.h"
#include "..\eigen\dynamic\QR\DynamicDoubleShiftQRIteration.h"
#include "..\eigen\dynamic\QR\DynamicSingleShiftQRIteration.h"
#include "..\transformation\dynamic\DynamicHessenbergFormular.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"

class DynamicNormalEigenSolverForReal : public NormalEigenSolverForReal
{
public:
	//DynamicNormalEigenSolverForReal();
	DynamicNormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix);

	void init(BasicMatrix* p_input_OpMatrix);
	void reload(BasicMatrix* p_input_OpMatrix);

protected:
	//ԭʼ��������
	DynamicMatrix OpMatrix;

	//ԭʼ���������Ӧ������ֵ����
	DynamicMatrix EigenValueMatrix;

	//ԭʼ����Hessenberg����
	DynamicMatrix OpHessenbergMatrix;

	//ԭʼ����ĵ������任����
	DynamicMatrix QTMatrix_Iteration;
	DynamicMatrix QMatrix_Iteration;

	//ԭʼ���������任����
	DynamicMatrix QTMatrix_Total;
	DynamicMatrix QMatrix_Total;

	//�ѽ��׵� ����Hessenberg����
	DynamicMatrix OpHessenbergMatrix_deflated;

	//�ѽ��׾���ĵ������任����Q\QT
	DynamicMatrix QTMatrix_Deflated_Iteration;
	DynamicMatrix QMatrix_Deflated_Iteration;

	//���һ����ԶԽ���2x2�����Ĳ���
	DynamicMatrix LastStepMatrix_2x2;

	//˫�ز�QR������
	DynamicDoubleShiftQRIteration dDoubleShifeQR;

	//˫�ز�QR������
	DynamicSingleShiftQRIteration dSingleShifeQR;

	//hessen��ʽ��
	DynamicHessenbergFormular dHessenbergForm;

	//�˷���
	DynamicMatrixMultiplier dMultiplier;

	//hessenberg���׵����
	HessenbergDeflation HessenbergDeflation;

	//��������ת�þ������ʱ���Զ���
	DynamicMatrix testForTemp_nxn;
	DynamicMatrixMultiplier testMulti;

};


#endif /* EIGEN_DYNAMIC_DYNAMICNORMALEIGENSOLVERFORREAL_H_ */
