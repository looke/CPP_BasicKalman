/*
 * DynamicHessenbergTriangleDeflation.cpp
 *
 *  Created on: 2017年5月6日
 *      Author: looke
 */


#include <transformation/dynamic/DynamicQZTriangleZeroChasing.h>

/*
DynamicHessenbergTriangleDeflation::DynamicHessenbergTriangleDeflation()
{

};
*/

DynamicQZTriangleZeroChasing::DynamicQZTriangleZeroChasing(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B):dMultiplier(input_Op_Matrix_A,input_Op_Matrix_A),dGivensTrans()
{
	this->init(input_Op_Matrix_A, input_Op_Matrix_B);
};

void DynamicQZTriangleZeroChasing::init(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B)
{
	deflate_End_New = input_Op_Matrix_B->rowNum -1;
	opMatrix_A = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	opMatrix_A.copyMatrixElementNoCheck(input_Op_Matrix_A);

	opMatrix_B = DynamicMatrix(input_Op_Matrix_B->rowNum, input_Op_Matrix_B->columnNum);
	opMatrix_B.copyMatrixElementNoCheck(input_Op_Matrix_B);

	givensMatrixFor_Q_total = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensMatrixFor_Q_total.resetMatrixToI();
	givensMatrixFor_Z_total = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensMatrixFor_Z_total.resetMatrixToI();

	givensMatrixFor_Q_iterate = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensMatrixFor_Q_iterate.resetMatrixToI();
	givensMatrixFor_Z_iterate = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensMatrixFor_Z_iterate.resetMatrixToI();

	givensMatrixFor_Q_step = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensMatrixFor_Q_step.resetMatrixToI();
	givensMatrixFor_Z_step = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensMatrixFor_Z_step.resetMatrixToI();

	opSubMatrix_A = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	opSubMatrix_B = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);

	givensSubMatrixFor_Q_step = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensSubMatrixFor_Q_step.resetMatrixToI();
	givensSubMatrixFor_Z_step = DynamicMatrix(input_Op_Matrix_A->rowNum, input_Op_Matrix_A->columnNum);
	givensSubMatrixFor_Z_step.resetMatrixToI();

	//原始矩阵A Hessenberg
	p_OpMatrix_A = &this->opMatrix_A;
	//原始矩阵B 上三角
	p_OpMatrix_B = &this->opMatrix_B;

	//左Givens变换矩阵G-总体综合矩阵
	p_GivensMatrixFor_Q_total = &this->givensMatrixFor_Q_total;
	//右Givens变换矩阵Z-总体综合矩阵
	p_GivensMatrixFor_Z_total = &this->givensMatrixFor_Z_total;

	//左Givens变换矩阵G-迭代过程矩阵
	p_GivensMatrixFor_Q_iterate = &this->givensMatrixFor_Q_iterate;
	//右Givens变换矩阵Z-迭代过程矩阵
	p_GivensMatrixFor_Z_iterate = &this->givensMatrixFor_Z_iterate;

	//左Givens变换矩阵G-单步过程矩阵
	p_GivensMatrixFor_Q_step = &this->givensMatrixFor_Q_step;
	//右Givens变换矩阵Z-单步过程矩阵
	p_GivensMatrixFor_Z_step = &this->givensMatrixFor_Z_step;


	//左上A子矩阵
	p_OpSubMatrix_A = &this->opSubMatrix_A;
	//左上B子矩阵
	p_OpSubMatrix_B = &this->opSubMatrix_B;

	//左Givens变换子矩阵G-单步过程矩阵
	p_GivensSubMatrixFor_Q_step = &this->givensSubMatrixFor_Q_step;
	//右Givens变换子矩阵Z-单步过程矩阵
	p_GivensSubMatrixFor_Z_step = &this->givensSubMatrixFor_Z_step;

	//乘法器
	p_Multiplier = &this->dMultiplier;

	//Givens变换器
	p_GivensTrans = &this->dGivensTrans;

};

void DynamicQZTriangleZeroChasing::reload(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B)
{
	//A/B矩阵维度不变
	if(this->p_OpMatrix_A->rowNum == input_Op_Matrix_A->rowNum && this->p_OpMatrix_A->columnNum == input_Op_Matrix_A->columnNum
			&& this->p_OpMatrix_B->rowNum == input_Op_Matrix_B->rowNum && this->p_OpMatrix_B->columnNum && input_Op_Matrix_B->columnNum)
	{
		p_OpMatrix_A->copyMatrixElementNoCheck(input_Op_Matrix_A);
		p_OpMatrix_B->copyMatrixElementNoCheck(input_Op_Matrix_B);

		p_GivensMatrixFor_Q_total->resetMatrixToI();
		p_GivensMatrixFor_Z_total->resetMatrixToI();

		p_GivensMatrixFor_Q_iterate->resetMatrixToI();
		p_GivensMatrixFor_Z_iterate->resetMatrixToI();

		p_GivensMatrixFor_Q_step->resetMatrixToI();
		p_GivensMatrixFor_Z_step->resetMatrixToI();

		p_OpSubMatrix_A->resetMatrixToI();
		p_OpSubMatrix_B->resetMatrixToI();

		p_GivensSubMatrixFor_Q_step->resetMatrixToI();
		p_GivensSubMatrixFor_Z_step->resetMatrixToI();

		deflate_End_New = input_Op_Matrix_B->rowNum -1;
	}
	else
	{
		this->init(input_Op_Matrix_A, input_Op_Matrix_B);
	}
};

/*
void DynamicQZTriangleZeroChasing::resizeSubMatrix(int rowAndColumnNumber)
{
	opSubMatrix_A = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	opSubMatrix_B = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);

	givensSubMatrixFor_G_step = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	givensSubMatrixFor_G_step.resetMatrixToI();
	givensSubMatrixFor_Z_step = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	givensSubMatrixFor_Z_step.resetMatrixToI();
	//左上A子矩阵
	p_OpSubMatrix_A = &this->opSubMatrix_A;
	//左上B子矩阵
	p_OpSubMatrix_B = &this->opSubMatrix_B;

	//左Givens变换子矩阵G-单步过程矩阵
	p_GivensSubMatrixFor_G_step = &this->givensSubMatrixFor_G_step;
	//右Givens变换子矩阵Z-单步过程矩阵
	p_GivensSubMatrixFor_Z_step = &this->givensSubMatrixFor_Z_step;
};
*/
