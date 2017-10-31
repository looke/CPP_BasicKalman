/*
 * MatrixTransposer.cpp
 *
 *  Created on: 2017��2��25��
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
 * ����ת��
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
 * ��ӡ��ת�õľ���
 */
void MatrixTransposer::printMatrixTranspose()
{
	p_opMatrixTransposed->printMatrix();
};

BasicMatrix* MatrixTransposer::getTransposeMatrix()
{
	return this->p_opMatrixTransposed;
};
