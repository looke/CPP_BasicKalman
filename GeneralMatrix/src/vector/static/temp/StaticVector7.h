/*
 * StaticVector7.h
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR7_H_
#define VECTOR_STATIC_STATICVECTOR7_H_


#include "..\vector\basic\BasicVector.h"

class StaticVector7 : public BasicVector
{
public:
	StaticVector7();

protected:
	void init();
	double vector[7];
};



#endif /* VECTOR_STATIC_STATICVECTOR7_H_ */
