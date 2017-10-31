/*
 * MatrixInverser.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef MATRIXINVERSER_H_
#define MATRIXINVERSER_H_
#include "basic\BasicMatrix.h"

class MatrixInverser
{
public:

	MatrixInverser(BasicMatrix* input_opMatrix);
	virtual void reload(BasicMatrix* input_opMatrix);
	virtual void init(BasicMatrix* input_opMatrix);

	void unZeroPivotRow(int pivotRow);
	void normalizePivotRow(int pivotRow);
	void eliminateSubMatrix(int pivotRow);
	void eliminateUpperMatrix(int startRow);
	void generateInverseMatrix();


	bool isOpMatrixFullRank();
	BasicMatrix* getInverseMatrix();


	void printOpMatrix();
	void printInverseMatrix();
	virtual ~MatrixInverser() {};
protected:

	BasicMatrix* p_operateMatrix;
	BasicMatrix* p_inverseMatrix;


	bool isSquareMatrix;
	int rowNumber;
	int columnNumber;
	bool isFullRank;
};

#endif /* MATRIXINVERSER_H_ */
