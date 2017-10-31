/*
 * MatrixSingularValueDecomposition.cpp
 *
 *  Created on: 2017��3��24��
 *      Author: looke
 */

#include "MatrixSingularValueDecomposition.h"
//#include <malloc.h>
#include <iostream>
#include "math.h"
using namespace std;

/*
 * SVD�ֽ� ���캯��
 */
MatrixSingularValueDecomposition::MatrixSingularValueDecomposition(BasicMatrix* input_matrix)
{
	//this->MatrixSingularValueDecomposition();
	this->init(input_matrix);
};

/*
 * SVD�ֽ� ��ʼ������
 *
 * ����m*n��������
 *
 */
void MatrixSingularValueDecomposition::init(BasicMatrix* input_matrix)
{

};

/*
 * ����װ��
 */
void MatrixSingularValueDecomposition::reload(BasicMatrix* input_matrix)
{

};

/*
 * ratio_engenValue:��������ֵ����������ʱ�Բ�����������ű���
 *
 * SVD�ֽ����
 * 1.����U=A*AT
 * 2.����U������ֵ����������
 * 3.����V=AT*A
 * 4.����V������ֵ����������
 * 5.�ϲ� U V����ֵ����
 * 6.����S
 *
 */
void MatrixSingularValueDecomposition::sigularValueDecomposition(int ratio_engenValue)
{
	//���� A*AT
	this->p_multiplyProc->reload(p_opMatrix,p_opTMatrix);
	this->p_multiplyProc->multiplyCalc();
	//A*AT�Ľ����ֵ��UMatrix
	this->p_UMatrix->copyMatrixElementNoCheck(p_multiplyProc->getMultiplyResult());

	cout << "-------------A*AT-------------" << endl;
	this->p_UMatrix->printMatrix();

	//����A*AT������ֵ����������
	this->p_eigenValueProc->reload(p_UMatrix);
	p_eigenValueProc->calcEigenValue(ratio_engenValue);

	//����������������UMatrix
	this->p_UMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenVectorMatrix());

	//��������ֵ����U_eigenValueMatrix
	this->p_U_eigenValueMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenValueMatrix());

	cout << "-------------A*AT EigenVector-------------" << endl;
	this->p_UMatrix->printMatrix();
	cout << "-------------A*AT EigenValue-------------" << endl;
	this->p_U_eigenValueMatrix->printMatrix();

	cout << "-----------------------------------------" << endl;

	//���� AT*A
	this->p_multiplyProc->reload(p_opTMatrix,p_opMatrix);
	this->p_multiplyProc->multiplyCalc();
	// AT*A�Ľ����ֵ��VMatrix
	this->p_VMatrix->copyMatrixElementNoCheck(p_multiplyProc->getMultiplyResult());
	cout << "-------------AT*A-------------" << endl;
	this->p_VMatrix->printMatrix();

	//����AT*A������ֵ����������
	this->p_eigenValueProc->reload(p_VMatrix);
	p_eigenValueProc->calcEigenValue(ratio_engenValue);

	//����������������UMatrix
	this->p_VMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenVectorMatrix());

	//��������ֵ����U_eigenValueMatrix
	this->p_V_eigenValueMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenValueMatrix());

	cout << "-------------AT*A EigenVector-------------" << endl;
	this->p_VMatrix->printMatrix();
	cout << "-------------AT*A EigenValue-------------" << endl;
	this->p_V_eigenValueMatrix->printMatrix();

	//��������ֵ��С����������ֵS����
	this->p_SingularValueMatrix->resetMatrixToZero();

	BasicMatrix* eigenValueMatrixPointer;
	if(p_U_eigenValueMatrix->rowNum > p_V_eigenValueMatrix->rowNum)
	{
		eigenValueMatrixPointer = p_U_eigenValueMatrix;
	}
	else
	{
		eigenValueMatrixPointer = p_V_eigenValueMatrix;
	}

	for(int i=0; i<p_SingularValueMatrix->rowNum && i<p_SingularValueMatrix->columnNum; i++)
	{
		//double������0�Աȣ�����fPrecision
		if(this->isDoubleEqual(eigenValueMatrixPointer->getMatrixElement(i,i), 0, this->fPrecision))
		{
			p_SingularValueMatrix->setMatrixElement(i,i,0);
		}
		else
		{
			p_SingularValueMatrix->setMatrixElement(i,i,sqrt(eigenValueMatrixPointer->getMatrixElement(i,i)));
		}
	}

	cout << "Singular Value Matrix:" << endl;
	this->p_SingularValueMatrix->printMatrix();
};

/*
void MatrixSingularValueDecomposition::sigularValueDecomposition(int ratio_engenValue)
{

};
*/

/*
 * ��ӡ��������
 */
void MatrixSingularValueDecomposition::printOpMatrix()
{
	this->p_opMatrix->printMatrix();
};

/*
 * ��ӡ���������ת��
 */
void MatrixSingularValueDecomposition::printOpTMatrix()
{
	this->p_opTMatrix->printMatrix();
};

/*
 * �жϸ������Ƿ���ȣ�����Ϊerror_max
 */
bool MatrixSingularValueDecomposition::isDoubleEqual(double f1, double f2, double error_max)
{
	double error = fabs(fabs(f1)-fabs(f2));
	if(error < error_max)
	{
		return 1;
	}
	else
		return 0;
};

BasicMatrix* MatrixSingularValueDecomposition::getUMatrix()
{
	return this->p_UMatrix;
};

BasicMatrix* MatrixSingularValueDecomposition::getSingularValueMatrix()
{
	return this->p_SingularValueMatrix;
};

BasicMatrix* MatrixSingularValueDecomposition::getVMatrix()
{
	return this->p_VMatrix;
};
