/*
 * StaticVector15.h
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR15_H_
#define VECTOR_STATIC_STATICVECTOR15_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector15:public BasicVector
{
public:
	StaticVector15();

protected:
	void init();
	double vector[15];
};

#endif /* VECTOR_STATIC_STATICVECTOR15_H_ */
