/*
 * StaticMatrixSquareRootSolver.h
 * Solve square roots based on Denman-Beavers Iteration.
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#ifndef STATICMATRIXSQUAREROOTSOLVER_H_
#define STATICMATRIXSQUAREROOTSOLVER_H_
//#include "basic\BasicMatrix.h"
#include "basic\util\MatrixSquareRootSolver.h"
#include "static\util\StaticMatrixInverser.h"
#include "static\StaticMatrix.h"

class StaticMatrixSquareRootSolver:public MatrixSquareRootSolver
{
public:
	StaticMatrixSquareRootSolver(BasicMatrix* input_opMatrix);

	void init(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);

protected:
	//逆矩阵求解
	StaticMatrixInverser inverser;

	StaticMatrix YMatrix;
	StaticMatrix ZMatrix;

	//放置中间过程计算结果的矩阵
	StaticMatrix tempYMatrix;
	StaticMatrix tempZMatrix;
};

#endif /* STATICMATRIXSQUAREROOTSOLVER_H_ */
