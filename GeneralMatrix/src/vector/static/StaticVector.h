/*
 * StaticVector.h
 *
 *  Created on: 2017年4月25日
 *      Author: looke
 */

#ifndef VECTOR_STATIC_STATICVECTOR_H_
#define VECTOR_STATIC_STATICVECTOR_H_
#include "..\vector\basic\BasicVector.h"
/*
#include "..\vector\static\StaticVector2.h"
#include "..\vector\static\StaticVector3.h"
#include "..\vector\static\StaticVector4.h"
#include "..\vector\static\StaticVector5.h"
#include "..\vector\static\StaticVector6.h"
#include "..\vector\static\StaticVector7.h"
#include "..\vector\static\StaticVector8.h"
#include "..\vector\static\StaticVector9.h"
#include "..\vector\static\StaticVector10.h"
#include "..\vector\static\StaticVector11.h"
#include "..\vector\static\StaticVector12.h"
#include "..\vector\static\StaticVector13.h"
#include "..\vector\static\StaticVector14.h"
#include "..\vector\static\StaticVector15.h"
*/
class StaticVector : public BasicVector
{
public:
	StaticVector();
	StaticVector(int input_dimension);

	//取向量的元素
	double getElement(int index);

	//设置向量的元素
	void setElement(int index, double value);

protected:
	void init(int input_dimension);

	//int vector_length;
	double vector_static[20];

private:

	//void setVectorPointer(int input_dimension);
	//BasicVector* p_currentVector;

	/*
	StaticVector2 vector_2;
	StaticVector3 vector_3;
	StaticVector4 vector_4;
	StaticVector5 vector_5;
	StaticVector6 vector_6;
	StaticVector7 vector_7;
	StaticVector8 vector_8;
	StaticVector9 vector_9;
	StaticVector10 vector_10;
	StaticVector11 vector_11;
	StaticVector12 vector_12;
	StaticVector13 vector_13;
	StaticVector14 vector_14;
	StaticVector15 vector_15;
	*/

};


#endif /* VECTOR_STATIC_STATICVECTOR_H_ */
