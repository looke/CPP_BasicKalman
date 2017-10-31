/*
 * StaticMatrix.h
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#ifndef MATRIX_STATIC_STATICMATRIX_H_
#define MATRIX_STATIC_STATICMATRIX_H_

#include "basic\BasicMatrix.h"
#include "..\vector\static\StaticVector.h"

class StaticMatrix:public BasicMatrix
{
public:
	StaticMatrix();
	StaticMatrix(int inputRowNum, int inputColumnNum);

	//int rowNum;
	//int columnNum;

	void setMatrixElement(int rNum, int cNum, double val);
	double getMatrixElement(int rNum, int cNum);
	//��ȡ����ָ��Ԫ�ص�ֵ(��Ԫ��ֵ�������Σ�С�ھ��ȵ�ֱֵ�ӷ���0)
	double getMatrixElementRegulared(int rNum, int cNum, double lowEdge);

	void printMatrix();

	//������
	void swapRow(int from, int to);

	//������
	void swapColumn(int from, int to);

	//�����Խ�����Ԫ
	void swapDiagElement(int from, int to);

	//����������Ϊ��λ����
	void resetMatrixToI();

	//����������Ϊ��λ����
	void resetMatrixToZero();

	//��ȡָ��������
	BasicVector* getColumnVector(int columnNo);

	//��ȡָ��������
	BasicVector* getRowVector(int rowNo);

	//��ȡָ��������
	BasicVector* getSubMatrixColumnVector(int subMatrixIndex, int columnNo);

	//��ȡָ��������
	BasicVector* getSubMatrixRowVector(int subMatrixIndex, int rowNo);

	//��ȡָ���Խ��Ӿ���hessenberg������
	BasicVector* getSubMatrixHessenColumnVector(int subMatrixIndex);

private:

	double matrixNxN[20][20];
	StaticVector columnVector;
	StaticVector rowVector;
	void initMatrix();

};

#endif /* MATRIX_STATIC_STATICMATRIX_H_ */
