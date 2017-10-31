/*
 * StaticMatrixCholeskyDecomposition.h
 * Cholesky Decompostion
 *
 *  Created on: 2017��3��16��
 *      Author: looke
 */

#ifndef STATICMATRIXCHOLESKYDECOMPOSITION_H_
#define STATICMATRIXCHOLESKYDECOMPOSITION_H_
#include "basic\util\MatrixCholeskyDecomposition.h"
#include "static\StaticMatrix.h"
class StaticMatrixCholeskyDecomposition:public MatrixCholeskyDecomposition
{
public:
	StaticMatrixCholeskyDecomposition(BasicMatrix* input_opMatrix);

	void init(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);


private:

	StaticMatrix opMatrix;
	StaticMatrix DecompositionMatrix;
};

#endif /* STATIC33MATRIXCHOLESKYDECOMPOSITION_H_ */
