/*
 * StaticVector14.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR14_H_
#define VECTOR_STATIC_STATICVECTOR14_H_


#include "..\vector\basic\BasicVector.h"

class StaticVector14 : public BasicVector
{
public:
	StaticVector14();

protected:
	void init();
	double vector[14];
};




#endif /* VECTOR_STATIC_STATICVECTOR14_H_ */
