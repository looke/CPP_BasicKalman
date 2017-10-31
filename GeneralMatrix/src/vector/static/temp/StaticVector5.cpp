/*
 * StaticVector5.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */


#include "StaticVector5.h"

StaticVector5::StaticVector5()
{
	this->dimension = 5;
	this->init();
};

void StaticVector5::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};


