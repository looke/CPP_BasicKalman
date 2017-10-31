/*
 * StaticMatrixSquareRootSolver.cpp
 *
 *  Created on: 2017年3月11日
 *      Author: looke
 */
#include <static/util/StaticMatrixSquareRootSolver.h>
#include <iostream>
using namespace std;
/*
 * 方阵求平方根函数初始化，复制入参矩阵的内容
 * 判断是否方阵
 * 初始化行列数
 * 初始化矩阵
 * 生成伴随单位矩阵Z
 */
StaticMatrixSquareRootSolver::StaticMatrixSquareRootSolver(BasicMatrix* input_opMatrix):MatrixSquareRootSolver(input_opMatrix),inverser(input_opMatrix),YMatrix(),ZMatrix(),tempYMatrix(),tempZMatrix()
{
	this->init(input_opMatrix);
};

void StaticMatrixSquareRootSolver::init(BasicMatrix* input_opMatrix)
{
	//初始化行列数
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;
	this->maxDiff = 10000;
	this->threshold = 0.01;	//精度要求
	this->maxIterationTime = 10; //最多迭代10次
	this->iterationTime = 0; //当前迭代数

	this->isSquareMatrix = false;

	if(rowNumber == columnNumber)
	{
		this->isSquareMatrix = true;
	}

	//初始化求逆矩阵对象
	this->p_inverser = &this->inverser;

	//初始化操作矩阵
	this->YMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_YMatrix = YMatrix.getCurrentMatrixPointer();
	this->p_YMatrix = &YMatrix;
	this->p_YMatrix->copyMatrixElementNoCheck(input_opMatrix);

	//初始化中间计算值矩阵
	this->tempYMatrix = StaticMatrix(rowNumber, columnNumber);
	this->tempZMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_tempYMatrix = tempYMatrix.getCurrentMatrixPointer();
	this->p_tempYMatrix = &tempYMatrix;
	//this->p_tempZMatrix = tempZMatrix.getCurrentMatrixPointer();
	this->p_tempZMatrix = &tempZMatrix;

	//生成伴随单位矩阵Z
	this->ZMatrix = StaticMatrix(rowNumber, columnNumber);
	//this->p_ZMatrix = ZMatrix.getCurrentMatrixPointer();
	this->p_ZMatrix = &ZMatrix;
	this->p_ZMatrix->resetMatrixToI();

};

void StaticMatrixSquareRootSolver::reload(BasicMatrix* input_opMatrix)
{
	//重新装填的矩阵行列数与原矩阵行列数相同,不需要重新声明对象,节省内存
	if(input_opMatrix->rowNum == rowNumber && input_opMatrix->columnNum == columnNumber)
	{
		this->maxDiff = 10000;
		this->iterationTime = 0; //当前迭代数
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
