/*
 * DynamicMatrixEigenValueSolver.h
 * ʹ���ſɱȵ��������ԳƷ��������ֵ����������
 *
 *  Created on: 2017��2��26��
 *      Author: looke
 */

#ifndef DYNAMICMATRIXEIGENVALUESOLVER_H_
#define DYNAMICMATRIXEIGENVALUESOLVER_H_

#include "dynamic\DynamicMatrix.h"
#include "dynamic\util\DynamicMatrixTransposer.h"
#include "dynamic\util\DynamicMatrixMultiplier.h"
#include "basic\util\MatrixEigenValueSolver.h"

class DynamicMatrixEigenValueSolver:public MatrixEigenValueSolver
{
public:
	DynamicMatrixEigenValueSolver(BasicMatrix* input_opMatrix);
	void init(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);
protected:
	DynamicMatrix operateMatrix;
	DynamicMatrix Jn;
	DynamicMatrix Jn_transopse;
	DynamicMatrix An;
	DynamicMatrix eigenVectorMatrix;

	DynamicMatrixTransposer transposer;
	DynamicMatrixMultiplier multiplier;
};


#endif /* DYNAMICMATRIXEIGENVALUESOLVER_H_ */
