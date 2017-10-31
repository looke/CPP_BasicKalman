/*
 * Static1515MatrixEigenValueSolver.cpp
 *
 *  Created on: 2017��2��26��
 *      Author: looke
 */
#include <static/util/StaticMatrixEigenValueSolver.h>
#include "math.h"
#include <cmath>
#include <iostream>

using namespace std;

/*
 * ��ʼ������
 * ����������������������г�ʼ��
 * �������������Ϊ�ԳƷ��������������ʼ��
 */
StaticMatrixEigenValueSolver::StaticMatrixEigenValueSolver(BasicMatrix* input_opMatrix):MatrixEigenValueSolver(input_opMatrix),transposer(input_opMatrix),multiplier(input_opMatrix, input_opMatrix)
{

	this->init(input_opMatrix);
};

/*
 * ��ȷ���������Ϊ�ԳƷ������ô�init������ʼ��
 */
void StaticMatrixEigenValueSolver::init(BasicMatrix* input_opMatrix)
{
	this->isSymmetryMatrix = input_opMatrix->isInputSymmetryMatrix();

	//�ǶԳƷ���Ļ�����Ҫ����ʼ�� ��ӡ������˳�
	if(!this->isSymmetryMatrix)
	{
		cout << "StaticMatrixEigenValueSolver:not Symmm! no init proc." << endl;
		return;
	}

	this->p_transposer = &this->transposer;
	this->p_multiplier = &this->multiplier;

	this->rowAndColumnNumber = input_opMatrix->rowNum; //���������ֵ
	this->i_maxNoneDiaElementRow = -1; //�����Խ�Ԫ���Ԫ��������
	this->j_maxNoneDiaElementColumn = -1; //�����Խ�Ԫ���Ԫ��������
	this->precision = 0.00001; //����

	//��ʼ����������
	this->operateMatrix = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_operateMatrix = operateMatrix.getCurrentMatrixPointer();
	this->p_operateMatrix = &operateMatrix;
	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);

	//��ʼ��Jn
	this->Jn = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_Jn = Jn.getCurrentMatrixPointer();
	this->p_Jn = &Jn;

	this->Jn_transopse = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_Jn_transopse = Jn_transopse.getCurrentMatrixPointer();
	this->p_Jn_transopse = &Jn_transopse;

	this->eigenVectorMatrix = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_eigenVectorMatrix = eigenVectorMatrix.getCurrentMatrixPointer();
	this->p_eigenVectorMatrix = &eigenVectorMatrix;

	//��ʼ��������������Ϊ��λ����
	p_eigenVectorMatrix->resetMatrixToI();
};

void StaticMatrixEigenValueSolver::reload(BasicMatrix* input_opMatrix)
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

	//��ع��̾���Ԫ������
	this->p_Jn->resetMatrixToI();
	this->p_Jn_transopse->resetMatrixToI();
	this->p_eigenVectorMatrix->resetMatrixToI();

};
