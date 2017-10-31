/*
 * StaticVector10.h
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR10_H_
#define VECTOR_STATIC_STATICVECTOR10_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector10 : public BasicVector
{
public:
	StaticVector10();

protected:
	void init();
	double vector[10];
};

#endif /* VECTOR_STATIC_STATICVECTOR10_H_ */
