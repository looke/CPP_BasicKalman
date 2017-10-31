/*
 * StaticVector11.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR11_H_
#define VECTOR_STATIC_STATICVECTOR11_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector11 : public BasicVector
{
public:
	StaticVector11();

protected:
	void init();
	double vector[11];
};

#endif /* VECTOR_STATIC_STATICVECTOR11_H_ */
