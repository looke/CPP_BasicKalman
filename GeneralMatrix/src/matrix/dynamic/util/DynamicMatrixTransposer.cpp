/*
 * MatrixTransposer.cpp
 *
 *  Created on: 2017��2��25��
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
 * ����װ��
 */
void DynamicMatrixTransposer::reload(BasicMatrix* input_matrix)
{
	//�ж���������Ƿ���ԭ����������һ�£���һ�£��򿽱��������ݼ��ɣ���ʡ�ڴ�
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
