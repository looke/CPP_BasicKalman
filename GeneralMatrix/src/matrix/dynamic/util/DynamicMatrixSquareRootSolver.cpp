/*
 * DynamicMatrixSquareRootSolver.cpp
 *
 *  Created on: 2017��3��11��
 *      Author: looke
 */
#include <dynamic/util/DynamicMatrixSquareRootSolver.h>
#include <dynamic/DynamicMatrix.h>
#include <iostream>
using namespace std;
/*
 * ������ƽ����������ʼ����������ξ��������
 * �ж��Ƿ���
 * ��ʼ��������
 * ��ʼ������
 * ���ɰ��浥λ����Z
 */
DynamicMatrixSquareRootSolver::DynamicMatrixSquareRootSolver(BasicMatrix* input_opMatrix):MatrixSquareRootSolver(input_opMatrix),inverser(input_opMatrix)
{
	this->init(input_opMatrix);
};

void DynamicMatrixSquareRootSolver::init(BasicMatrix* input_opMatrix)
{
	//��ʼ��������
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;
	this->maxDiff = 10000;
	this->threshold = 0.01;	//����Ҫ��
	this->maxIterationTime = 10; //������10��
	this->iterationTime = 0; //��ǰ������
	this->p_inverser = &this->inverser;
	//�ж��Ƿ���
	if(this->rowNumber == this->columnNumber)
	{
		this->isSquareMatrix = true;
	}
	else
	{
		this->isSquareMatrix = false;
	}

	//��ʼ����������
	this->YMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_YMatrix = &this->YMatrix;
	//this->YMatrixPointer = YMatrix.getMatrixPointer();
	//��������������ĸ���Ԫ��
	YMatrix.copyMatrixElementNoCheck(input_opMatrix);

	//��ʼ���м����ֵ����
	this->tempYMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_tempYMatrix = &this->tempYMatrix;
	this->tempZMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_tempZMatrix = &this->tempZMatrix;
	//this->tempYMatrixPointer = tempYMatrix.getMatrixPointer();
	//this->tempZMatrixPointer = tempZMatrix.getMatrixPointer();

	//���ɰ��浥λ����Z
	this->ZMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_ZMatrix = &this->ZMatrix;
	this->ZMatrix.resetMatrixToI();
	//this->ZMatrixPointer = this->ZMatrix.getMatrixPointer();
	/*
	for(int i=0; i<rowNumber; i++)
	{
		for(int j=0; j<columnNumber; j++)
		{
			if(i==j)
			{
				this->ZMatrix.setMatrixElement(i,j,1);
			}
			else
			{
				this->ZMatrix.setMatrixElement(i,j,0);
			}
		}
	}
	*/
};

void DynamicMatrixSquareRootSolver::reload(BasicMatrix* input_opMatrix)
{
	//����װ��ľ�����������ԭ������������ͬ,����Ҫ������������,��ʡ�ڴ�
	if(this->rowNumber == input_opMatrix->rowNum && this->columnNumber == input_opMatrix->columnNum)
	{
		this->maxDiff = 10000;
		this->iterationTime = 0; //��ǰ������
		this->YMatrix.copyMatrixElementNoCheck(input_opMatrix);
		this->tempYMatrix.resetMatrixToI();
		this->tempZMatrix.resetMatrixToI();
		this->ZMatrix.resetMatrixToI();
	}
	else
	{
		this->init(input_opMatrix);
	}
};
