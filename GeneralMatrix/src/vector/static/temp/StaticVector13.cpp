/*
 * StaticVector13.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include "StaticVector13.h"

StaticVector13::StaticVector13()
{
	this->dimension = 13;
	this->init();
};

void StaticVector13::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};



