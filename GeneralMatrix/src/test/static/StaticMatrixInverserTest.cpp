/*
 * StaticMatrixInverserTest.cpp
 *
 *  Created on: 2017年4月7日
 *      Author: looke
 */
#include "test\static\StaticMatrixInverserTest.h"
#include <iostream>

using namespace std;

StaticMatrixInverserTest::StaticMatrixInverserTest()
{
	this->myTestMatrix33_B = StaticMatrix(3,3);
	myTestMatrix33_B.setMatrixElement(0,0,13);
	myTestMatrix33_B.setMatrixElement(0,1,3);
	myTestMatrix33_B.setMatrixElement(0,2,1);

	myTestMatrix33_B.setMatrixElement(1,0,0);
	myTestMatrix33_B.setMatrixElement(1,1,1);
	myTestMatrix33_B.setMatrixElement(1,2,3);

	myTestMatrix33_B.setMatrixElement(2,0,0);
	myTestMatrix33_B.setMatrixElement(2,1,0);
	myTestMatrix33_B.setMatrixElement(2,2,5);

	this->myTestMatrix33_A = StaticMatrix(3,3);
	myTestMatrix33_A.setMatrixElement(0,0,3);
	myTestMatrix33_A.setMatrixElement(0,1,3);
	myTestMatrix33_A.setMatrixElement(0,2,1);

	myTestMatrix33_A.setMatrixElement(1,0,5);
	myTestMatrix33_A.setMatrixElement(1,1,4);
	myTestMatrix33_A.setMatrixElement(1,2,3);

	myTestMatrix33_A.setMatrixElement(2,0,0);
	myTestMatrix33_A.setMatrixElement(2,1,9);
	myTestMatrix33_A.setMatrixElement(2,2,5);

	this->Binv_n_2_n_2 = 0;
	this->Binv_n_2_n_1 = 0;
	this->Binv_n_2_n = 0;

	this->Binv_n_1_n_1 = 0;
	this->Binv_n_1_n = 0;

	this->Binv_n_n = 0;
};

