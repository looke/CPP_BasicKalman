/*
 * MatrixTransposer.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */
#include <dynamic/DynamicMatrix.h>
#include <dynamic/util/DynamicMatrixTransposer.h>
#include <iostream>
using namespace std;
DynamicMatrixTransposer::DynamicMatrixTransposer(BasicMatrix* input_matrix):MatrixTransposer(input_matrix)
{
	this->init(input_matrix);
};

void DynamicMatrixTransposer::init(BasicMatrix* input_matrix)
{
	opMatrix = DynamicMatrix(input_matrix->rowNum, input_matrix->columnNum);
	p_opMatrix = &opMatrix;
	opMatrix.copyMatrixElementNoCheck(input_matrix);

	opMatrixTransposed = DynamicMatrix(input_matrix->rowNum, input_matrix->columnNum);
	p_opMatrixTransposed =&opMatrixTransposed;
};

/*
 * 重新装填
 */
void DynamicMatrixTransposer::reload(BasicMatrix* input_matrix)
{
	//判断输入矩阵是否与原矩阵行列数一致，若一致，则拷贝矩阵内容即可，节省内存
	if(input_matrix->rowNum == opMatrix.rowNum && input_matrix->columnNum == opMatrix.columnNum)
	{
		opMatrix.copyMatrixElementNoCheck(input_matrix);
		opMatrixTransposed.resetMatrixToI();
	}
	else
	{
		this->init(input_matrix);
	}
};
