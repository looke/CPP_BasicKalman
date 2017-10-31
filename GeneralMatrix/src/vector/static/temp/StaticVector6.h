/*
 * StaticVector6.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR6_H_
#define VECTOR_STATIC_STATICVECTOR6_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector6 : public BasicVector
{
public:
	StaticVector6();

protected:
	void init();
	double vector[6];
};



#endif /* VECTOR_STATIC_STATICVECTOR6_H_ */
