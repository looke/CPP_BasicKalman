/*
 * StaticVector11.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include "StaticVector11.h"

StaticVector11::StaticVector11()
{
	this->dimension = 11;
	this->init();
};

void StaticVector11::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};
