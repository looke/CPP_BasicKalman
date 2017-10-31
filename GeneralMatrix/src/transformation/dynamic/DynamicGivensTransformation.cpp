/*
 * DynamicGivensTransformation.cpp
 *
 *  Created on: 2017Äê4ÔÂ23ÈÕ
 *      Author: looke
 */
#include "DynamicGivensTransformation.h"

DynamicGivensTransformation::DynamicGivensTransformation()
{
	//this->isUsingPreElement = true;
};

DynamicGivensTransformation::DynamicGivensTransformation(BasicVector* p_input_Vector)
{
	this->init(p_input_Vector);
};

void DynamicGivensTransformation::init(BasicVector* p_input_Vector)
{
	int size = p_input_Vector->getDimension();

	this->givensVector = DynamicVector(size);
	this->givensMatrix = DynamicMatrix(size, size);

	this->givensVector.copyVector(p_input_Vector);

	this->p_GivensVector = &givensVector;
	this->p_GivensMatrix = &givensMatrix;

	//this->isUsingPreElement = true;
};

void DynamicGivensTransformation::reload(BasicVector* p_input_Vector)
{
	if(this->givensVector.getDimension() == p_input_Vector->getDimension())
	{
		this->p_GivensVector->copyVector(p_input_Vector);
		this->p_GivensMatrix->resetMatrixToI();
	}
	else
	{
		init(p_input_Vector);
	}

	//this->isUsingPreElement = true;
};
