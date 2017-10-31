/*
 * StaticVector4.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR4_H_
#define VECTOR_STATIC_STATICVECTOR4_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector4 : public BasicVector
{
public:
	StaticVector4();

protected:
	void init();
	double vector[4];
};



#endif /* VECTOR_STATIC_STATICVECTOR4_H_ */
