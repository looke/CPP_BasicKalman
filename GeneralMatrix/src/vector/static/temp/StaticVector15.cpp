/*
 * StaticVector15.cpp
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#include "StaticVector15.h"

StaticVector15::StaticVector15()
{
	this->dimension = 15;
	this->init();
};

void StaticVector15::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};
