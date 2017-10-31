/*
 * StaticVector10.cpp
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: looke
 */

#include "StaticVector10.h"

StaticVector10::StaticVector10()
{
	this->dimension = 10;
	this->init();
};

void StaticVector10::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};


