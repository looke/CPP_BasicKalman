/*
 * StaticVector.cpp
 *
 *  Created on: 2017年4月25日
 *      Author: looke
 */

#include <vector/static/StaticVector.h>

StaticVector::StaticVector()
{
	this->space = 20;
};

StaticVector::StaticVector(int input_dimension)
{
	this->init(input_dimension);
};


void StaticVector::init(int input_dimension)
{
	this->space = 20;
	for(int i=0; i<space; i++)
	{
		vector_static[i] = 1;
	}

	this->dimension = input_dimension;
	//this->p_Vector = vector_static;
};

//取向量的元素
double StaticVector::getElement(int index)
{
	return this->vector_static[index];
};

//设置向量的元素
void StaticVector::setElement(int index, double value)
{
	this->vector_static[index] = value;
};
