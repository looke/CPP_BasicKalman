/*
 * DynamicHouseholderTransformation.h
 *
 *  Created on: 2017Äê4ÔÂ24ÈÕ
 *      Author: looke
 */

#ifndef TRANSFORMATION_DYNAMIC_DYNAMICHOUSEHOLDERTRANSFORMATION_H_
#define TRANSFORMATION_DYNAMIC_DYNAMICHOUSEHOLDERTRANSFORMATION_H_



#include "..\transformation\basic\HouseholderTransformation.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"

class DynamicHouseholderTransformation:public HouseholderTransformation
{
public:
	DynamicHouseholderTransformation();
	DynamicHouseholderTransformation(BasicVector* p_input_Vector);

	void init(BasicVector* p_input_Vector);
	void reload(BasicVector* p_input_Vector);

private:
	DynamicVector householderVector;
	DynamicMatrix householderMatrix;

protected:
};

#endif /* TRANSFORMATION_DYNAMIC_DYNAMICHOUSEHOLDERTRANSFORMATION_H_ */
