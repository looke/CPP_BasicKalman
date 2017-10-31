/*
 * Static1510MatrixTransposer.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */
//#include "matrix/static1015/util/Static1015Matrix.h"
#include <static/util/StaticMatrixTransposer.h>
#include <iostream>
using namespace std;
StaticMatrixTransposer::StaticMatrixTransposer(BasicMatrix* input_matrix):MatrixTransposer(input_matrix)
{
	this->init(input_matrix);
};

void StaticMatrixTransposer::init(BasicMatrix* input_matrix)
{
	rowNumber = input_matrix->rowNum;
	columnNumber = input_matrix->columnNum;

	opMatrix = StaticMatrix(rowNumber, columnNumber);
	p_opMatrix = &opMatrix;
	//p_opMatrix = opMatrix.getCurrentMatrixPointer();
	p_opMatrix->copyMatrixElementNoCheck(input_matrix);

	opMatrixTransposed = StaticMatrix(columnNumber, rowNumber);
	p_opMatrixTransposed = &opMatrixTransposed;
	//p_opMatrixTransposed = opMatrixTransposed.getCurrentMatrixPointer();
	p_opMatrixTransposed->resetMatrixToI();
};

/*
 * 重新装填
 */
void StaticMatrixTransposer::reload(BasicMatrix* input_opMatrix)
{
	if(input_opMatrix->rowNum == rowNumber && input_opMatrix->columnNum==columnNumber)
	{
		this->p_opMatrix->copyMatrixElementNoCheck(input_opMatrix);
		this->p_opMatrixTransposed->resetMatrixToI();
	}
	else
	{
		init(input_opMatrix);
	}
};
