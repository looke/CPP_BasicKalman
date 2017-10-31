/*
 * DynamicMatrixEigenValueSolverTester.cpp
 *
 *  Created on: 2017Äê3ÔÂ24ÈÕ
 *      Author: looke
 */

#include <test\dynamic\DynamicMatrixEigenValueSolverTester.h>
#include <iostream>

//#include "basic\util\MatrixMultiplier.h"
//#include "basic\util\MatrixTransposer.h"

using namespace std;

DynamicMatrixEigenValueSolverTester::DynamicMatrixEigenValueSolverTester()
{
};


void DynamicMatrixEigenValueSolverTester::test()
{
/*
	DynamicMatrix eigenMatrix(4,4);

	eigenMatrix.setMatrixElement(0,0,0);
	eigenMatrix.setMatrixElement(0,1,1);
	eigenMatrix.setMatrixElement(0,2,0);
	eigenMatrix.setMatrixElement(0,3,0);

	eigenMatrix.setMatrixElement(1,0,1);
	eigenMatrix.setMatrixElement(1,1,0);
	eigenMatrix.setMatrixElement(1,2,0);
	eigenMatrix.setMatrixElement(1,3,0);

	eigenMatrix.setMatrixElement(2,0,0);
	eigenMatrix.setMatrixElement(2,1,0);
	eigenMatrix.setMatrixElement(2,2,2);
	eigenMatrix.setMatrixElement(2,3,1);

	eigenMatrix.setMatrixElement(3,0,0);
	eigenMatrix.setMatrixElement(3,1,0);
	eigenMatrix.setMatrixElement(3,2,1);
	eigenMatrix.setMatrixElement(3,3,2);
*/
	DynamicMatrix eigenMatrix(4,4);
	eigenMatrix.setMatrixElement(0,0,0);
	eigenMatrix.setMatrixElement(0,1,0);
	eigenMatrix.setMatrixElement(0,2,2);
	eigenMatrix.setMatrixElement(0,3,0);

	eigenMatrix.setMatrixElement(1,0,0);
	eigenMatrix.setMatrixElement(1,1,-1);
	eigenMatrix.setMatrixElement(1,2,0);
	eigenMatrix.setMatrixElement(1,3,0);

	eigenMatrix.setMatrixElement(2,0,2);
	eigenMatrix.setMatrixElement(2,1,0);
	eigenMatrix.setMatrixElement(2,2,0);
	eigenMatrix.setMatrixElement(2,3,0);

	eigenMatrix.setMatrixElement(3,0,0);
	eigenMatrix.setMatrixElement(3,1,0);
	eigenMatrix.setMatrixElement(3,2,0);
	eigenMatrix.setMatrixElement(3,3,0);
	DynamicMatrixEigenValueSolver eigenValue = DynamicMatrixEigenValueSolver(&eigenMatrix);
	eigenValue.calcEigenValue(1);

	cout << "Final Eigen Value" << endl;
	eigenValue.printEigenValueMatrix();
	cout << "Final Eigen Vector" << endl;
	eigenValue.printEigenVectorMatrix();
};
