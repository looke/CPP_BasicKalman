/*
 * HessenbergTriangleFormular.h
 *
 *  Created on: 2017��4��28��
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_HESSENBERGTRIANGLEFORMULAR_H_
#define TRANSFORMATION_BASIC_HESSENBERGTRIANGLEFORMULAR_H_

#include "..\matrix\basic\BasicMatrix.h"
//#include "..\vector\basic\BasicVector.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "GivensTransformation.h"


class HessenbergTriangleFormular
{
public:
	HessenbergTriangleFormular();
	HessenbergTriangleFormular(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);

	void initABMatrix();
	void formularABMatrix();
	void formularColumnVector(int columnIndex);

	void updateMatrixByQ();
	void updateMatrixByZ();

	void updateQZMatrix_Total();


	BasicMatrix* getMatrixA();
	BasicMatrix* getMatrixB();
	BasicMatrix* getHessenbergMatrixA();
	BasicMatrix* getTriangleMatrixB();
	BasicMatrix* getMatrixQ_Step();
	BasicMatrix* getMatrixZ_Step();
	BasicMatrix* getMatrixQ_Total();
	BasicMatrix* getMatrixZ_Total();


	virtual void init(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);
	virtual void reload(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);

	virtual ~HessenbergTriangleFormular(){};
protected:

	//ԭʼ��������A
	BasicMatrix* p_OpMatrix_A;
	//ԭʼ��������B
	BasicMatrix* p_OpMatrix_B;

	//Hessenberg����A
	BasicMatrix* p_OpHessenbergMatrix_A;

	//�����Ƿ���B
	BasicMatrix* p_OpTriangleMatrix_B;

	//����Q�任����,���ڻ�����˲�������
	BasicMatrix* p_QMatrix_Total;

	//����Z�任����,���ڻ����ҳ˲�������
	BasicMatrix* p_ZMatrix_Total;

	//����Q�任����,������˲�������
	BasicMatrix* p_QMatrix_Step;

	//����Z�任����,�����ҳ˲�������
	BasicMatrix* p_ZMatrix_Step;

	//Q* A Z--->Hessenberg����
	//Q* B Z--->�����Ǿ���

	//QR�ֽ�
	QRDecomposition* p_QRDecomp;

	//Givens�任
	GivensTransformation* p_GivensTrans;

	//�˷���
	MatrixMultiplier* p_Multiplier;

private:

};

#endif /* TRANSFORMATION_BASIC_HESSENBERGTRIANGLEFORMULAR_H_ */
