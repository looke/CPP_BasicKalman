/*
 * DynamicMatrixTransposer.h
 *
 *  Created on: 2017Äê2ÔÂ25ÈÕ
 *      Author: looke
 */

#ifndef DYNAMICMATRIXTRANSPOSER_H_
#define DYNAMICMATRIXTRANSPOSER_H_
#include "basic\util\MatrixTransposer.h"
#include "dynamic\DynamicMatrix.h"
class DynamicMatrixTransposer:public MatrixTransposer
{
public:
	DynamicMatrixTransposer(BasicMatrix* input_matrix);

	void init(BasicMatrix* input_matrix);
	void reload(BasicMatrix* input_matrix);


private:
	DynamicMatrix opMatrix;
	DynamicMatrix opMatrixTransposed;
};

#endif /* MATRIXTRANSPOSER_H_ */
