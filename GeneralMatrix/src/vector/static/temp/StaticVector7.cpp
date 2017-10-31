/*
 * StaticVector7.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include "StaticVector7.h"

StaticVector7::StaticVector7()
{
	this->dimension = 7;
	this->init();
};

void StaticVector7::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};


