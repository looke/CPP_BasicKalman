/*
 * NormalEigenVectorSolverForReal.h
 *
 *  Created on: 2017Äê6ÔÂ6ÈÕ
 *      Author: looke
 */

#ifndef EIGEN_NORMALEIGENVECTORSOLVERFORREAL_H_
#define EIGEN_NORMALEIGENVECTORSOLVERFORREAL_H_

class NormalEigenVectorSolverForReal
{
public:
	NormalEigenVectorSolverForReal();
	NormalEigenVectorSolverForReal(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~NormalEigenVectorSolverForReal(){};

protected:
	BasicMatrix* p_OpMatrix;
};

#endif /* EIGEN_NORMALEIGENVECTORSOLVERFORREAL_H_ */
