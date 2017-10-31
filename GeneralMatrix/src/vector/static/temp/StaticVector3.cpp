/*
 * StaticVector3.cpp
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: looke
 */

#include "StaticVector3.h"

StaticVector3::StaticVector3()
{
	this->dimension = 3;
	this->init();
};

void StaticVector3::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};


