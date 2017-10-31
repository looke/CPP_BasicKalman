/*
 * StaticVector12.h
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR12_H_
#define VECTOR_STATIC_STATICVECTOR12_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector12 : public BasicVector
{
public:
	StaticVector12();

protected:
	void init();
	double vector[12];
};

#endif /* VECTOR_STATIC_STATICVECTOR12_H_ */
