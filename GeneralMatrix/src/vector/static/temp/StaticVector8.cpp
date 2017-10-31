/*
 * StaticVector8.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include "StaticVector8.h"

StaticVector8::StaticVector8()
{
	this->dimension = 8;
	this->init();
};

void StaticVector8::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};
