/*
 * StaticMatrixTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ25ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "StaticMatrixTest.h"
#include "basic\BasicMatrix.h"
#include "..\vector\basic\BasicVector.h"
using namespace std;


StaticMatrixTest::StaticMatrixTest()
{
};

void StaticMatrixTest::test()
{
	//3*3
	StaticMatrix test33 = StaticMatrix(3,3);
	BasicMatrix* p_test33 = &test33;
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

	cout << "Column Vector 1 of Matrix" << endl;
	BasicVector* p_testVector = p_test33->getColumnVector(1);
	p_testVector->printVector();

	cout << "Column Vector 0 of Sub Matrix 1" << endl;
	BasicVector* p_testSubVector = p_test33->getSubMatrixColumnVector(1,0);
	p_testSubVector->printVector();

	cout << "Column Vector 2 of Matrix" << endl;
	p_testVector = p_test33->getColumnVector(2);
	p_testVector->printVector();



	//6*8
	StaticMatrix test68 = StaticMatrix(6,8);
	BasicMatrix* p_test68 = &test68;
	cout << "6*8 Matrix" << endl;
	p_test68->printMatrix();
	cout << "Row 2 of 6*8 Matrix" << endl;
	BasicVector* p_rowVector = p_test68->getRowVector(2);
	p_rowVector->printVector();

	cout << "Column 3 of 6*8 Matrix" << endl;
	BasicVector* p_columnVector = p_test68->getColumnVector(3);
	p_columnVector->printVector();

	//8*8
	StaticMatrix test88 = StaticMatrix(8,8);
	BasicMatrix* p_test88 = &test88;
	cout << "8*8 Matrix" << endl;
	p_test88->printMatrix();

	cout << "8*8 Matrix diagonal Subtraction 3 " << endl;
	p_test88->diagonalSubtraction(3);
	p_test88->printMatrix();

	cout << "8*8 Matrix diagonal Addition 3" << endl;
	p_test88->diagonalAddition(3);
	p_test88->printMatrix();

	cout << "Row 2 of 8*8 Sub Matrix Level2" << endl;
	p_rowVector = p_test88->getSubMatrixRowVector(2,2);
	p_rowVector->printVector();

	cout << "Column 3 of 8*8 Sub Matrix Level2" << endl;
	p_columnVector = p_test88->getSubMatrixColumnVector(2,3);
	p_columnVector->printVector();

	cout << "Hessenberg Column of column 0" << endl;
	p_test88->getSubMatrixHessenColumnVector(0)->printVector();
	cout << "Hessenberg Column of column 1" << endl;
	p_test88->getSubMatrixHessenColumnVector(1)->printVector();
	cout << "Hessenberg Column of column 2" << endl;
	p_test88->getSubMatrixHessenColumnVector(2)->printVector();
	cout << "Hessenberg Column of column 3" << endl;
	p_test88->getSubMatrixHessenColumnVector(3)->printVector();
	cout << "Hessenberg Column of column 4" << endl;
	p_test88->getSubMatrixHessenColumnVector(4)->printVector();
	cout << "Hessenberg Column of column 5" << endl;
	p_test88->getSubMatrixHessenColumnVector(5)->printVector();
	cout << "Hessenberg Column of column 6" << endl;
	p_test88->getSubMatrixHessenColumnVector(6)->printVector();
	cout << "Hessenberg Column of column 7" << endl;
	p_test88->getSubMatrixHessenColumnVector(7)->printVector();

	StaticMatrix normF44 = StaticMatrix(4,4);
	normF44.setMatrixElement(0,0,1);
	normF44.setMatrixElement(0,1,0.5);
	normF44.setMatrixElement(0,2,0.3333);
	normF44.setMatrixElement(0,3,0.25);

	normF44.setMatrixElement(1,0,0.5);
	normF44.setMatrixElement(1,1,0.3333);
	normF44.setMatrixElement(1,2,0.25);
	normF44.setMatrixElement(1,3,0.2);

	normF44.setMatrixElement(2,0,0.3333);
	normF44.setMatrixElement(2,1,0.25);
	normF44.setMatrixElement(2,2,0.2);
	normF44.setMatrixElement(2,3,0.1667);

	normF44.setMatrixElement(3,0,0.25);
	normF44.setMatrixElement(3,1,0.2);
	normF44.setMatrixElement(3,2,0.1667);
	normF44.setMatrixElement(3,3,0.1429);
	cout << "Matrix Precision for Forbenious Normal Test:"  << normF44.getPrecision() << endl;

	cout << "Matrix for Forbenious Normal Test" << endl;
	normF44.printMatrix();
	cout << "Forbenious Normal:" << normF44.FrobeniousNorm() << endl;


	normF44.resizeMatrix(8,8);
	cout << "resized normF44:" << endl;
	normF44.printMatrix();

	cout << "Valued normF44:" << endl;
	normF44.setMatrixElement(1,0,0.5);
	normF44.setMatrixElement(2,1,1.5);
	normF44.setMatrixElement(3,2,2.5);
	normF44.setMatrixElement(4,3,3.5);
	normF44.setMatrixElement(5,4,4.5);
	normF44.setMatrixElement(6,5,5.5);
	normF44.printMatrix();
	normF44.getColumnVector(5)->printVector();
	normF44.getRowVector(6)->printVector();

	normF44.getSubMatrixColumnVector(5,0)->printVector();
	normF44.getSubMatrixRowVector(5,1)->printVector();

	normF44.getSubMatrixHessenColumnVector(1)->printVector();
};

