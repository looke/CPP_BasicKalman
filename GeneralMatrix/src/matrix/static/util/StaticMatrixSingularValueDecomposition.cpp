/*
 * Static1510MatrixSingularValueDecomposition.cpp
 *
 *  Created on: 2017��3��24��
 *      Author: looke
 */

#include <static/util/StaticMatrixSingularValueDecomposition.h>
#include <iostream>
#include "math.h"
using namespace std;

/*
 * SVD�ֽ� ���캯��
 */
StaticMatrixSingularValueDecomposition::StaticMatrixSingularValueDecomposition(BasicMatrix* input_matrix):MatrixSingularValueDecomposition(input_matrix),eigenValueProc(input_matrix),multiplyProc(input_matrix, input_matrix),opMatrix(),opTMatrix(),UMatrix(),U_eigenValueMatrix(),SingularValueMatrix(),VMatrix(),V_eigenValueMatrix()
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
void StaticMatrixSingularValueDecomposition::init(BasicMatrix* input_matrix)
{
	this->fPrecision = 0.000001;
	this->rowNumber = input_matrix->rowNum;
	this->columnNumber = input_matrix->columnNum;

	this->p_multiplyProc = &this->multiplyProc;
	this->p_eigenValueProc = &this->eigenValueProc;

	//��ʼ���������� m*n
	this->opMatrix = StaticMatrix(rowNumber,columnNumber);
	//this->p_opMatrix = opMatrix.getCurrentMatrixPointer();
	this->p_opMatrix = &opMatrix;
	this->p_opMatrix->copyMatrixElementNoCheck(input_matrix);


	//��ʼ�����������ת�� n*m
	this->opTMatrix = StaticMatrix(columnNumber,rowNumber);
	//this->p_opTMatrix = opTMatrix.getCurrentMatrixPointer();
	this->p_opTMatrix = &opTMatrix;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<15; j++)
		{
			this->p_opTMatrix->setMatrixElement(i,j, input_matrix->getMatrixElement(j, i));
		}
	}

	//this->multiplyProc.reload(&opMatrix,&opTMatrix);
	//this->eigenValueProc.reload(&opMatrix);

	//m*m matrix
	this->UMatrix = StaticMatrix(rowNumber,rowNumber);
	//this->p_UMatrix = UMatrix.getCurrentMatrixPointer();
	this->p_UMatrix = &UMatrix;

	//m*m matrix
	this->U_eigenValueMatrix = StaticMatrix(rowNumber,rowNumber);
	//this->p_U_eigenValueMatrix = U_eigenValueMatrix.getCurrentMatrixPointer();
	this->p_U_eigenValueMatrix = &U_eigenValueMatrix;

	//m*n matrix
	this->SingularValueMatrix = StaticMatrix(rowNumber,columnNumber);
	//this->p_SingularValueMatrix = SingularValueMatrix.getCurrentMatrixPointer();
	this->p_SingularValueMatrix = &SingularValueMatrix;

	//n*n matrix
	this->VMatrix = StaticMatrix(columnNumber,columnNumber);
	//this->p_VMatrix = VMatrix.getCurrentMatrixPointer();
	this->p_VMatrix = &VMatrix;

	//n*n matrix
	this->V_eigenValueMatrix = StaticMatrix(columnNumber,columnNumber);
	//this->p_V_eigenValueMatrix = V_eigenValueMatrix.getCurrentMatrixPointer();
	this->p_V_eigenValueMatrix = &V_eigenValueMatrix;

};

/*
 * ����װ��
 */
void StaticMatrixSingularValueDecomposition::reload(BasicMatrix* input_matrix)
{
	//�����������ԭ��������������һ�£���򵥳�ʼ������ʡ�ڴ�
	if(this->rowNumber == input_matrix->rowNum && this->columnNumber == input_matrix->columnNum)
	{
		//��ʼ����������
		this->p_opMatrix->copyMatrixElementNoCheck(input_matrix);


		//��ʼ�����������ת��
		for(int i=0; i<this->columnNumber; i++)
		{
			for(int j=0; j<this->rowNumber; j++)
			{
				this->p_opTMatrix->setMatrixElement(i,j, input_matrix->getMatrixElement(j, i));
			}
		}

		//���ü���������
		//m*m matrix
		this->p_UMatrix->resetMatrixToI();
		//m*m matrix
		this->p_U_eigenValueMatrix->resetMatrixToI();

		//m*n matrix
		this->p_SingularValueMatrix->resetMatrixToZero();

		//n*n matrix
		this->p_VMatrix->resetMatrixToI();
		//n*n matrix
		this->p_V_eigenValueMatrix->resetMatrixToI();

	}
	else
	{
		this->init(input_matrix);
	}
};

