/*
 * StaticVector15.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
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
