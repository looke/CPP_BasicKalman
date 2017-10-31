/*
 * StaticMatrixSquareRootSolver.cpp
 *
 *  Created on: 2017��3��11��
 *      Author: looke
 */
#include <static/util/StaticMatrixSquareRootSolver.h>
#include <iostream>
using namespace std;
/*
 * ������ƽ����������ʼ����������ξ��������
 * �ж��Ƿ���
 * ��ʼ��������
 * ��ʼ������
 * ���ɰ��浥λ����Z
 */
StaticMatrixSquareRootSolver::StaticMatrixSquareRootSolver(BasicMatrix* input_opMatrix):MatrixSquareRootSolver(input_opMatrix),inverser(input_opMatrix),YMatrix(),ZMatrix(),tempYMatrix(),tempZMatrix()
{
	this->init(input_opMatrix);
};

void StaticMatrixSquareRootSolver::init(BasicMatrix* input_opMatrix)
{
	//��ʼ��������
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;
	this->maxDiff = 10000;
	this->threshold = 0.01;	//����Ҫ��
	this->maxIterationTime = 10; //������10��
	this->iterationTime = 0; //��ǰ������

	this->isSquareMatrix = false;

	if(rowNumber == columnNumber)
	{
		this->isSquareMatrix = true;
	}

	//��ʼ������������
	this->p_inverser = &this->inverser;

	//��ʼ����������
	this->YMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_YMatrix = YMatrix.getCurrentMatrixPointer();
	this->p_YMatrix = &YMatrix;
	this->p_YMatrix->copyMatrixElementNoCheck(input_opMatrix);

	//��ʼ���м����ֵ����
	this->tempYMatrix = StaticMatrix(rowNumber, columnNumber);
	this->tempZMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_tempYMatrix = tempYMatrix.getCurrentMatrixPointer();
	this->p_tempYMatrix = &tempYMatrix;
	//this->p_tempZMatrix = tempZMatrix.getCurrentMatrixPointer();
	this->p_tempZMatrix = &tempZMatrix;

	//���ɰ��浥λ����Z
	this->ZMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_ZMatrix = ZMatrix.getCurrentMatrixPointer();
	this->p_ZMatrix = &ZMatrix;
	this->p_ZMatrix->resetMatrixToI();

};

void StaticMatrixSquareRootSolver::reload(BasicMatrix* input_opMatrix)
{
	//����װ��ľ�����������ԭ������������ͬ,����Ҫ������������,��ʡ�ڴ�
	if(input_opMatrix->rowNum == rowNumber && input_opMatrix->columnNum == columnNumber)
	{
		this->maxDiff = 10000;
		this->iterationTime = 0; //��ǰ������
		this->p_YMatrix->copyMatrixElementNoCheck(input_opMatrix);
		this->p_tempYMatrix->resetMatrixToI();
		this->p_tempZMatrix->resetMatrixToI();
		this->p_ZMatrix->resetMatrixToI();
	}
	else
	{
		init(input_opMatrix);
	}
};
