/*
 * DynamicMatrixTest.cpp
 *
 *  Created on: 2017Äê3ÔÂ25ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "DynamicMatrixTest.h"
#include "..\vector\basic\BasicVector.h"

using namespace std;


DynamicMatrixTest::DynamicMatrixTest()
{
};

void DynamicMatrixTest::test()
{
	DynamicMatrix test = DynamicMatrix(3,3);
	cout << "DynamicMatrix 3*3 test" << endl;
	test.printMatrix();

	cout << "test swap column 0 to 2" << endl;
	test.swapColumn(0,2);
	test.printMatrix();

	cout << "test swap diag element 0 to 2" << endl;
	test.swapDiagElement(0,2);
	test.printMatrix();

	BasicVector* p_testRowV = test.getRowVector(0);
	cout << "Row 0 of Matrix test is:" << endl;
	p_testRowV->printVector();

	//7*7
	DynamicMatrix test77 = DynamicMatrix(7,7);
	cout << "DynamicMatrix 7*7 test" << endl;
	test77.printMatrix();

	cout << "DynamicMatrix 7*7 diagonal Subtraction 2" << endl;
	test77.diagonalSubtraction(2);
	test77.printMatrix();

	cout << "DynamicMatrix 7*7 diagonal Addition 2" << endl;
	test77.diagonalAddition(2);
	test77.printMatrix();

	cout << "DynamicMatrix 7*7 Column 3 Vector:" << endl;
	BasicVector* p_subMatrixColumn = test77.getColumnVector(3);
	p_subMatrixColumn->printVector();
	cout << "DynamicMatrix 7*7 Row 0 Vector:" << endl;
	BasicVector* p_subMatrixRow = test77.getRowVector(0);
	p_subMatrixRow->printVector();

	cout << "DynamicMatrix 7*7 Sub Matrix level 4 Column 0 Vector:" << endl;
	p_subMatrixColumn = test77.getSubMatrixColumnVector(4,2);
	p_subMatrixColumn->printVector();

	cout << "DynamicMatrix 7*7 Sub Matrix level 6 Row 0 Vector:" << endl;
	p_subMatrixRow = test77.getSubMatrixRowVector(4,2);
	p_subMatrixRow->printVector();


	cout << "indexOfZeroOnDiagonal" << endl;
	test77.setMatrixElement(5,6,0);
	test77.printMatrix();
	cout << test77.indexOfZeroOnDiagonal() << endl;

	cout << "Hessenberg Column Vector of column 0" << endl;
	test77.getSubMatrixHessenColumnVector(0)->printVector();
	cout << "Hessenberg Column Vector of column 1" << endl;
	test77.getSubMatrixHessenColumnVector(1)->printVector();
	cout << "Hessenberg Column Vector of column 2" << endl;
	test77.getSubMatrixHessenColumnVector(2)->printVector();
	cout << "Hessenberg Column Vector of column 3" << endl;
	test77.getSubMatrixHessenColumnVector(3)->printVector();
	cout << "Hessenberg Column Vector of column 4" << endl;
	test77.getSubMatrixHessenColumnVector(4)->printVector();
	cout << "Hessenberg Column Vector of column 5" << endl;
	test77.getSubMatrixHessenColumnVector(5)->printVector();
	cout << "Hessenberg Column Vector of column 6" << endl;
	test77.getSubMatrixHessenColumnVector(6)->printVector();

	DynamicMatrix normF44 = DynamicMatrix(4,4);
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



	DynamicMatrix hessenbergTest55 = DynamicMatrix(5,5);
	hessenbergTest55.setMatrixElement(0,0,1);
	hessenbergTest55.setMatrixElement(0,1,0.5);
	hessenbergTest55.setMatrixElement(0,2,0.3333);
	hessenbergTest55.setMatrixElement(0,3,0.25);
	hessenbergTest55.setMatrixElement(0,4,0.25);

	hessenbergTest55.setMatrixElement(1,0,0.5);
	hessenbergTest55.setMatrixElement(1,1,0.3333);
	hessenbergTest55.setMatrixElement(1,2,0.25);
	hessenbergTest55.setMatrixElement(1,3,0.2);
	hessenbergTest55.setMatrixElement(1,4,0.25);

	hessenbergTest55.setMatrixElement(2,0,0);
	hessenbergTest55.setMatrixElement(2,1,0);
	hessenbergTest55.setMatrixElement(2,2,0.2);
	hessenbergTest55.setMatrixElement(2,3,0.1667);
	hessenbergTest55.setMatrixElement(2,4,0.25);

	hessenbergTest55.setMatrixElement(3,0,0);
	hessenbergTest55.setMatrixElement(3,1,0);
	hessenbergTest55.setMatrixElement(3,2,0.1667);
	hessenbergTest55.setMatrixElement(3,3,0.1429);
	hessenbergTest55.setMatrixElement(3,4,0.25);

	hessenbergTest55.setMatrixElement(4,0,0);
	hessenbergTest55.setMatrixElement(4,1,0);
	hessenbergTest55.setMatrixElement(4,2,0);
	hessenbergTest55.setMatrixElement(4,3,0.1429);
	hessenbergTest55.setMatrixElement(4,4,0.25);

	cout << "IS Upper Hessenberg Test" << endl;
	hessenbergTest55.printMatrix();
	cout << "Matrix hessenberg:" << hessenbergTest55.isUpperHessenbergMatrix() << endl;

	DynamicMatrix tiranlgeTest44 = DynamicMatrix(4,4);
	tiranlgeTest44.setMatrixElement(0,0,1);
	tiranlgeTest44.setMatrixElement(0,1,0.5);
	tiranlgeTest44.setMatrixElement(0,2,0.3333);
	tiranlgeTest44.setMatrixElement(0,3,0.25);

	tiranlgeTest44.setMatrixElement(1,0,0);
	tiranlgeTest44.setMatrixElement(1,1,0.3333);
	tiranlgeTest44.setMatrixElement(1,2,0.25);
	tiranlgeTest44.setMatrixElement(1,3,0.2);

	tiranlgeTest44.setMatrixElement(2,0,0);
	tiranlgeTest44.setMatrixElement(2,1,0);
	tiranlgeTest44.setMatrixElement(2,2,0.2);
	tiranlgeTest44.setMatrixElement(2,3,0.1667);

	tiranlgeTest44.setMatrixElement(3,0,0);
	tiranlgeTest44.setMatrixElement(3,1,0);
	tiranlgeTest44.setMatrixElement(3,2,0);
	tiranlgeTest44.setMatrixElement(3,3,0.1429);

	cout << "IS Upper Trianlge Test" << endl;
	tiranlgeTest44.printMatrix();
	cout << "Matrix Trianlge:" << tiranlgeTest44.isUpperTriangleMatrix() << endl;

};

