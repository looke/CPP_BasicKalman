/*
 * MatrixTransposer.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef MATRIXTRANSPOSER_H_
#define MATRIXTRANSPOSER_H_
#include "basic\BasicMatrix.h"

class MatrixTransposer
{
public:
	MatrixTransposer(BasicMatrix* input_matrix);

	virtual void init(BasicMatrix* input_matrix);
	virtual void reload(BasicMatrix* input_matrix);

	void transposeMatrix();

	BasicMatrix* getTransposeMatrix();
	void printMatrixTranspose();

	virtual ~MatrixTransposer() {};
protected:
	BasicMatrix* p_opMatrix;
	BasicMatrix* p_opMatrixTransposed;
};

#endif /* MATRIXTRANSPOSER_H_ */
