/*
 * DynamicMatrixInverser.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef DYNAMICMATRIXINVERSER_H_
#define DYNAMICMATRIXINVERSER_H_
#include "basic\util\MatrixInverser.h"
#include "dynamic\DynamicMatrix.h"
class DynamicMatrixInverser:public MatrixInverser
{
public:
	//MatrixInverser();
	DynamicMatrixInverser(BasicMatrix* opMatrix);
	void reload(BasicMatrix* opMatrix);
	void init(BasicMatrix* opMatrix);

private:
	DynamicMatrix operateMatrix;
	DynamicMatrix inverseMatrix;
};

#endif /* DYNAMICMATRIXINVERSER_H_ */
