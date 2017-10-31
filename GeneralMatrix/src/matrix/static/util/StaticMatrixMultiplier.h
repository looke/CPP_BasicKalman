/*
 * StaticMatrixMultiplier.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef STATICMATRIXMULTIPLIER_H_
#define STATICMATRIXMULTIPLIER_H_

#include <static\StaticMatrix.h>

#include "basic\util\MatrixMultiplier.h"

class StaticMatrixMultiplier:public MatrixMultiplier
{
public:
	StaticMatrixMultiplier(BasicMatrix* leftOp, BasicMatrix* rightOp);

	void reload(BasicMatrix* leftOp, BasicMatrix* rightOp);
	void init(BasicMatrix* leftOp, BasicMatrix* rightOp);

private:
	//Static1515Matrix MultiResult1515;
	//Static1010Matrix MultiResult1010;
	StaticMatrix MultiResult;
};

#endif /* STATICMATRIXMULTIPLIER_H_ */
