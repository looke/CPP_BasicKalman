/*
 * DynamicHouseholderTransformation.cpp
 *
 *  Created on: 2017Äê4ÔÂ24ÈÕ
 *      Author: looke
 */

#include "DynamicHouseholderTransformation.h"

DynamicHouseholderTransformation::DynamicHouseholderTransformation()
{
	int size = 0;

	this->householderVector = DynamicVector(size);
	this->householderMatrix = DynamicMatrix(size, size);

	this->p_HouseholderVector = &householderVector;
	this->p_HouseholderMatrix = &householderMatrix;
};

DynamicHouseholderTransformation::DynamicHouseholderTransformation(BasicVector* p_input_Vector)
{
	this->init(p_input_Vector);
};


void DynamicHouseholderTransformation::init(BasicVector* p_input_Vector)
{
	int size = p_input_Vector->getDimension();

	this->householderVector = DynamicVector(size);
	this->householderMatrix = DynamicMatrix(size, size);

	this->householderVector.copyVector(p_input_Vector);

	this->p_HouseholderVector = &householderVector;
	this->p_HouseholderMatrix = &householderMatrix;
};


void DynamicHouseholderTransformation::reload(BasicVector* p_input_Vector)
{
	if(this->p_HouseholderVector->getDimension() == p_input_Vector->getDimension())
	{
		this->p_HouseholderVector->copyVector(p_input_Vector);
		this->p_HouseholderMatrix->resetMatrixToI();
	}
	else
	{
		init(p_input_Vector);
	}
};
