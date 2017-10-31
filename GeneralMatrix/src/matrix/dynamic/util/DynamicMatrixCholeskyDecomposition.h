/*
 * DynamicMatrixCholeskyDecomposition.h
 * Cholesky Decompostion
 *
 *  Created on: 2017Äê3ÔÂ16ÈÕ
 *      Author: looke
 */

#ifndef DYNAMICMATRIXCHOLESKYDECOMPOSITION_H_
#define DYNAMICMATRIXCHOLESKYDECOMPOSITION_H_

#include "basic\util\MatrixCholeskyDecomposition.h"
#include "dynamic\DynamicMatrix.h"
class DynamicMatrixCholeskyDecomposition:public MatrixCholeskyDecomposition
{
public:
	DynamicMatrixCholeskyDecomposition(BasicMatrix* input_opMatrix);

	void init(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);


protected:

	DynamicMatrix opMatrix;
	DynamicMatrix DecompositionMatrix;
};

#endif /* DYNAMICMATRIXCHOLESKYDECOMPOSITION_H_ */
