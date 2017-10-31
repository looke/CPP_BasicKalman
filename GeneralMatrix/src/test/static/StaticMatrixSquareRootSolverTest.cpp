/*
 * StaticMatrixSquareRootSolverTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ8ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "basic\BasicMatrix.h"
#include "test\static\StaticMatrixSquareRootSolverTest.h"
#include "static\util\StaticMatrixMultiplier.h"
#include "..\matrix\static\StaticMatrix.h"
using namespace std;


StaticMatrixSquareRootSolverTest::StaticMatrixSquareRootSolverTest()
{
};

void StaticMatrixSquareRootSolverTest::test()
{
	StaticMatrix testMatrix33 = StaticMatrix(3,3);
	//testMatrix33.init(3,3);
	//BasicMatrix* p_testMatrix33 = testMatrix33.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix33 = &testMatrix33;

	p_testMatrix33->setMatrixElement(0,0,4);
	p_testMatrix33->setMatrixElement(0,1,4);
	p_testMatrix33->setMatrixElement(0,2,4);

	p_testMatrix33->setMatrixElement(1,0,0);
	p_testMatrix33->setMatrixElement(1,1,4);
	p_testMatrix33->setMatrixElement(1,2,0);

	p_testMatrix33->setMatrixElement(2,0,0);
	p_testMatrix33->setMatrixElement(2,1,0);
	p_testMatrix33->setMatrixElement(2,2,4);

	cout << "OP Matrix" << endl;
	p_testMatrix33->printMatrix();


	StaticMatrixSquareRootSolver sqrt = StaticMatrixSquareRootSolver(p_testMatrix33);
	bool hasSqrt = sqrt.generateSquareRootMatrix();

	cout << "Has Sqrt:" << hasSqrt << endl;

	if(hasSqrt)
	{
		BasicMatrix* p_sqrtMatrix = sqrt.getSquareRootMatrix();
		cout << "Sqrt Matrix" << endl;
		p_sqrtMatrix->printMatrix();
		StaticMatrixMultiplier multi = StaticMatrixMultiplier(p_sqrtMatrix,p_sqrtMatrix);
		multi.multiplyCalc();
		BasicMatrix* p_mutiResult = multi.getMultiplyResult();

		cout << "Sqrt Matrix ^ 2" << endl;
		p_mutiResult->printMatrix();
	}



};
