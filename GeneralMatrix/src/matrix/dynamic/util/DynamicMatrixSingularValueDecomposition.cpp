/*
 * DynamicMatrixSingularValueDecomposition.cpp
 *
 *  Created on: 2017年3月24日
 *      Author: looke
 */

#include <dynamic/util/DynamicMatrixSingularValueDecomposition.h>
#include <dynamic/DynamicMatrix.h>
#include <iostream>
#include "math.h"
using namespace std;

/*
 * SVD分解 构造函数
 */
DynamicMatrixSingularValueDecomposition::DynamicMatrixSingularValueDecomposition(BasicMatrix* input_matrix):MatrixSingularValueDecomposition(input_matrix),eigenValueProc(input_matrix),multiplyProc(input_matrix, input_matrix)
{
	//this->MatrixSingularValueDecomposition();
	this->init(input_matrix);
};

/*
 * SVD分解 初始化过程
 *
 * 输入m*n操作矩阵
 *
 */
void DynamicMatrixSingularValueDecomposition::init(BasicMatrix* input_matrix)
{
	this->fPrecision = 0.000001;

	//初始化操作矩阵
	this->opMatrix = DynamicMatrix(input_matrix->rowNum, input_matrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(input_matrix);
	this->p_opMatrix = &this->opMatrix;
	/*
	for(int i=0; i<input_matrix->rowNum; i++)
	{
		for(int j=0; j<input_matrix->columnNum; j++)
		{
			this->opMatrix.setMatrixElement(i,j, input_matrix->getMatrixElement(i, j));
		}
	}
	*/

	//初始化操作矩阵的转置
	this->opTMatrix = DynamicMatrix(input_matrix->columnNum, input_matrix->rowNum);
	for(int i=0; i<input_matrix->columnNum; i++)
	{
		for(int j=0; j<input_matrix->rowNum; j++)
		{
			this->opTMatrix.setMatrixElement(i,j, input_matrix->getMatrixElement(j, i));
		}
	}
	this->p_opTMatrix = &this->opTMatrix;

	//初始化乘法器和特征值解算器
	this->p_multiplyProc = &this->multiplyProc;
	this->p_eigenValueProc = &this->eigenValueProc;

	//m*m matrix
	this->UMatrix = DynamicMatrix(input_matrix->rowNum, input_matrix->rowNum);
	this->p_UMatrix = &this->UMatrix;
	//m*m matrix
	this->U_eigenValueMatrix = DynamicMatrix(input_matrix->rowNum, input_matrix->rowNum);
	this->p_U_eigenValueMatrix = &this->U_eigenValueMatrix;
	//m*n matrix
	this->SingularValueMatrix = DynamicMatrix(input_matrix->rowNum, input_matrix->columnNum);
	this->p_SingularValueMatrix = &this->SingularValueMatrix;
	//n*n matrix
	this->VMatrix = DynamicMatrix(input_matrix->columnNum, input_matrix->columnNum);
	this->p_VMatrix = &this->VMatrix;
	//n*n matrix
	this->V_eigenValueMatrix = DynamicMatrix(input_matrix->columnNum, input_matrix->columnNum);
	this->p_V_eigenValueMatrix = &this->V_eigenValueMatrix;

};

/*
 * 重新装载
 */
void DynamicMatrixSingularValueDecomposition::reload(BasicMatrix* input_matrix)
{
	//若输入矩阵与原操作矩阵行列数一致，则简单初始化，节省内存
	if(this->opMatrix.rowNum == input_matrix->rowNum &&
	   this->opMatrix.columnNum == input_matrix->columnNum)
	{

		//初始化操作矩阵
		this->opMatrix.copyMatrixElementNoCheck(input_matrix);

		/*
		for(int i=0; i<input_matrix->rowNum; i++)
		{
			for(int j=0; j<input_matrix->columnNum; j++)
			{
				this->opMatrix.setMatrixElement(i,j, input_matrix->getMatrixElement(i, j));
			}
		}
		*/

		//初始化操作矩阵的转置
		for(int i=0; i<input_matrix->columnNum; i++)
		{
			for(int j=0; j<input_matrix->rowNum; j++)
			{
				this->opTMatrix.setMatrixElement(i,j, input_matrix->getMatrixElement(j, i));
			}
		}

		//重置计算结果矩阵
		//m*m matrix
		this->UMatrix.resetMatrixToI();
		//m*m matrix
		this->U_eigenValueMatrix.resetMatrixToI();

		//m*n matrix
		this->SingularValueMatrix.resetMatrixToZero();

		//n*n matrix
		this->VMatrix.resetMatrixToI();
		//n*n matrix
		this->V_eigenValueMatrix.resetMatrixToI();
	}
	else
	{
		this->init(input_matrix);
	}
};