void StaticMatrixInverserTest::test()
{
	StaticMatrix testMatrix33 = StaticMatrix(3,3);
	//testMatrix33.init(3,3);
	//BasicMatrix* p_testMatrix33 = testMatrix33.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix33 = &testMatrix33;

	/*
	p_testMatrix33->setMatrixElement(0,0,3);
	p_testMatrix33->setMatrixElement(0,1,-1);
	p_testMatrix33->setMatrixElement(0,2,4);

	p_testMatrix33->setMatrixElement(1,0,1);
	p_testMatrix33->setMatrixElement(1,1,0);
	p_testMatrix33->setMatrixElement(1,2,0);

	p_testMatrix33->setMatrixElement(2,0,2);
	p_testMatrix33->setMatrixElement(2,1,1);
	p_testMatrix33->setMatrixElement(2,2,-5);
	*/
	/*
	p_testMatrix33->setMatrixElement(0,0,0);
	p_testMatrix33->setMatrixElement(0,1,1);
	p_testMatrix33->setMatrixElement(0,2,2);

	p_testMatrix33->setMatrixElement(1,0,1);
	p_testMatrix33->setMatrixElement(1,1,1);
	p_testMatrix33->setMatrixElement(1,2,4);

	p_testMatrix33->setMatrixElement(2,0,2);
	p_testMatrix33->setMatrixElement(2,1,-1);
	p_testMatrix33->setMatrixElement(2,2,0);
	 */
	p_testMatrix33->setMatrixElement(0,0,2);
	p_testMatrix33->setMatrixElement(0,1,3);
	p_testMatrix33->setMatrixElement(0,2,1);

	p_testMatrix33->setMatrixElement(1,0,0);
	p_testMatrix33->setMatrixElement(1,1,1);
	p_testMatrix33->setMatrixElement(1,2,3);

	p_testMatrix33->setMatrixElement(2,0,1);
	p_testMatrix33->setMatrixElement(2,1,2);
	p_testMatrix33->setMatrixElement(2,2,5);

	StaticMatrix testMatrix22 = StaticMatrix(2,2);
	//testMatrix22.init(2,2);
	//BasicMatrix* p_testMatrix22 = testMatrix22.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix22 = &testMatrix22;

	StaticMatrix testMatrix44 = StaticMatrix(4,4);
	//testMatrix44.init(4,4);
	//BasicMatrix* p_testMatrix44 = testMatrix44.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix44 = &testMatrix44;
	p_testMatrix44->setMatrixElement(0,0,5);
	p_testMatrix44->setMatrixElement(0,1,2);
	p_testMatrix44->setMatrixElement(0,2,0);
	p_testMatrix44->setMatrixElement(0,3,0);

	p_testMatrix44->setMatrixElement(1,0,2);
	p_testMatrix44->setMatrixElement(1,1,1);
	p_testMatrix44->setMatrixElement(1,2,0);
	p_testMatrix44->setMatrixElement(1,3,0);

	p_testMatrix44->setMatrixElement(2,0,0);
	p_testMatrix44->setMatrixElement(2,1,0);
	p_testMatrix44->setMatrixElement(2,2,1);
	p_testMatrix44->setMatrixElement(2,3,3);

	p_testMatrix44->setMatrixElement(3,0,0);
	p_testMatrix44->setMatrixElement(3,1,0);
	p_testMatrix44->setMatrixElement(3,2,1);
	p_testMatrix44->setMatrixElement(3,3,-1);

	cout << "OP Matrix" << endl;
	p_testMatrix44->printMatrix();


	StaticMatrixInverser inverTest = StaticMatrixInverser(p_testMatrix44);
	inverTest.generateInverseMatrix();
	cout << "Is Full Rank:" << inverTest.isOpMatrixFullRank() << endl;

	cout << "After Normalization and Elimination" << endl;
	inverTest.printOpMatrix();

	BasicMatrix* p_inversedMatrix = inverTest.getInverseMatrix();

	cout << "Inverse" << endl;
	p_inversedMatrix->printMatrix();

	StaticMatrixMultiplier multi = StaticMatrixMultiplier(p_testMatrix44, p_inversedMatrix);
	multi.multiplyCalc();
	BasicMatrix* p_multiMatrixResult = multi.getMultiplyResult();

	cout << "After multi" << endl;
	p_multiMatrixResult->printMatrix();

	cout << "calcBinv" << endl;
	calcBinv();

	cout << "myTestMatrix33 Inv Matrix" << endl;
	inverTest.reload(&myTestMatrix33_B);
	inverTest.generateInverseMatrix();
	inverTest.getInverseMatrix()->printMatrix();

	cout << "calcABinvLast2x2" << endl;
	calcABinvLast2x2();

	multi.reload(&myTestMatrix33_A,inverTest.getInverseMatrix());
	multi.multiplyCalc();
	cout << "A * Binv" << endl;
	multi.getMultiplyResult()->printMatrix();

	calcABinvFirst3x2();
};

