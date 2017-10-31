/*
 * StaticVector5.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR5_H_
#define VECTOR_STATIC_STATICVECTOR5_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector5 : public BasicVector
{
public:
	StaticVector5();

protected:
	void init();
	double vector[5];
};

#endif /* VECTOR_STATIC_STATICVECTOR5_H_ */
