/*
 * StaticVector6.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include "StaticVector6.h"

StaticVector6::StaticVector6()
{
	this->dimension = 6;
	this->init();
};

void StaticVector6::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};



