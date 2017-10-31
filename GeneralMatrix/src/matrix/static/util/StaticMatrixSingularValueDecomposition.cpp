/*
 * Static1510MatrixSingularValueDecomposition.cpp
 *
 *  Created on: 2017年3月24日
 *      Author: looke
 */

#include <static/util/StaticMatrixSingularValueDecomposition.h>
#include <iostream>
#include "math.h"
using namespace std;

/*
 * SVD分解 构造函数
 */
StaticMatrixSingularValueDecomposition::StaticMatrixSingularValueDecomposition(BasicMatrix* input_matrix):MatrixSingularValueDecomposition(input_matrix),eigenValueProc(input_matrix),multiplyProc(input_matrix, input_matrix),opMatrix(),opTMatrix(),UMatrix(),U_eigenValueMatrix(),SingularValueMatrix(),VMatrix(),V_eigenValueMatrix()
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
void StaticMatrixSingularValueDecomposition::init(BasicMatrix* input_matrix)
{
	this->fPrecision = 0.000001;
	this->rowNumber = input_matrix->rowNum;
	this->columnNumber = input_matrix->columnNum;

	this->p_multiplyProc = &this->multiplyProc;
	this->p_eigenValueProc = &this->eigenValueProc;

	//初始化操作矩阵 m*n
	this->opMatrix = StaticMatrix(rowNumber,columnNumber);
	//this->p_opMatrix = opMatrix.getCurrentMatrixPointer();
	this->p_opMatrix = &opMatrix;
	this->p_opMatrix->copyMatrixElementNoCheck(input_matrix);


	//初始化操作矩阵的转置 n*m
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
 * 重新装载
 */
void StaticMatrixSingularValueDecomposition::reload(BasicMatrix* input_matrix)
{
	//若输入矩阵与原操作矩阵行列数一致，则简单初始化，节省内存
	if(this->rowNumber == input_matrix->rowNum && this->columnNumber == input_matrix->columnNum)
	{
		//初始化操作矩阵
		this->p_opMatrix->copyMatrixElementNoCheck(input_matrix);


		//初始化操作矩阵的转置
		for(int i=0; i<this->columnNumber; i++)
		{
			for(int j=0; j<this->rowNumber; j++)
			{
				this->p_opTMatrix->setMatrixElement(i,j, input_matrix->getMatrixElement(j, i));
			}
		}

		//重置计算结果矩阵
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

