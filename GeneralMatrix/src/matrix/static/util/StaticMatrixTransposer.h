/*
 * StaticMatrixTransposer.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef StaticMatrixTransposer_H_
#define StaticMatrixTransposer_H_
#include <..\matrix\static\StaticMatrix.h>
#include "basic\util\MatrixTransposer.h"

class StaticMatrixTransposer:public MatrixTransposer
{
public:
	StaticMatrixTransposer(BasicMatrix* input_matrix);

	void init(BasicMatrix* input_matrix);
	void reload(BasicMatrix* input_matrix);
	//void transposeMatrix();

	//BasicMatrix* getTransposeMatrix();
	//void printMatrixTranspose();

private:
	int rowNumber;
	int columnNumber;
	StaticMatrix opMatrix;
	StaticMatrix opMatrixTransposed;
};

#endif /* StaticMatrixTransposer_H_ */
