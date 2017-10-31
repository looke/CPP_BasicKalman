/*
 * Dynamic2x2ComplexEigenValueCalculator.h
 *
 *  Created on: 2017Äê6ÔÂ3ÈÕ
 *      Author: looke
 */

#ifndef EIGEN_DYNAMIC_DYNAMIC2X2COMPLEXEIGENVALUECALCULATOR_H_
#define EIGEN_DYNAMIC_DYNAMIC2X2COMPLEXEIGENVALUECALCULATOR_H_

#include "..\matrix\dynamic\DynamicMatrix.h"

class Dynamic2x2ComplexEigenValueCalculator
{
public:
	Dynamic2x2ComplexEigenValueCalculator();
	//Dynamic2x2ComplexEigenValueCalculator(BasicMatrix* input_OpMatrix_2x2);

	void printEigenValue(BasicMatrix* input_OpMatrix_2x2);

protected:
	DynamicMatrix opMatrix_2x2;

};


#endif /* EIGEN_DYNAMIC_DYNAMIC2X2COMPLEXEIGENVALUECALCULATOR_H_ */
