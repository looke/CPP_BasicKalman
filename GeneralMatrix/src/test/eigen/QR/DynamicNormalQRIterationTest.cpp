/*
 * DynamicNormalQRIterationTest.cpp
 *
 *  Created on: 2017Äê5ÔÂ8ÈÕ
 *      Author: looke
 */

#include "DynamicNormalQRIterationTest.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "iostream"
using namespace std;

DynamicNormalQRIterationTest::DynamicNormalQRIterationTest()
{};

void DynamicNormalQRIterationTest::test()
{
	DynamicMatrix inputMatrix_B = DynamicMatrix(4,4);
	inputMatrix_B.setMatrixElement(0,0,0);
	inputMatrix_B.setMatrixElement(0,1,0);
	inputMatrix_B.setMatrixElement(0,2,2);
	inputMatrix_B.setMatrixElement(0,3,0);

	inputMatrix_B.setMatrixElement(1,0,0);
	inputMatrix_B.setMatrixElement(1,1,-1);
	inputMatrix_B.setMatrixElement(1,2,0);
	inputMatrix_B.setMatrixElement(1,3,0);

	inputMatrix_B.setMatrixElement(2,0,2);
	inputMatrix_B.setMatrixElement(2,1,0);
	inputMatrix_B.setMatrixElement(2,2,0);
	inputMatrix_B.setMatrixElement(2,3,0);

	inputMatrix_B.setMatrixElement(3,0,0);
	inputMatrix_B.setMatrixElement(3,1,0);
	inputMatrix_B.setMatrixElement(3,2,0);
	inputMatrix_B.setMatrixElement(3,3,0);

	DynamicMatrix inputMatrix_22 = DynamicMatrix(2,2);

	inputMatrix_22.setMatrixElement(0,0,0);
	inputMatrix_22.setMatrixElement(0,1,2);

	inputMatrix_22.setMatrixElement(1,0,2);
	inputMatrix_22.setMatrixElement(1,1,0);

	DynamicMatrix inputMatrix_33 = DynamicMatrix(3,3);

	inputMatrix_33.setMatrixElement(0,0,5);
	inputMatrix_33.setMatrixElement(0,1,-3);
	inputMatrix_33.setMatrixElement(0,2,2);

	inputMatrix_33.setMatrixElement(1,0,6);
	inputMatrix_33.setMatrixElement(1,1,-4);
	inputMatrix_33.setMatrixElement(1,2,4);

	inputMatrix_33.setMatrixElement(2,0,4);
	inputMatrix_33.setMatrixElement(2,1,-4);
	inputMatrix_33.setMatrixElement(2,2,5);

	DynamicMatrix inputMatrix_222 = DynamicMatrix(2,2);

	inputMatrix_222.setMatrixElement(0,0,8);
	inputMatrix_222.setMatrixElement(0,1,2);

	inputMatrix_222.setMatrixElement(1,0,2);
	inputMatrix_222.setMatrixElement(1,1,5);

	DynamicNormalQRIteration normQRit = DynamicNormalQRIteration(&inputMatrix_222);
	normQRit.QRIteration(10);

};


