/*
 * StaticVector9.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR9_H_
#define VECTOR_STATIC_STATICVECTOR9_H_
#include "..\vector\basic\BasicVector.h"

class StaticVector9 : public BasicVector
{
public:
	StaticVector9();

protected:
	void init();
	double vector[9];
};

#endif /* VECTOR_STATIC_STATICVECTOR9_H_ */
