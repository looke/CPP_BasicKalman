/*
 * BasicVector.h
 *
 *  Created on: 2017年4月22日
 *      Author: looke
 */

#ifndef VECTOR_BASIC_BASICVECTOR_H_
#define VECTOR_BASIC_BASICVECTOR_H_

class BasicVector
{

public:
	BasicVector();
	BasicVector(int input_dimension);

	//求向量的模
	double getNormOfVector();
	//求向量的模^2
	double getNormPowerOfVector();

	//向量维度
	int getDimension();

	void resetDimension(int input_newDimension);

	//取向量的元素
	virtual double getElement(int index);

	//设置向量的元素
	virtual void setElement(int index, double value);

	//拷贝向量的元素
	void copyVector(BasicVector* input_Vector);

	void printVector();

	virtual ~BasicVector(){};

private:



protected:
	int dimension;
	int space;
	//double* p_Vector;
	virtual void init();

};



#endif /* VECTOR_BASIC_BASICVECTOR_H_ */
