/*
 * GivensTransformation.cpp
 *
 *  Created on: 2017��4��23��
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
 * ������������������Givens���������ҳ˸�����������ָ��λ�õ�Ԫ��Ϊ0
 * �ҳ�Givens�����Ӧ������Ϊ����������
 */
BasicMatrix* GivensTransformation::getGivensMatrixAfterMultiple(int elementIndexToZero)
{
	//getGivensMatrixPreMultiple(elementIndexToZero);
	int i,j;

	//�ҳ�Givens���� ʹ�ú���Ԫ�ؽ�����Ԫ
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

	//����Givens����
	GenerateGivensMatrix(i, i_Value, j, j_Value);

	//��p_GivensMatrix����ת��
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
 * ������������������Givens����������˸�����������ָ��λ�õ�Ԫ��Ϊ0
 * ���Givens�����Ӧ������Ϊ����������
 */
BasicMatrix* GivensTransformation::getGivensMatrixPreMultiple(int elementIndexToZero)
{
	int i,j;
	//���Givens���� ʹ��ǰ��Ԫ�ؽ�����Ԫ
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

	//����Givens����
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
