/*
 * Static1515MatrixEigenValueSolver.cpp
 *
 *  Created on: 2017年2月26日
 *      Author: looke
 */
#include <static/util/StaticMatrixEigenValueSolver.h>
#include "math.h"
#include <cmath>
#include <iostream>

using namespace std;

/*
 * 初始化函数
 * 根据输入操作矩阵的情况进行初始化
 * 若输入操作矩阵为对称方阵，则进行正常初始化
 */
StaticMatrixEigenValueSolver::StaticMatrixEigenValueSolver(BasicMatrix* input_opMatrix):MatrixEigenValueSolver(input_opMatrix),transposer(input_opMatrix),multiplier(input_opMatrix, input_opMatrix)
{

	this->init(input_opMatrix);
};

/*
 * 在确认输入矩阵为对称方阵后调用此init函数初始化
 */
void StaticMatrixEigenValueSolver::init(BasicMatrix* input_opMatrix)
{
	this->isSymmetryMatrix = input_opMatrix->isInputSymmetryMatrix();

	//非对称方阵的话不需要做初始化 打印警告后退出
	if(!this->isSymmetryMatrix)
	{
		cout << "StaticMatrixEigenValueSolver:not Symmm! no init proc." << endl;
		return;
	}

	this->p_transposer = &this->transposer;
	this->p_multiplier = &this->multiplier;

	this->rowAndColumnNumber = input_opMatrix->rowNum; //方阵的行列值
	this->i_maxNoneDiaElementRow = -1; //非主对角元最大元素所在行
	this->j_maxNoneDiaElementColumn = -1; //非主对角元最大元素所在列
	this->precision = 0.00001; //精度

	//初始化操作矩阵
	this->operateMatrix = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_operateMatrix = operateMatrix.getCurrentMatrixPointer();
	this->p_operateMatrix = &operateMatrix;
	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);

	//初始化Jn
	this->Jn = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_Jn = Jn.getCurrentMatrixPointer();
	this->p_Jn = &Jn;

	this->Jn_transopse = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_Jn_transopse = Jn_transopse.getCurrentMatrixPointer();
	this->p_Jn_transopse = &Jn_transopse;

	this->eigenVectorMatrix = StaticMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	//this->p_eigenVectorMatrix = eigenVectorMatrix.getCurrentMatrixPointer();
	this->p_eigenVectorMatrix = &eigenVectorMatrix;

	//初始化特征向量矩阵为单位矩阵
	p_eigenVectorMatrix->resetMatrixToI();
};

void StaticMatrixEigenValueSolver::reload(BasicMatrix* input_opMatrix)
{
	//非对称方阵，不做初始化
	if(!input_opMatrix->isInputSymmetryMatrix())
	{
		cout << "reload stop. not Symmm! no reload proc." << endl;
		return;
	}

	//矩阵行列不一致，重新初始化
	if(this->rowAndColumnNumber != input_opMatrix->rowNum)
	{
		this->init(input_opMatrix);
		return;
	}

	//矩阵行列一致，则简单重置相关参数即可，节省内存

	this->i_maxNoneDiaElementRow = -1; //非主对角元最大元素所在行
	this->j_maxNoneDiaElementColumn = -1; //非主对角元最大元素所在列

	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);

	//相关过程矩阵元素重置
	this->p_Jn->resetMatrixToI();
	this->p_Jn_transopse->resetMatrixToI();
	this->p_eigenVectorMatrix->resetMatrixToI();

};
