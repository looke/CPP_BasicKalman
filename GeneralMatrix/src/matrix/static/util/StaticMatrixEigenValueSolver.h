/*
 * StaticMatrixEigenValueSolver.h
 * 使用雅可比迭代法求解对称方阵的特征值和特征向量
 *
 *  Created on: 2017年2月26日
 *      Author: looke
 */

#ifndef STATICMATRIXEIGENVALUESOLVER_H_
#define STATICMATRIXEIGENVALUESOLVER_H_

#include "static\StaticMatrix.h"
#include "static\util\StaticMatrixTransposer.h"
#include "static\util\StaticMatrixMultiplier.h"
#include "basic\util\MatrixEigenValueSolver.h"

class StaticMatrixEigenValueSolver:public MatrixEigenValueSolver
{
public:
	StaticMatrixEigenValueSolver(BasicMatrix* input_opMatrix);
	virtual void init(BasicMatrix* input_opMatrix);
	virtual void reload(BasicMatrix* input_opMatrix);

protected:
	StaticMatrix operateMatrix;
	StaticMatrix Jn;
	StaticMatrix Jn_transopse;
	StaticMatrix An;
	StaticMatrix eigenVectorMatrix;

	StaticMatrixTransposer transposer;
	StaticMatrixMultiplier multiplier;
};


#endif /* STATICMATRIXEIGENVALUESOLVER_H_ */
