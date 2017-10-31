/*
 * StaticVector2.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR2_H_
#define VECTOR_STATIC_STATICVECTOR2_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector2 : public BasicVector
{
public:
	StaticVector2();

protected:
	void init();
	double vector[2];
};



#endif /* VECTOR_STATIC_STATICVECTOR2_H_ */
