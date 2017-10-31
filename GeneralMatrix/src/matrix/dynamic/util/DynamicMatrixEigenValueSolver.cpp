/*
 * DynamicMatrixEigenValueSolver.cpp
 *
 *  Created on: 2017��2��26��
 *      Author: looke
 */
#include <dynamic/util/DynamicMatrixEigenValueSolver.h>
#include <dynamic/DynamicMatrix.h>
#include "math.h"
#include <cmath>
#include <iostream>
//#include "basic\util\MatrixTransposer.h"
//#include "basic\util\MatrixMultiplier.h"
using namespace std;

/*
 * ��ʼ������
 * ����������������������г�ʼ��
 * �������������Ϊ�ԳƷ��������������ʼ��
 */
DynamicMatrixEigenValueSolver::DynamicMatrixEigenValueSolver(BasicMatrix* input_opMatrix):MatrixEigenValueSolver(input_opMatrix),transposer(input_opMatrix),multiplier(input_opMatrix,input_opMatrix)
{
	this->init(input_opMatrix);
};

/*
 * ��ȷ���������Ϊ�ԳƷ������ô�init������ʼ��
 */
void DynamicMatrixEigenValueSolver::init(BasicMatrix* input_opMatrix)
{
	//int row = input_opMatrix->rowNum;
	//int column = input_opMatrix->columnNum;

	this->isSymmetryMatrix = input_opMatrix->isInputSymmetryMatrix();

	//�ǶԳƷ���Ļ�����Ҫ����ʼ�� ��ӡ������˳�
	if(!this->isSymmetryMatrix)
	{
		cout << "not Symmm! no init proc." << endl;
		return;
	}

	this->rowAndColumnNumber = input_opMatrix->rowNum; //���������ֵ
	this->i_maxNoneDiaElementRow = -1; //�����Խ�Ԫ���Ԫ��������
	this->j_maxNoneDiaElementColumn = -1; //�����Խ�Ԫ���Ԫ��������
	this->precision = 0.000001; //����

	operateMatrix = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_operateMatrix = &operateMatrix;
	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);

	/*
	//��������������ĸ���Ԫ��
	for(int i=0; i<input_opMatrix->rowNum; i++)
	{
		for(int j=0; j<input_opMatrix->columnNum; j++)
		{
			operateMatrix.setMatrixElement(i,j, tempPointer[i][j]);
		}
	}
	*/
	//this->operateMatrixPointer = this->operateMatrix.getMatrixPointer();
	//��ʼ��Jn
	Jn = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_Jn = &Jn;
	Jn_transopse = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_Jn_transopse = &Jn_transopse;
	eigenVectorMatrix = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_eigenVectorMatrix = &eigenVectorMatrix;

	//��ʼ��������������Ϊ��λ����
	p_eigenVectorMatrix->resetMatrixToI();

	//��ʼ���˷�����ת����
	//this->transposer.reload(p_operateMatrix);
	p_transposer = &transposer;
	//this->multiplier = DynamicMatrixMultiplier(p_Jn,p_Jn_transopse);
	p_multiplier = &multiplier;
	//cout << "Symmm!" << endl;
	//cout << "eigenVectorMatrix:" << endl;
	//eigenVectorMatrix.printMatrix();
};

void DynamicMatrixEigenValueSolver::reload(BasicMatrix* input_opMatrix)
{
	//�ǶԳƷ��󣬲�����ʼ��
	if(!input_opMatrix->isInputSymmetryMatrix())
	{
		cout << "reload stop. not Symmm! no reload proc." << endl;
		return;
	}

	//�������в�һ�£����³�ʼ��
	if(this->rowAndColumnNumber != input_opMatrix->rowNum)
	{
		this->init(input_opMatrix);
		return;
	}

	//��������һ�£����������ز������ɣ���ʡ�ڴ�

	this->i_maxNoneDiaElementRow = -1; //�����Խ�Ԫ���Ԫ��������
	this->j_maxNoneDiaElementColumn = -1; //�����Խ�Ԫ���Ԫ��������

	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);
	/*
	//��������������ĸ���Ԫ��
	for(int i=0; i<input_opMatrix->rowNum; i++)
	{
		for(int j=0; j<input_opMatrix->columnNum; j++)
		{
			operateMatrix.setMatrixElement(i,j, tempPointer[i][j]);
		}
	}
	 */
	//��ع��̾���Ԫ������
	this->p_Jn->resetMatrixToI();
	this->p_Jn_transopse->resetMatrixToI();
	this->p_eigenVectorMatrix->resetMatrixToI();

};
