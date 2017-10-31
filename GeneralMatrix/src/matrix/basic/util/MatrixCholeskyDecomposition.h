/*
 * MatrixCholeskyDecomposition.h
 * Cholesky Decompostion
 *
 *  Created on: 2017Äê3ÔÂ16ÈÕ
 *      Author: looke
 */

#ifndef MATRIXCHOLESKYDECOMPOSITION_H_
#define MATRIXCHOLESKYDECOMPOSITION_H_
#include "basic\BasicMatrix.h"

class MatrixCholeskyDecomposition
{
public:
	//MatrixCholeskyDecomposition();
	MatrixCholeskyDecomposition(BasicMatrix* input_opMatrix);

	virtual void init(BasicMatrix* input_opMatrix){};
	virtual void reload(BasicMatrix* input_opMatrix){};

	void generateDecompositionMatrix();

	BasicMatrix* getDecompositionMatrix();

	void printDecompositionMatrix();
	void printOpMatrix();

	virtual ~MatrixCholeskyDecomposition() {};
protected:
	int rowNumber;
	int columnNumber;

	BasicMatrix* p_opMatrix;

	BasicMatrix* p_DecompositionMatrix;

};

#endif /* MATRIXINVERSER_H_ */
