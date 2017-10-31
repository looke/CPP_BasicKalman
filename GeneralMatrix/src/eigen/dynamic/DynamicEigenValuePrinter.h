/*
 * DynamicEigenValuePrinter.h
 *
 *  Created on: 2017Äê6ÔÂ3ÈÕ
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMICEIGENVALUEPRINTER_H_
#define EIGEN_DYNAMIC_DYNAMICEIGENVALUEPRINTER_H_

#include "..\eigen\dynamic\Dynamic2x2ComplexEigenValueCalculator.h"
#include "..\eigen\dynamic\DynamicGeneralizedEigenSolverForReal.h"
#include "..\eigen\dynamic\DynamicNormalEigenSolverForReal.h"
#include "..\eigen\util\ABInverseCalculator.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"

class DynamicEigenValuePrinter
{
public:
	DynamicEigenValuePrinter(BasicMatrix* p_input_OpMatrix);

	void printEigenValues(BasicMatrix* p_input_OpMatrix);
	void printEigenValues(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B);

protected:
	DynamicMatrix OpMatrix;

	DynamicMatrix OpMatrix_A;
	DynamicMatrix OpMatrix_B;

	DynamicGeneralizedEigenSolverForReal generalizedEigenCalc_nxn;

	DynamicNormalEigenSolverForReal normalEigenCalc_nxn;

	Dynamic2x2ComplexEigenValueCalculator EigenCalc_2x2;

	ABInverseCalculator ABInvCalc;

	DynamicMatrixMultiplier testMulti;
};



#endif /* EIGEN_DYNAMIC_DYNAMICEIGENVALUEPRINTER_H_ */
