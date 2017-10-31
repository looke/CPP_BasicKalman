/*
 * DynamicVector.h
 *
 *  Created on: 2017年4月22日
 *      Author: looke
 */

#ifndef VECTOR_DYNAMIC_DYNAMICVECTOR_H_
#define VECTOR_DYNAMIC_DYNAMICVECTOR_H_

#include "..\vector\basic\BasicVector.h"

class DynamicVector:public BasicVector
{
public:
	DynamicVector();
	DynamicVector(int input_dimension);

	//取向量的元素
	double getElement(int index);

	//设置向量的元素
	void setElement(int index, double value);

protected:
	//int vector_length;
	double* p_Vector;
	void init();

};



#endif /* VECTOR_DYNAMIC_DYNAMICVECTOR_H_ */
