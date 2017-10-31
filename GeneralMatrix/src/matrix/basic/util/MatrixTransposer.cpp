/*
 * MatrixTransposer.cpp
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#include "MatrixTransposer.h"
#include <iostream>
using namespace std;
MatrixTransposer::MatrixTransposer(BasicMatrix* input_matrix)
{
	this->init(input_matrix);
};

void MatrixTransposer::init(BasicMatrix* input_matrix)
{

};

void MatrixTransposer::reload(BasicMatrix* input_matrix)
{
};

/*
 * 矩阵转置
 */
void MatrixTransposer::transposeMatrix()
{
	int rowNumber = p_opMatrix->rowNum;
	int columnNumber = p_opMatrix->columnNum;
	//loat** matrixPointer = opMatrix.getMatrixPointer();

	for(int i=0; i<columnNumber; i++)
	{
		for(int j=0; j<rowNumber; j++)
		{
			p_opMatrixTransposed->setMatrixElement(i, j, p_opMatrix->getMatrixElement(j,i));
		}
	}
};

/*
 * 打印已转置的矩阵
 */
void MatrixTransposer::printMatrixTranspose()
{
	p_opMatrixTransposed->printMatrix();
};

BasicMatrix* MatrixTransposer::getTransposeMatrix()
{
	return this->p_opMatrixTransposed;
};
