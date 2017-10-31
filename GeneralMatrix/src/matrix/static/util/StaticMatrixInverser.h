/*
 * StaticMatrixInverser.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef STATICMATRIXINVERSER_H_
#define STATICMATRIXINVERSER_H_
#include <..\matrix\static\StaticMatrix.h>
#include "basic\util\MatrixInverser.h"

class StaticMatrixInverser:public MatrixInverser
{
public:
	//MatrixInverser();
	StaticMatrixInverser(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);
	void init(BasicMatrix* input_opMatrix);

private:
	StaticMatrix operateMatrix;
	StaticMatrix inverseMatrix;

};

#endif /* STATICMATRIXINVERSER_H_ */
