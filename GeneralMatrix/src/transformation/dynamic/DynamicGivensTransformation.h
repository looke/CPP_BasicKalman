/*
 * DynamicGivensTransformation.h
 *
 *  Created on: 2017Äê4ÔÂ23ÈÕ
 *      Author: looke
 */

#ifndef TRANSFORMATION_DYNAMIC_DYNAMICGIVENSTRANSFORMATION_H_
#define TRANSFORMATION_DYNAMIC_DYNAMICGIVENSTRANSFORMATION_H_

#include "..\transformation\basic\GivensTransformation.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"

class DynamicGivensTransformation:public GivensTransformation
{
public:
	DynamicGivensTransformation();
	DynamicGivensTransformation(BasicVector* p_input_Vector);

	void init(BasicVector* p_input_Vector);
	void reload(BasicVector* p_input_Vector);

private:
	DynamicVector givensVector;
	DynamicMatrix givensMatrix;

protected:
};


#endif /* TRANSFORMATION_DYNAMIC_DYNAMICGIVENSTRANSFORMATION_H_ */
