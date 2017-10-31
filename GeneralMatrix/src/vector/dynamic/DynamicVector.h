/*
 * DynamicVector.h
 *
 *  Created on: 2017��4��22��
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

	//ȡ������Ԫ��
	double getElement(int index);

	//����������Ԫ��
	void setElement(int index, double value);

protected:
	//int vector_length;
	double* p_Vector;
	void init();

};



#endif /* VECTOR_DYNAMIC_DYNAMICVECTOR_H_ */
