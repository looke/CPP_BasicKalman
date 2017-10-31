/*
 * DynamicGivensTransformationTester.cpp
 *
 *  Created on: 2017Äê4ÔÂ23ÈÕ
 *      Author: looke
 */

#include "DynamicGivensTransformationTester.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "iostream"
using namespace std;

DynamicGivensTransformationTester::DynamicGivensTransformationTester()
{};

void DynamicGivensTransformationTester::test()
{
	DynamicVector testVector = DynamicVector(3);
	testVector.setElement(0,1.0);
	testVector.setElement(1,2.0);
	testVector.setElement(2,3.0);

	BasicMatrix* p_GivensMatrix;

	DynamicGivensTransformation givens = DynamicGivensTransformation(&testVector);
	p_GivensMatrix = givens.getGivensMatrixPreMultiple(2);
	cout <<"Pre Multiple Given Matrix:" << endl;
	p_GivensMatrix->printMatrix();

	p_GivensMatrix = givens.getGivensMatrixAfterMultiple(2);
	cout <<"After Multiple Given Matrix:" << endl;
	p_GivensMatrix->printMatrix();
};
