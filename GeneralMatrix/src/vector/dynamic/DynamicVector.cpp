/*
 * DynamicVector.cpp
 *
 *  Created on: 2017年4月22日
 *      Author: looke
 */

#include "DynamicVector.h"
#include <malloc.h>

DynamicVector::DynamicVector()
{

};

DynamicVector::DynamicVector(int input_dimension)
{
	this->space = 20;
	if(input_dimension > 0)
	{
		this->dimension = input_dimension;
		this->init();
	}
};

void DynamicVector::init()
{
	this->p_Vector = (double *) malloc(this->space*sizeof(double));
	for(int i=0; i<this->space; i++)
	{
		*(p_Vector+i)=1.0;
	}
};

//取向量的元素
double DynamicVector::getElement(int index)
{
	return *(p_Vector+index);
};

//设置向量的元素
void DynamicVector::setElement(int index, double value)
{
	*(p_Vector+index) = value;
};
