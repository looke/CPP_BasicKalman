/*
 * StaticVector12.cpp
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#include "StaticVector12.h"

StaticVector12::StaticVector12()
{
	this->dimension = 12;
	this->init();
};

void StaticVector12::init()
{
	//this->p_Vector = vector;
	for(int i=0; i<this->dimension; i++)
	{
		vector[i] = 1;
	}
};


