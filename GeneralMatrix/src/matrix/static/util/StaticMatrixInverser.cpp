/*
 * StaticMatrixInverser.cpp
 *
 *  Created on: 2017��2��27��
 *      Author: looke
 */

#include "static\util\StaticMatrixInverser.h"
/*
MatrixInverser::MatrixInverser()
{
};
*/
StaticMatrixInverser::StaticMatrixInverser(BasicMatrix* input_opMatrix):MatrixInverser(input_opMatrix)
{
	this->init(input_opMatrix);
};

/*
 * 	��ʼ���������������
 */
void StaticMatrixInverser::init(BasicMatrix* input_opMatrix)
{
	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;

	if(rowNumber == columnNumber)
	{
		isSquareMatrix = true;
	}

	operateMatrix = StaticMatrix(rowNumber, columnNumber);
	inverseMatrix = StaticMatrix(rowNumber, columnNumber);

	//this->p_operateMatrix = operateMatrix.getCurrentMatrixPointer();
	this->p_operateMatrix = &operateMatrix;
	this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);

	//this->p_inverseMatrix = inverseMatrix.getCurrentMatrixPointer();
	this->p_inverseMatrix = &inverseMatrix;
	this->p_inverseMatrix->resetMatrixToI();
};
/*
 * ����װ��������󣬳�ʼ���������
 * ���������������
 */
void StaticMatrixInverser::reload(BasicMatrix* input_opMatrix)
{
	if(input_opMatrix->rowNum == rowNumber && input_opMatrix->columnNum==columnNumber)
	{
		this->p_operateMatrix->copyMatrixElementNoCheck(input_opMatrix);
		this->p_inverseMatrix->resetMatrixToI();
	}
	else
	{
		init(input_opMatrix);
	}
};

