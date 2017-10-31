/*
 * StaticMatrixTransposerTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ26ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "basic\BasicMatrix.h"
#include "StaticMatrixMultipleTest.h"
#include "..\matrix\static\StaticMatrix.h"
#include "StaticMatrixTransposerTest.h"
using namespace std;

StaticMatrixTransposerTest::StaticMatrixTransposerTest()
{};

void StaticMatrixTransposerTest::test()
{
	StaticMatrix Matrix1 = StaticMatrix(3,3);
	BasicMatrix* p_Matrix1 = &Matrix1;

	cout << "Matrix 1 Before Transpose" << endl;
	p_Matrix1->printMatrix();

	StaticMatrixTransposer tr = StaticMatrixTransposer(p_Matrix1);
	tr.transposeMatrix();
	p_Matrix1->copyMatrixElementNoCheck(tr.getTransposeMatrix());
	cout << "Matrix 1 After Transpose" << endl;
	p_Matrix1->printMatrix();

	StaticMatrix Matrix2 = StaticMatrix(4,4);
	BasicMatrix* p_Matrix2 = &Matrix2;
	cout << "Matrix 2 Before Transpose" << endl;
	p_Matrix2->printMatrix();

	tr.reload(p_Matrix2);
	tr.transposeMatrix();
	p_Matrix2->copyMatrixElementNoCheck(tr.getTransposeMatrix());
	cout << "Matrix 2 After Transpose" << endl;
	p_Matrix2->printMatrix();


	StaticMatrix Matrix3 = StaticMatrix(4,3);
	BasicMatrix* p_Matrix3 = &Matrix3;

	cout << "Matrix 3 Before Transpose" << endl;
	p_Matrix3->printMatrix();

	tr.reload(p_Matrix3);
	tr.transposeMatrix();
	StaticMatrix Matrix3T = StaticMatrix(3,4);
	BasicMatrix* p_Matrix3T = &Matrix3T;
	p_Matrix3T->copyMatrixElementNoCheck(tr.getTransposeMatrix());
	cout << "Matrix 3 After Transpose" << endl;
	p_Matrix3T->printMatrix();


};

