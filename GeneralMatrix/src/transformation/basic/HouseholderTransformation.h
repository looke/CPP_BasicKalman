/*
 * HouseholderTransformation.h
 *
 *  Created on: 2017��4��24��
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

	//����Householder�任����,����������,ת��Ϊ��һ��Ȼ������e1
	//isReverseElement:ָ���Ƿ��Ԫ�ط��Ž��з�ת�Ա㽵�;�����ʧ
	BasicMatrix* getHouseholderMatrixToE1(bool isReverseElement);

	//����Householder�任����,����������,ת��Ϊ��n��Ȼ������en
	//isReverseElement:ָ���Ƿ��Ԫ�ط��Ž��з�ת�Ա㽵�;�����ʧ
	BasicMatrix* getHouseholderMatrixToEn(bool isReverseElement);

	//����Householder Vector ��������Householder���� W = I-U*UT
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
