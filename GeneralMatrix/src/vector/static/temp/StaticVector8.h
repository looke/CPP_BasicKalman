/*
 * StaticVector8.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR8_H_
#define VECTOR_STATIC_STATICVECTOR8_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector8 : public BasicVector
{
public:
	StaticVector8();

protected:
	void init();
	double vector[8];
};


#endif /* VECTOR_STATIC_STATICVECTOR8_H_ */
