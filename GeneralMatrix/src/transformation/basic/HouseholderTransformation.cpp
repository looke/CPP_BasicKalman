/*
 * HouseholderTransformation.cpp
 *
 *  Created on: 2017年4月24日
 *      Author: looke
 */

#include "HouseholderTransformation.h"
#include <iostream>
using namespace std;
HouseholderTransformation::HouseholderTransformation()
{};

HouseholderTransformation::HouseholderTransformation(BasicVector* p_input_Vector)
{
	this->init(p_input_Vector);
};


void HouseholderTransformation::init(BasicVector* p_input_Vector)
{

};

void HouseholderTransformation::reload(BasicVector* p_input_Vector)
{

};


/*
 * 根据输入向量，生成Householder矩阵，转换为第一自然基向量e1
 * 左乘Householder矩阵对应的向量为矩阵列向量
 * 右乘Householder矩阵对应的向量为矩阵行向量
 */
BasicMatrix* HouseholderTransformation::getHouseholderMatrixToE1(bool isReverseElement)
{
	cout << "Input Vector for Calc Householder matrix---HouseholderMatrixToE1" << endl;
	this->p_HouseholderVector->printVector();

	//int size = this->p_HouseholderVector->getDimension();
	double norm_X = this->p_HouseholderVector->getNormOfVector();
	double X_0 = this->p_HouseholderVector->getElement(0);

	//防止元素符号相同产生对消
	if(X_0 > 0 && isReverseElement)
	{
		norm_X = 0 - norm_X;
	}
	//计算X-aE1 (a为norm_X)
	this->p_HouseholderVector->setElement(0, X_0-norm_X);
	//测试打印
	cout << "Vector U for Calc Householder matrix" << endl;
	this->p_HouseholderVector->printVector();

	generateHouseholderMatrixByVector();
	/*
	double normPower_U = this->p_HouseholderVector->getNormPowerOfVector();
	double temp;
	for(int i=0; i<size; i++)
	{
		for(int j=i; j<size; j++)
		{
			temp = 2*this->p_HouseholderVector->getElement(i) * this->p_HouseholderVector->getElement(j);

			if(0 == normPower_U)
			{
				temp = 0;
			}
			else
			{
				temp = temp/normPower_U;
			}


			if(j == i)
			{
				//对角线元素
				temp = 1 - temp;
			}
			else
			{
				temp = 0 - temp;
			}
			this->p_HouseholderMatrix->setMatrixElement(i,j,temp);
			this->p_HouseholderMatrix->setMatrixElement(j,i,temp);
		}
	}
	*/
	return this->p_HouseholderMatrix;
};

/*
 * 根据Householder Vector 计算生成Householder矩阵 W = I-U*UT
 */
void HouseholderTransformation::generateHouseholderMatrixByVector()
{
	int size = this->p_HouseholderVector->getDimension();
	double normPower_U = this->p_HouseholderVector->getNormPowerOfVector();

	double temp;
	for(int i=0; i<size; i++)
	{
		for(int j=i; j<size; j++)
		{
			temp = 2*this->p_HouseholderVector->getElement(i) * this->p_HouseholderVector->getElement(j);

			if(0 == normPower_U)
			{
				temp = 0;
			}
			else
			{
				temp = temp/normPower_U;
			}


			if(j == i)
			{
				//对角线元素
				temp = 1 - temp;
			}
			else
			{
				temp = 0 - temp;
			}
			this->p_HouseholderMatrix->setMatrixElement(i,j,temp);
			this->p_HouseholderMatrix->setMatrixElement(j,i,temp);
		}
	}
};


/*
 * 根据输入向量，生成Householder矩阵，转换为第n自然基向量en
 * 左乘Householder矩阵对应的向量为矩阵列向量
 * 右乘Householder矩阵对应的向量为矩阵行向量
 */
BasicMatrix* HouseholderTransformation::getHouseholderMatrixToEn(bool isReverseElement)
{
	cout << "Input Vector for Calc Householder matrix---HouseholderMatrixToEn" << endl;
	this->p_HouseholderVector->printVector();

	int size = this->p_HouseholderVector->getDimension();
	double norm_X = this->p_HouseholderVector->getNormOfVector();
	double X_n = this->p_HouseholderVector->getElement(size-1);

	//防止元素符号相同产生对消
	if(X_n > 0 && isReverseElement)
	{
		norm_X = 0 - norm_X;
	}
	//计算X-aEn (a为norm_X)
	this->p_HouseholderVector->setElement(size-1, X_n-norm_X);
	//测试打印
	cout << "Vector U for Calc Householder matrix" << endl;
	this->p_HouseholderVector->printVector();

	generateHouseholderMatrixByVector();
	return this->p_HouseholderMatrix;
};
