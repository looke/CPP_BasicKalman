/*
 * DynamicMatrixEigenValueSolver.cpp
 *
 *  Created on: 2017年2月26日
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
 * 初始化函数
 * 根据输入操作矩阵的情况进行初始化
 * 若输入操作矩阵为对称方阵，则进行正常初始化
 */
DynamicMatrixEigenValueSolver::DynamicMatrixEigenValueSolver(BasicMatrix* input_opMatrix):MatrixEigenValueSolver(input_opMatrix),transposer(input_opMatrix),multiplier(input_opMatrix,input_opMatrix)
{
	this->init(input_opMatrix);
};

/*
 * 在确认输入矩阵为对称方阵后调用此init函数初始化
 */
void DynamicMatrixEigenValueSolver::init(BasicMatrix* input_opMatrix)
{
	//int row = input_opMatrix->rowNum;
	//int column = input_opMatrix->columnNum;

	this->isSymmetryMatrix = input_opMatrix->isInputSymmetryMatrix();

	//非对称方阵的话不需要做初始化 打印警告后退出
	if(!this->isSymmetryMatrix)
	{
		cout << "not Symmm! no init proc." << endl;
		return;
	}

	this->rowAndColumnNumber = input_opMatrix->rowNum; //方阵的行列值
	this->i_maxNoneDiaElementRow = -1; //非主对角元最大元素所在行
	this->j_maxNoneDiaElementColumn = -1; //非主对角元最大元素所在列
	this->precision = 0.000001; //精度

	operateMatrix = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_operateMatrix = &operateMatrix;
	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);

	/*
	//拷贝待操作矩阵的各个元素
	for(int i=0; i<input_opMatrix->rowNum; i++)
	{
		for(int j=0; j<input_opMatrix->columnNum; j++)
		{
			operateMatrix.setMatrixElement(i,j, tempPointer[i][j]);
		}
	}
	*/
	//this->operateMatrixPointer = this->operateMatrix.getMatrixPointer();
	//初始化Jn
	Jn = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_Jn = &Jn;
	Jn_transopse = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_Jn_transopse = &Jn_transopse;
	eigenVectorMatrix = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->p_eigenVectorMatrix = &eigenVectorMatrix;

	//初始化特征向量矩阵为单位矩阵
	p_eigenVectorMatrix->resetMatrixToI();

	//初始化乘法器和转置器
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
	/*
	//拷贝待操作矩阵的各个元素
	for(int i=0; i<input_opMatrix->rowNum; i++)
	{
		for(int j=0; j<input_opMatrix->columnNum; j++)
		{
			operateMatrix.setMatrixElement(i,j, tempPointer[i][j]);
		}
	}
	 */
	//相关过程矩阵元素重置
	this->p_Jn->resetMatrixToI();
	this->p_Jn_transopse->resetMatrixToI();
	this->p_eigenVectorMatrix->resetMatrixToI();

};
