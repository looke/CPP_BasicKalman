/*
 * DynamicMatrixSquareRootSolver.h
 * Solve square roots based on Denman-Beavers Iteration.
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#ifndef DYNAMICMATRIXSQUAREROOTSOLVER_H_
#define DYNAMICMATRIXSQUAREROOTSOLVER_H_
#include "dynamic\DynamicMatrix.h"
#include "dynamic\util\DynamicMatrixInverser.h"
#include "basic\util\MatrixSquareRootSolver.h"

class DynamicMatrixSquareRootSolver:public MatrixSquareRootSolver
{
public:
	DynamicMatrixSquareRootSolver(BasicMatrix* input_opMatrix);

	void init(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);

protected:
	//逆矩阵求解
	DynamicMatrixInverser inverser;

	DynamicMatrix YMatrix;
	DynamicMatrix ZMatrix;

	//放置中间过程计算结果的矩阵
	DynamicMatrix tempYMatrix;
	DynamicMatrix tempZMatrix;

};

#endif /* DYNAMICMATRIXSQUAREROOTSOLVER_H_ */
