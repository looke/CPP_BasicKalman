/*
 * GivensTransformation.h
 *
 *  Created on: 2017年4月22日
 *      Author: looke
 */

#ifndef TRANSFORMATION_GIVENSTRANSFORMATION_H_
#define TRANSFORMATION_GIVENSTRANSFORMATION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\vector\basic\BasicVector.h"

class GivensTransformation
{
public:
	GivensTransformation();
	GivensTransformation(BasicVector* p_input_Vector);

	//生成Givens变换矩阵,根据输入向量,以及要消除的元素所引.生成矩阵在左乘向量后将指定元素消元为0
	//左乘Givens矩阵使用前驱元素
	BasicMatrix* getGivensMatrixPreMultiple(int elementIndexToZero);

	//生成Givens变换矩阵,根据输入向量,以及要消除的元素所引.生成矩阵在右乘向量后将指定元素消元为0
	//右乘Givens矩阵使用后驱元素
	BasicMatrix* getGivensMatrixAfterMultiple(int elementIndexToZero);

	virtual void init(BasicVector* p_input_Vector);
	virtual void reload(BasicVector* p_input_Vector);

	virtual ~GivensTransformation(){};

	//void setIsUsingPreElement(bool input);

private:


protected:
	//是否使用指定向量元素的前一个元素构造Givens矩阵,默认情况为True;
	//在进行Hessenberg-Tirangle格式化的过程中,对B矩阵的消元需要将此处设置为False;
	//bool isUsingPreElement;

	BasicMatrix* p_GivensMatrix;
	BasicVector* p_GivensVector;
	void GenerateGivensMatrix(int i, double i_Value, int j, double j_Value);
};



#endif /* TRANSFORMATION_GIVENSTRANSFORMATION_H_ */
