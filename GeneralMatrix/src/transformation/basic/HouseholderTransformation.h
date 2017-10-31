/*
 * HouseholderTransformation.h
 *
 *  Created on: 2017年4月24日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_HOUSEHOLDERTRANSFORMATION_H_
#define TRANSFORMATION_BASIC_HOUSEHOLDERTRANSFORMATION_H_


#include "..\matrix\basic\BasicMatrix.h"
#include "..\vector\basic\BasicVector.h"

class HouseholderTransformation
{
public:
	HouseholderTransformation();
	HouseholderTransformation(BasicVector* p_input_Vector);

	//生成Householder变换矩阵,将输入向量,转换为第一自然基向量e1
	//isReverseElement:指定是否对元素符号进行反转以便降低精度损失
	BasicMatrix* getHouseholderMatrixToE1(bool isReverseElement);

	//生成Householder变换矩阵,将输入向量,转换为第n自然基向量en
	//isReverseElement:指定是否对元素符号进行反转以便降低精度损失
	BasicMatrix* getHouseholderMatrixToEn(bool isReverseElement);

	//根据Householder Vector 计算生成Householder矩阵 W = I-U*UT
	void generateHouseholderMatrixByVector();

	virtual void init(BasicVector* p_input_Vector);
	virtual void reload(BasicVector* p_input_Vector);

	virtual ~HouseholderTransformation(){};

private:


protected:
	BasicMatrix* p_HouseholderMatrix;
	BasicVector* p_HouseholderVector;
};


#endif /* TRANSFORMATION_BASIC_HOUSEHOLDERTRANSFORMATION_H_ */
