/*
 * DynamicMatrixEquationSolver.h
 *
 *  Created on: 2017��2��19��
 *      Author: looke
 */

#ifndef DYNAMICMATRIXEQUATIONSOLVER_H_
#define DYNAMICMATRIXEQUATIONSOLVER_H_

#include "basic\util\MatrixEquationSolver.h"

class DynamicMatrixEquationSolver:public MatrixEquationSolver
{

public:
	DynamicMatrixEquationSolver(BasicMatrix* input_opMatrix);

	void init(BasicMatrix* input_opMatrix);
	void reload(BasicMatrix* input_opMatrix);

private:


};

#endif /* DYNAMICMATRIXEQUATIONSOLVER_H_ */
