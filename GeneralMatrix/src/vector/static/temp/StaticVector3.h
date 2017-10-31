/*
 * StaticVector3.h
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR3_H_
#define VECTOR_STATIC_STATICVECTOR3_H_

#include "..\vector\basic\BasicVector.h"

class StaticVector3 : public BasicVector
{
public:
	StaticVector3();

protected:
	void init();
	double vector[3];
};

#endif /* VECTOR_STATIC_STATICVECTOR3_H_ */
