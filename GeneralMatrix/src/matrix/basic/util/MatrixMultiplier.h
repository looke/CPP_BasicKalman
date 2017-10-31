/*
 * MatrixMultiplier.h
 *
 *  Created on: 2017��2��25��
 *      Author: looke
 */

#ifndef MATRIXMULTIPLIER_H_
#define MATRIXMULTIPLIER_H_
#include "basic\BasicMatrix.h"

class MatrixMultiplier
{
public:

	MatrixMultiplier(BasicMatrix* leftOp, BasicMatrix* rightOp);

	virtual void reload(BasicMatrix* leftOp, BasicMatrix* rightOp);
	virtual void init(BasicMatrix* leftOp, BasicMatrix* rightOp);

	void multiplyCalc();

	void printMultiplyResult();

	BasicMatrix* getMultiplyResult();
	virtual ~MatrixMultiplier() {};
protected:

	BasicMatrix* p_leftOpMatrix;	//�����������
	BasicMatrix* p_rightOpMatrix;//�Ҳ���������

	BasicMatrix* p_MultiResult;

	bool isLegalMultiply;

	int leftRow;
	int leftColumn;

	int rightRow;
	int rightColumn;
};

#endif /* MATRIXMULTIPLIER_H_ */
