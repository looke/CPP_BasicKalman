/*
 * StaticVector14.cpp
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#include "StaticVector14.h"

StaticVector14::StaticVector14()
{
	this->dimension = 14;
	this->init();
};

void StaticVector14::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};


