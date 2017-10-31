/*
 * StaticVector4.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */


#include "StaticVector4.h"

StaticVector4::StaticVector4()
{
	this->dimension = 4;
	this->init();
};

void StaticVector4::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};
