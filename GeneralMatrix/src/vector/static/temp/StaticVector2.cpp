/*
 * StaticVector2.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include "StaticVector2.h"

StaticVector2::StaticVector2()
{
	this->dimension = 2;
	this->init();
};

void StaticVector2::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};
