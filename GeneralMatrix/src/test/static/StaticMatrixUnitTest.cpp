/*
 * DynamicMatrixTest.cpp
 *
 *  Created on: 2017Äê3ÔÂ25ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "StaticMatrixUnitTest.h"
#include "basic\BasicMatrix.h"
#include "..\vector\basic\BasicVector.h"
using namespace std;


StaticMatrixUnitTest::StaticMatrixUnitTest()
{
};

void StaticMatrixUnitTest::test()
{
	//3*3
	StaticMatrixUnit test33 = StaticMatrixUnit();
	test33.init(3,3);
	BasicMatrix* p_test33 = test33.getCurrentMatrixPointer();
	//test.resetMatrixToI();
	p_test33->printMatrix();

	cout << "test swap row 0 to 2" << endl;
	p_test33->swapRow(0,2);
	p_test33->printMatrix();

	cout << "test swap column 0 to 2" << endl;
	p_test33->swapColumn(0,2);
	p_test33->printMatrix();

	cout << "test swap diag element 0 to 2" << endl;
	p_test33->swapDiagElement(0,2);
	p_test33->printMatrix();

	//3*2
	StaticMatrixUnit test32 = StaticMatrixUnit();
	test32.init(3,2);
	BasicMatrix* p_test32 = test32.getCurrentMatrixPointer();
	cout << "test32" << endl;
	p_test32->printMatrix();

	//2*3
	StaticMatrixUnit test23 = StaticMatrixUnit();
	test23.init(2,3);
	BasicMatrix* p_test23 = test23.getCurrentMatrixPointer();
	cout << "test23" << endl;
	p_test23->printMatrix();

	//2*2
	StaticMatrixUnit test22 = StaticMatrixUnit();
	test22.init(2,2);
	BasicMatrix* p_test22 = test22.getCurrentMatrixPointer();
	cout << "test22" << endl;
	p_test22->printMatrix();

	//15*15
	StaticMatrixUnit test1515 = StaticMatrixUnit();
	test1515.init(15,15);
	BasicMatrix* p_test1515 = test1515.getCurrentMatrixPointer();
	cout << "test1515" << endl;
	p_test1515->printMatrix();

	//15*10
	StaticMatrixUnit test1510 = StaticMatrixUnit();
	test1510.init(15,10);
	BasicMatrix* p_test1510 = test1510.getCurrentMatrixPointer();
	cout << "test1510" << endl;
	p_test1510->printMatrix();

	//15*11
	StaticMatrixUnit test1511 = StaticMatrixUnit();
	test1511.init(15,11);
	BasicMatrix* p_test1511 = test1511.getCurrentMatrixPointer();
	cout << "test1511" << endl;
	p_test1511->printMatrix();

	BasicVector* p_VectorOfTest1511 = p_test1511->getColumnVector(2);
	cout << "Column Vector 2 of test1511:" << endl;
	p_VectorOfTest1511->printVector();

	p_VectorOfTest1511 = p_test1511->getRowVector(2);
	cout << "Row Vector 2 of test1511:" << endl;
	p_VectorOfTest1511->printVector();

	//10*10
	StaticMatrixUnit test1111 = StaticMatrixUnit();
	test1111.init(11,11);
	BasicMatrix* p_test1111 = test1111.getCurrentMatrixPointer();
	cout << "test1111" << endl;
	p_test1111->printMatrix();



	//10*10
	StaticMatrixUnit test1010 = StaticMatrixUnit();
	test1010.init(10,10);
	BasicMatrix* p_test1010 = test1010.getCurrentMatrixPointer();
	cout << "test1010" << endl;
	p_test1010->printMatrix();

	cout << "test1010 swap diag element 0 to 2" << endl;
	p_test1010->swapDiagElement(0,2);
	p_test1010->printMatrix();

	BasicVector* p_VectorOfTest1010 = p_test1010->getColumnVector(2);
	cout << "Column Vector 2 of test1010:" << endl;
	p_VectorOfTest1010->printVector();

	p_VectorOfTest1010 = p_test1010->getRowVector(2);
	cout << "Row Vector 2 of test1010:" << endl;
	p_VectorOfTest1010->printVector();
};

