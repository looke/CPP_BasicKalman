/*
 * DynamicMatrixEquationSolver.cpp
 *
 *  Created on: 2017Äê2ÔÂ19ÈÕ
 *      Author: looke
 */

#include <dynamic/util/DynamicMatrixEquationSolver.h>
#include <iostream>
#include <malloc.h>
#include "math.h"
#include "dynamic\DynamicMatrix.h"
using namespace std;

DynamicMatrixEquationSolver::DynamicMatrixEquationSolver(BasicMatrix* input_opMatrix):MatrixEquationSolver(input_opMatrix)
{
	this->init(input_opMatrix);
}

void DynamicMatrixEquationSolver::init(BasicMatrix* input_opMatrix)
{
	this->opMatrix = DynamicMatrix(input_opMatrix->rowNum, input_opMatrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(input_opMatrix);

	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;

	this->roots = (double *) malloc(input_opMatrix->columnNum * sizeof(double));
};

void DynamicMatrixEquationSolver::reload(BasicMatrix* input_opMatrix)
{
	if(input_opMatrix->rowNum == this->rowNumber && input_opMatrix->columnNum == this->columnNumber)
	{
		this->opMatrix.copyMatrixElementNoCheck(input_opMatrix);
	}
	else
	{
		this->init(input_opMatrix);
	}
};