void StaticMatrixInverserTest::calcBinv()
{
	int n = this->myTestMatrix33_B.rowNum - 1;
	double B_n_2_n_2  = this->myTestMatrix33_B.getMatrixElement(n-2,n-2);
	double B_n_2_n_1 = this->myTestMatrix33_B.getMatrixElement(n-2,n-1);
	double B_n_2_n = this->myTestMatrix33_B.getMatrixElement(n-2,n);

	double B_n_1_n_1 = this->myTestMatrix33_B.getMatrixElement(n-1,n-1);
	double B_n_1_n = this->myTestMatrix33_B.getMatrixElement(n-1,n);

	double B_n_n = this->myTestMatrix33_B.getMatrixElement(n,n);

	this->Binv_n_n = 1/B_n_n;

	this->Binv_n_1_n_1 = 1/B_n_1_n_1;
	this->Binv_n_1_n = 0 - B_n_1_n/(B_n_1_n_1 * B_n_n);

	this->Binv_n_2_n_2 = 1/B_n_2_n_2;
	this->Binv_n_2_n_1 = 0 - B_n_2_n_1/(B_n_2_n_2 * B_n_1_n_1);
	this->Binv_n_2_n = 0 - (Binv_n_2_n_2*B_n_2_n + Binv_n_2_n_1*B_n_1_n) * Binv_n_n;

	cout << "B n-2 :" << B_n_2_n_2 << "," << B_n_2_n_1 << "," << B_n_2_n <<endl;
	cout << "B n-1 :" <<"0," << B_n_1_n_1 << "," << B_n_1_n <<endl;
	cout << "B n :" <<"  0,0," << B_n_n <<endl;
	cout << "----------------" << endl;
	cout << "B^1 n-2 :" << Binv_n_2_n_2 << "," << Binv_n_2_n_1 << "," << Binv_n_2_n <<endl;
	cout << "B^1 n-1 :" <<"0," << Binv_n_1_n_1 << "," << Binv_n_1_n <<endl;
	cout << "B^1 n :" <<"  0,0," << Binv_n_n <<endl;
};

void StaticMatrixInverserTest::calcABinvLast2x2()
{
	myTestMatrix33_A.printMatrix();
	int n = this->myTestMatrix33_A.rowNum - 1;

	double A_n_1_n_2 = myTestMatrix33_A.getMatrixElement(n-1,n-2);
	double A_n_1_n_1 = myTestMatrix33_A.getMatrixElement(n-1,n-1);
	double A_n_1_n = myTestMatrix33_A.getMatrixElement(n-1,n);

	double A_n_n_1 = myTestMatrix33_A.getMatrixElement(n,n-1);
	double A_n_n = myTestMatrix33_A.getMatrixElement(n,n);

	double ABinv_n_1_n_1 = A_n_1_n_2*Binv_n_2_n_1 + A_n_1_n_1*Binv_n_1_n_1;
	double ABinv_n_1_n = A_n_1_n_2*Binv_n_2_n + A_n_1_n_1*Binv_n_1_n + A_n_1_n*Binv_n_n;

	double ABinv_n_n_1 = A_n_n_1 * Binv_n_1_n_1;
	double ABinv_n_n = A_n_n_1*Binv_n_1_n + A_n_n*Binv_n_n;

	cout << "-------ABinv last 2x2 ---------" << endl;

	cout << "AB^-1 n-1 :" << ABinv_n_1_n_1 << "," << ABinv_n_1_n <<endl;
	cout << "AB^-1 n :" <<ABinv_n_n_1 << "," << ABinv_n_n <<endl;
};

void StaticMatrixInverserTest::calcABinvFirst3x2()
{
	//A B各自矩阵的元素
	double a11,a12,a21,a22,a32;
	double b11,b12,b22;

	a11 = myTestMatrix33_A.getMatrixElement(0,0);
	a12 = myTestMatrix33_A.getMatrixElement(0,1);
	a21 = myTestMatrix33_A.getMatrixElement(1,0);
	a22 = myTestMatrix33_A.getMatrixElement(1,1);
	a32 = myTestMatrix33_A.getMatrixElement(2,1);

	b11 = myTestMatrix33_B.getMatrixElement(0,0);
	b12 = myTestMatrix33_B.getMatrixElement(0,1);
	b22 = myTestMatrix33_B.getMatrixElement(1,1);

	//A*B^-1 前两列元素
	double ABinv_11 = a11/b11;
	double ABinv_12 = (a12*b11 - a11*b12)/(b11*b22);
	double ABinv_21 = a21/b11;
	double ABinv_22 = (a22*b11 - a21*b12)/(b11*b22);
	double ABinv_32 = a32/b22;

	cout << "AB^-1 1 :" << ABinv_11 << "," << ABinv_12 <<endl;
	cout << "AB^-1 2 :" <<ABinv_21 << "," << ABinv_22 <<endl;
	cout << "AB^-1 3 :" << "0," << ABinv_32 <<endl;
};
