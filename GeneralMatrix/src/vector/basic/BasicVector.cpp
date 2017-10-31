/*
 * BasicVector.cpp
 *
 *  Created on: 2017年4月22日
 *      Author: looke
 */

#include "BasicVector.h"
#include "math.h"
#include "iostream"
using namespace std;

BasicVector::BasicVector()
{
	this->dimension = 0;
	this->init();
};

BasicVector::BasicVector(int input_dimension)
{
	if(input_dimension > 0)
	{
		this->dimension = input_dimension;
	}
	this->init();
};

//取向量的元素
double BasicVector::getElement(int index)
{};

//设置向量的元素
void BasicVector::setElement(int index, double value)
{};

//求向量的模
double BasicVector::getNormOfVector()
{
	double temp = 0.0;
	double result = 0.0;
	for(int i=0; i<this->dimension; i++)
	{
		temp = this->getElement(i);
		result += temp*temp;
	}

	return sqrt(result);
};

//求向量的模^2
double BasicVector::getNormPowerOfVector()
{
	double temp = 0.0;
	double result = 0.0;
	for(int i=0; i<this->dimension; i++)
	{
		temp = this->getElement(i);
		result += temp*temp;
	}

	return result;
};

//向量维度
int BasicVector::getDimension()
{
	return this->dimension;
};

void BasicVector::resetDimension(int input_newDimension)
{
	this->dimension = input_newDimension;
};

//拷贝向量的元素
void BasicVector::copyVector(BasicVector* input_Vector)
{
	if(this->dimension == input_Vector->getDimension())
	{
		for(int i=0; i<this->dimension; i++)
		{
			this->setElement(i,input_Vector->getElement(i));
		}
	}

};

//打印向量
void BasicVector::printVector()
{
	cout << "Vecotr: ";
	for(int i=0; i<this->dimension; i++)
	{
		cout << this->getElement(i) << "; ";
	}
	cout << endl;
};


void BasicVector::init()
{};
