/*
 * StaticMatrixSquareRootSolver.h
 * Solve square roots based on Denman-Beavers Iteration.
 *
 *  Created on: 2017��2��25��
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
	//��������
	StaticMatrixInverser inverser;

	StaticMatrix YMatrix;
	StaticMatrix ZMatrix;

	//�����м���̼������ľ���
	StaticMatrix tempYMatrix;
	StaticMatrix tempZMatrix;
};

#endif /* STATICMATRIXSQUAREROOTSOLVER_H_ */
