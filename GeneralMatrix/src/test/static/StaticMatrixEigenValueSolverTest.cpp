/*
 * StaticMatrixEigenValueSolverTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ8ÈÕ
 *      Author: looke
 */

#include "test\static\StaticMatrixEigenValueSolverTest.h"
#include <iostream>
#include "basic\BasicMatrix.h"
#include "static\util\StaticMatrixMultiplier.h"
using namespace std;

StaticMatrixEigenValueSolverTest::StaticMatrixEigenValueSolverTest()
{
};

void StaticMatrixEigenValueSolverTest::test()
{
	StaticMatrix testMatrix33 = StaticMatrix(3,3);
	//testMatrix33.init(3,3);
	//BasicMatrix* p_testMatrix33 = testMatrix33.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix33 = &testMatrix33;

	p_testMatrix33->setMatrixElement(0,0,4);
	p_testMatrix33->setMatrixElement(0,1,2);
	p_testMatrix33->setMatrixElement(0,2,2);

	p_testMatrix33->setMatrixElement(1,0,2);
	p_testMatrix33->setMatrixElement(1,1,5);
	p_testMatrix33->setMatrixElement(1,2,1);

	p_testMatrix33->setMatrixElement(2,0,2);
	p_testMatrix33->setMatrixElement(2,1,1);
	p_testMatrix33->setMatrixElement(2,2,6);

	cout << "OP Matrix" << endl;
	p_testMatrix33->printMatrix();

	StaticMatrixEigenValueSolver eigenSolver = StaticMatrixEigenValueSolver(p_testMatrix33);
	eigenSolver.calcEigenValue(1);

};


