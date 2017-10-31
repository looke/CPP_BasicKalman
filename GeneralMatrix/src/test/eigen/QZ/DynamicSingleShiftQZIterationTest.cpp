/*
 * DynamicSingleShiftQZIterationTest.cpp
 *
 *  Created on: 2017Äê5ÔÂ29ÈÕ
 *      Author: looke
 */

#include "DynamicSingleShiftQZIterationTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "iostream"
using namespace std;

DynamicSingleShiftQZIterationTest::DynamicSingleShiftQZIterationTest()
{};

void DynamicSingleShiftQZIterationTest::test()
{
	cout << "DynamicSingleShiftQZIterationTest" << endl;

	DynamicMatrix test44_A = DynamicMatrix(4,4);

	test44_A.setMatrixElement(0,0,1);
	test44_A.setMatrixElement(0,1,2);
	test44_A.setMatrixElement(0,2,3);
	test44_A.setMatrixElement(0,3,4);

	test44_A.setMatrixElement(1,0,5);
	test44_A.setMatrixElement(1,1,6);
	test44_A.setMatrixElement(1,2,7);
	test44_A.setMatrixElement(1,3,8);

	test44_A.setMatrixElement(2,0,0);
	test44_A.setMatrixElement(2,1,9);
	test44_A.setMatrixElement(2,2,10);
	test44_A.setMatrixElement(2,3,11);

	test44_A.setMatrixElement(3,0,0);
	test44_A.setMatrixElement(3,1,0);
	test44_A.setMatrixElement(3,2,12);
	test44_A.setMatrixElement(3,3,13);


	DynamicMatrix test44_B = DynamicMatrix(4,4);

	test44_B.setMatrixElement(0,0,1);
	test44_B.setMatrixElement(0,1,2);
	test44_B.setMatrixElement(0,2,3);
	test44_B.setMatrixElement(0,3,4);

	test44_B.setMatrixElement(1,0,0);
	test44_B.setMatrixElement(1,1,5);
	test44_B.setMatrixElement(1,2,6);
	test44_B.setMatrixElement(1,3,7);

	test44_B.setMatrixElement(2,0,0);
	test44_B.setMatrixElement(2,1,0);
	test44_B.setMatrixElement(2,2,8);
	test44_B.setMatrixElement(2,3,9);

	test44_B.setMatrixElement(3,0,0);
	test44_B.setMatrixElement(3,1,0);
	test44_B.setMatrixElement(3,2,0);
	test44_B.setMatrixElement(3,3,10);

	DynamicSingleShiftQZIteration qzIteration = DynamicSingleShiftQZIteration(&test44_A, &test44_B);

	qzIteration.rayleigh_Quotient_IM_QZIteration(150);
};


