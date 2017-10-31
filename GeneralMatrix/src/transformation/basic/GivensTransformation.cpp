/*
 * GivensTransformation.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: looke
 */

#include "GivensTransformation.h"
#include "math.h"

GivensTransformation::GivensTransformation()
{
	//this->isUsingPreElement = true;
};

GivensTransformation::GivensTransformation(BasicVector* p_input_Vector)
{
	//this->isUsingPreElement = true;
	this->init(p_input_Vector);
};

/*
 * 根据输入向量，生成Givens矩阵，用于右乘该向量并消除指定位置的元素为0
 * 右乘Givens矩阵对应的向量为矩阵行向量
 */
BasicMatrix* GivensTransformation::getGivensMatrixAfterMultiple(int elementIndexToZero)
{
	//getGivensMatrixPreMultiple(elementIndexToZero);
	int i,j;

	//右乘Givens矩阵 使用后驱元素进行消元
	if(this->p_GivensVector->getDimension()-1 == elementIndexToZero)
	{
		j = elementIndexToZero;
		i = 0;
	}
	else if(this->p_GivensVector->getDimension()-1 != elementIndexToZero)
	{
		j = elementIndexToZero;
		i = j+1;
	}

	double i_Value = this->p_GivensVector->getElement(i);
	double j_Value = this->p_GivensVector->getElement(j);

	//生成Givens矩阵
	GenerateGivensMatrix(i, i_Value, j, j_Value);

	//将p_GivensMatrix进行转置
	double temp;
	for(int i=0; i<p_GivensMatrix->rowNum;i++)
	{
		for(int j=i+1; j<p_GivensMatrix->columnNum;j++)
		{
			temp = p_GivensMatrix->getMatrixElement(i,j);

			p_GivensMatrix->setMatrixElement(i,j,p_GivensMatrix->getMatrixElement(j,i));
			p_GivensMatrix->setMatrixElement(j,i,temp);
		}
	}

	return this->p_GivensMatrix;
};

/*
 * 根据输入向量，生成Givens矩阵，用于左乘该向量并消除指定位置的元素为0
 * 左乘Givens矩阵对应的向量为矩阵列向量
 */
BasicMatrix* GivensTransformation::getGivensMatrixPreMultiple(int elementIndexToZero)
{
	int i,j;
	//左乘Givens矩阵 使用前驱元素进行消元
	if(0 == elementIndexToZero)
	{
		j = 0;
		i = (this->p_GivensVector->getDimension())-1;
	}
	else if(0 != elementIndexToZero)
	{
		j = elementIndexToZero;
		i = j-1;
	}

	double i_Value = this->p_GivensVector->getElement(i);
	double j_Value = this->p_GivensVector->getElement(j);

	//生成Givens矩阵
	GenerateGivensMatrix(i, i_Value, j, j_Value);

	return this->p_GivensMatrix;
};

void GivensTransformation::GenerateGivensMatrix(int i, double i_Value, int j, double j_Value)
{
	double cosine,sine;
	double denominator = sqrt(i_Value*i_Value + j_Value*j_Value);

	if(0 != denominator)
	{
		cosine = i_Value / denominator;
		sine = j_Value / denominator;
	}
	else
	{
		cosine = 1;
		sine = 0;
	}

	p_GivensMatrix->resetMatrixToI();

	p_GivensMatrix->setMatrixElement(i,i,cosine);
	p_GivensMatrix->setMatrixElement(j,j,cosine);

	p_GivensMatrix->setMatrixElement(j,i,0-sine);
	p_GivensMatrix->setMatrixElement(i,j,sine);
};

/*
void GivensTransformation::setIsUsingPreElement(bool input)
{
	this->isUsingPreElement = input;
};
*/

void GivensTransformation::init(BasicVector* p_input_Vector)
{};

void GivensTransformation::reload(BasicVector* p_input_Vector)
{};
