/*
 * StaticVector13.h
 *
 *  Created on: 2017��4��25��
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR13_H_
#define VECTOR_STATIC_STATICVECTOR13_H_


#include "..\vector\basic\BasicVector.h"

class StaticVector13 : public BasicVector
{
public:
	StaticVector13();

protected:
	void init();
	double vector[13];
};

#endif /* VECTOR_STATIC_STATICVECTOR13_H_ */
