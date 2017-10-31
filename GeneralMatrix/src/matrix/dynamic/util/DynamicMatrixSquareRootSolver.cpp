/*
 * DynamicMatrixSquareRootSolver.cpp
 *
 *  Created on: 2017年3月11日
 *      Author: looke
 */
#include <dynamic/util/DynamicMatrixSquareRootSolver.h>
#include <dynamic/DynamicMatrix.h>
#include <iostream>
using namespace std;
/*
 * 方阵求平方根函数初始化，复制入参矩阵的内容
 * 判断是否方阵
 * 初始化行列数
 * 初始化矩阵
 * 生成伴随单位矩阵Z
 */
DynamicMatrixSquareRootSolver::DynamicMatrixSquareRootSolver(BasicMatrix* input_opMatrix):MatrixSquareRootSolver(input_opMatrix),inverser(input_opMatrix)
{
	this->init(input_opMatrix);
};

void DynamicMatrixSquareRootSolver::init(BasicMatrix* input_opMatrix)
{
	//初始化行列数
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;
	this->maxDiff = 10000;
	this->threshold = 0.01;	//精度要求
	this->maxIterationTime = 10; //最多迭代10次
	this->iterationTime = 0; //当前迭代数
	this->p_inverser = &this->inverser;
	//判断是否方阵
	if(this->rowNumber == this->columnNumber)
	{
		this->isSquareMatrix = true;
	}
	else
	{
		this->isSquareMatrix = false;
	}

	//初始化操作矩阵
	this->YMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_YMatrix = &this->YMatrix;
	//this->YMatrixPointer = YMatrix.getMatrixPointer();
	//拷贝待操作矩阵的各个元素
	YMatrix.copyMatrixElementNoCheck(input_opMatrix);

	//初始化中间计算值矩阵
	this->tempYMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_tempYMatrix = &this->tempYMatrix;
	this->tempZMatrix = DynamicMatrix(this->rowNumber, this->columnNumber);
	this->p_tempZMatrix = &this->tempZMatrix;
	//this->tempYMatrixPointer = tempYMatrix.getMatrixPointer();
	//this->tempZMatrixPointer = tempZMatrix.getMatrixPointer();

	//生成伴随单位矩阵Z
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
	//重新装填的矩阵行列数与原矩阵行列数相同,不需要重新声明对象,节省内存
	if(this->rowNumber == input_opMatrix->rowNum && this->columnNumber == input_opMatrix->columnNum)
	{
		this->maxDiff = 10000;
		this->iterationTime = 0; //当前迭代数
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
