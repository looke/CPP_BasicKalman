/*
 * StaticVector9.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */
#include "StaticVector9.h"

StaticVector9::StaticVector9()
{
	this->dimension = 9;
	this->init();
};

void StaticVector9::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};



