/*
 * DynamicMatrix.h
 *
 *  Created on: 2017��2��18��
 *      Author: looke
 */

#ifndef DYNAMICMATRIX_H_
#define DYNAMICMATRIX_H_

#include "basic\BasicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"

class DynamicMatrix:public BasicMatrix
{
public:
	DynamicMatrix();
	DynamicMatrix(int inputRowNum, int inputColumnNum);

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

	//���������������Ԫ�ص�����ֵ

	//��������Ԫ��(���������)
	//bool copyMatrixElementWithCheck(BasicMatrix* input_Matrix);

	//��������Ԫ��(�����������)
	//void copyMatrixElementNoCheck(BasicMatrix* input_Matrix);

private:
	double **matrixPointer;
	DynamicVector columnVector;
	DynamicVector rowVector;
	void initMatrix();

};
#endif /* DYNAMICMATRIX_H_ */
