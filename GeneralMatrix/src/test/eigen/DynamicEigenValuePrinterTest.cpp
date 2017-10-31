/*
 * DynamicEigenValuePrinterTest.cpp
 *
 *  Created on: 2017Äê6ÔÂ3ÈÕ
 *      Author: looke
 */

#include "..\test\eigen\DynamicEigenValuePrinterTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include <time.h>
#include "iostream"
using namespace std;

DynamicEigenValuePrinterTest::DynamicEigenValuePrinterTest()
{};

void DynamicEigenValuePrinterTest::test()
{
	DynamicMatrix test66 = DynamicMatrix(6,6);
	test66.setMatrixElement(0,0,1);
	test66.setMatrixElement(0,1,2);
	test66.setMatrixElement(0,2,3);
	test66.setMatrixElement(0,3,4);
	test66.setMatrixElement(0,4,5);
	test66.setMatrixElement(0,5,6);

	test66.setMatrixElement(1,0,7);
	test66.setMatrixElement(1,1,8);
	test66.setMatrixElement(1,2,9);
	test66.setMatrixElement(1,3,10);
	test66.setMatrixElement(1,4,11);
	test66.setMatrixElement(1,5,12);

	test66.setMatrixElement(2,0,0);
	test66.setMatrixElement(2,1,13);
	test66.setMatrixElement(2,2,14);
	test66.setMatrixElement(2,3,15);
	test66.setMatrixElement(2,4,16);
	test66.setMatrixElement(2,5,17);

	test66.setMatrixElement(3,0,0);
	test66.setMatrixElement(3,1,0);
	test66.setMatrixElement(3,2,18);
	test66.setMatrixElement(3,3,19);
	test66.setMatrixElement(3,4,20);
	test66.setMatrixElement(3,5,21);

	test66.setMatrixElement(4,0,0);
	test66.setMatrixElement(4,1,0);
	test66.setMatrixElement(4,2,0);
	test66.setMatrixElement(4,3,22);
	test66.setMatrixElement(4,4,23);
	test66.setMatrixElement(4,5,24);

	test66.setMatrixElement(5,0,0);
	test66.setMatrixElement(5,1,0);
	test66.setMatrixElement(5,2,0);
	test66.setMatrixElement(5,3,0);
	test66.setMatrixElement(5,4,25);
	test66.setMatrixElement(5,5,26);

	test66.printMatrix();
	cout << "------------------------------" << endl;
	DynamicMatrix test77 = DynamicMatrix(7,7);
	test77.setMatrixElement(0,0,1);
	test77.setMatrixElement(0,1,2);
	test77.setMatrixElement(0,2,3);
	test77.setMatrixElement(0,3,4);
	test77.setMatrixElement(0,4,5);
	test77.setMatrixElement(0,5,6);
	test77.setMatrixElement(0,6,7);

	test77.setMatrixElement(1,0,8);
	test77.setMatrixElement(1,1,9);
	test77.setMatrixElement(1,2,10);
	test77.setMatrixElement(1,3,11);
	test77.setMatrixElement(1,4,12);
	test77.setMatrixElement(1,5,13);
	test77.setMatrixElement(1,6,14);

	test77.setMatrixElement(2,0,0);
	test77.setMatrixElement(2,1,15);
	test77.setMatrixElement(2,2,16);
	test77.setMatrixElement(2,3,17);
	test77.setMatrixElement(2,4,18);
	test77.setMatrixElement(2,5,19);
	test77.setMatrixElement(2,6,20);

	test77.setMatrixElement(3,0,0);
	test77.setMatrixElement(3,1,0);
	test77.setMatrixElement(3,2,21);
	test77.setMatrixElement(3,3,22);
	test77.setMatrixElement(3,4,23);
	test77.setMatrixElement(3,5,24);
	test77.setMatrixElement(3,6,25);

	test77.setMatrixElement(4,0,0);
	test77.setMatrixElement(4,1,0);
	test77.setMatrixElement(4,2,0);
	test77.setMatrixElement(4,3,26);
	test77.setMatrixElement(4,4,27);
	test77.setMatrixElement(4,5,28);
	test77.setMatrixElement(4,6,29);

	test77.setMatrixElement(5,0,0);
	test77.setMatrixElement(5,1,0);
	test77.setMatrixElement(5,2,0);
	test77.setMatrixElement(5,3,0);
	test77.setMatrixElement(5,4,30);
	test77.setMatrixElement(5,5,31);
	test77.setMatrixElement(5,6,32);

	test77.setMatrixElement(6,0,0);
	test77.setMatrixElement(6,1,0);
	test77.setMatrixElement(6,2,0);
	test77.setMatrixElement(6,3,0);
	test77.setMatrixElement(6,4,0);
	test77.setMatrixElement(6,5,33);
	test77.setMatrixElement(6,6,34);

	test77.printMatrix();

	cout << "------------------------------" << endl;
	DynamicMatrix test88 = DynamicMatrix(8,8);
	test88.setMatrixElement(0,0,1);
	test88.setMatrixElement(0,1,2);
	test88.setMatrixElement(0,2,3);
	test88.setMatrixElement(0,3,4);
	test88.setMatrixElement(0,4,5);
	test88.setMatrixElement(0,5,6);
	test88.setMatrixElement(0,6,7);
	test88.setMatrixElement(0,7,8);

	test88.setMatrixElement(1,0,9);
	test88.setMatrixElement(1,1,10);
	test88.setMatrixElement(1,2,11);
	test88.setMatrixElement(1,3,12);
	test88.setMatrixElement(1,4,13);
	test88.setMatrixElement(1,5,14);
	test88.setMatrixElement(1,6,15);
	test88.setMatrixElement(1,7,16);

	test88.setMatrixElement(2,0,17);
	test88.setMatrixElement(2,1,18);
	test88.setMatrixElement(2,2,19);
	test88.setMatrixElement(2,3,20);
	test88.setMatrixElement(2,4,21);
	test88.setMatrixElement(2,5,22);
	test88.setMatrixElement(2,6,23);
	test88.setMatrixElement(2,7,24);

	test88.setMatrixElement(3,0,25);
	test88.setMatrixElement(3,1,26);
	test88.setMatrixElement(3,2,27);
	test88.setMatrixElement(3,3,28);
	test88.setMatrixElement(3,4,29);
	test88.setMatrixElement(3,5,30);
	test88.setMatrixElement(3,6,31);
	test88.setMatrixElement(3,7,32);

	test88.setMatrixElement(4,0,33);
	test88.setMatrixElement(4,1,34);
	test88.setMatrixElement(4,2,35);
	test88.setMatrixElement(4,3,36);
	test88.setMatrixElement(4,4,37);
	test88.setMatrixElement(4,5,38);
	test88.setMatrixElement(4,6,39);
	test88.setMatrixElement(4,7,40);

	test88.setMatrixElement(5,0,41);
	test88.setMatrixElement(5,1,42);
	test88.setMatrixElement(5,2,43);
	test88.setMatrixElement(5,3,44);
	test88.setMatrixElement(5,4,45);
	test88.setMatrixElement(5,5,46);
	test88.setMatrixElement(5,6,47);
	test88.setMatrixElement(5,7,48);

	test88.setMatrixElement(6,0,49);
	test88.setMatrixElement(6,1,50);
	test88.setMatrixElement(6,2,51);
	test88.setMatrixElement(6,3,52);
	test88.setMatrixElement(6,4,53);
	test88.setMatrixElement(6,5,54);
	test88.setMatrixElement(6,6,55);
	test88.setMatrixElement(6,7,56);

	test88.setMatrixElement(7,0,57);
	test88.setMatrixElement(7,1,58);
	test88.setMatrixElement(7,2,59);
	test88.setMatrixElement(7,3,60);
	test88.setMatrixElement(7,4,61);
	test88.setMatrixElement(7,5,62);
	test88.setMatrixElement(7,6,63);
	test88.setMatrixElement(7,7,64);

	test88.printMatrix();
	cout << "------------------------------" << endl;
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
	test44_A.printMatrix();
	cout << "------------------------------" << endl;
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

	test44_B.printMatrix();

	cout << "------------------------------" << endl;
	DynamicMatrix test44_B_2 = DynamicMatrix(4,4);

	test44_B_2.setMatrixElement(0,0,1);
	test44_B_2.setMatrixElement(0,1,2);
	test44_B_2.setMatrixElement(0,2,3);
	test44_B_2.setMatrixElement(0,3,4);

	test44_B_2.setMatrixElement(1,0,2);
	test44_B_2.setMatrixElement(1,1,5);
	test44_B_2.setMatrixElement(1,2,6);
	test44_B_2.setMatrixElement(1,3,7);

	test44_B_2.setMatrixElement(2,0,2);
	test44_B_2.setMatrixElement(2,1,3);
	test44_B_2.setMatrixElement(2,2,8);
	test44_B_2.setMatrixElement(2,3,9);

	test44_B_2.setMatrixElement(3,0,5);
	test44_B_2.setMatrixElement(3,1,2);
	test44_B_2.setMatrixElement(3,2,3);
	test44_B_2.setMatrixElement(3,3,10);

	test44_B_2.printMatrix();
	cout << "------------------------------" << endl;

	DynamicMatrix ge_test66_A = DynamicMatrix(6,6);

	ge_test66_A.setMatrixElement(0,0,1);
	ge_test66_A.setMatrixElement(0,1,2);
	ge_test66_A.setMatrixElement(0,2,3);
	ge_test66_A.setMatrixElement(0,3,4);
	ge_test66_A.setMatrixElement(0,4,5);
	ge_test66_A.setMatrixElement(0,5,6);

	ge_test66_A.setMatrixElement(1,0,7);
	ge_test66_A.setMatrixElement(1,1,8);
	ge_test66_A.setMatrixElement(1,2,9);
	ge_test66_A.setMatrixElement(1,3,10);
	ge_test66_A.setMatrixElement(1,4,11);
	ge_test66_A.setMatrixElement(1,5,12);

	ge_test66_A.setMatrixElement(2,0,0);
	ge_test66_A.setMatrixElement(2,1,13);
	ge_test66_A.setMatrixElement(2,2,14);
	ge_test66_A.setMatrixElement(2,3,15);
	ge_test66_A.setMatrixElement(2,4,16);
	ge_test66_A.setMatrixElement(2,5,17);

	ge_test66_A.setMatrixElement(3,0,0);
	ge_test66_A.setMatrixElement(3,1,0);
	ge_test66_A.setMatrixElement(3,2,18);
	ge_test66_A.setMatrixElement(3,3,19);
	ge_test66_A.setMatrixElement(3,4,20);
	ge_test66_A.setMatrixElement(3,5,21);

	ge_test66_A.setMatrixElement(4,0,0);
	ge_test66_A.setMatrixElement(4,1,0);
	ge_test66_A.setMatrixElement(4,2,0);
	ge_test66_A.setMatrixElement(4,3,22);
	ge_test66_A.setMatrixElement(4,4,23);
	ge_test66_A.setMatrixElement(4,5,24);

	ge_test66_A.setMatrixElement(5,0,0);
	ge_test66_A.setMatrixElement(5,1,0);
	ge_test66_A.setMatrixElement(5,2,0);
	ge_test66_A.setMatrixElement(5,3,0);
	ge_test66_A.setMatrixElement(5,4,25);
	ge_test66_A.setMatrixElement(5,5,26);

	ge_test66_A.printMatrix();
	cout << "------------------------------" << endl;
	DynamicMatrix ge_test66_B = DynamicMatrix(6,6);

	ge_test66_B.setMatrixElement(0,0,1);
	ge_test66_B.setMatrixElement(0,1,2);
	ge_test66_B.setMatrixElement(0,2,3);
	ge_test66_B.setMatrixElement(0,3,4);
	ge_test66_B.setMatrixElement(0,4,5);
	ge_test66_B.setMatrixElement(0,5,6);

	ge_test66_B.setMatrixElement(1,0,0);
	ge_test66_B.setMatrixElement(1,1,7);
	ge_test66_B.setMatrixElement(1,2,8);
	ge_test66_B.setMatrixElement(1,3,9);
	ge_test66_B.setMatrixElement(1,4,10);
	ge_test66_B.setMatrixElement(1,5,11);

	ge_test66_B.setMatrixElement(2,0,0);
	ge_test66_B.setMatrixElement(2,1,0);
	ge_test66_B.setMatrixElement(2,2,12);
	ge_test66_B.setMatrixElement(2,3,13);
	ge_test66_B.setMatrixElement(2,4,14);
	ge_test66_B.setMatrixElement(2,5,15);

	ge_test66_B.setMatrixElement(3,0,0);
	ge_test66_B.setMatrixElement(3,1,0);
	ge_test66_B.setMatrixElement(3,2,0);
	ge_test66_B.setMatrixElement(3,3,16);
	ge_test66_B.setMatrixElement(3,4,17);
	ge_test66_B.setMatrixElement(3,5,18);

	ge_test66_B.setMatrixElement(4,0,0);
	ge_test66_B.setMatrixElement(4,1,0);
	ge_test66_B.setMatrixElement(4,2,0);
	ge_test66_B.setMatrixElement(4,3,0);
	ge_test66_B.setMatrixElement(4,4,19);
	ge_test66_B.setMatrixElement(4,5,20);

	ge_test66_B.setMatrixElement(5,0,0);
	ge_test66_B.setMatrixElement(5,1,0);
	ge_test66_B.setMatrixElement(5,2,0);
	ge_test66_B.setMatrixElement(5,3,0);
	ge_test66_B.setMatrixElement(5,4,0);
	ge_test66_B.setMatrixElement(5,5,21);
	ge_test66_B.printMatrix();

	cout << "------------------------------" << endl;
	DynamicMatrix ge_test66_B_2 = DynamicMatrix(6,6);

	ge_test66_B_2.setMatrixElement(0,0,0);
	ge_test66_B_2.setMatrixElement(0,1,0);
	ge_test66_B_2.setMatrixElement(0,2,2);
	ge_test66_B_2.setMatrixElement(0,3,0);
	ge_test66_B_2.setMatrixElement(0,4,0);
	ge_test66_B_2.setMatrixElement(0,5,0);

	ge_test66_B_2.setMatrixElement(1,0,0);
	ge_test66_B_2.setMatrixElement(1,1,-1);
	ge_test66_B_2.setMatrixElement(1,2,0);
	ge_test66_B_2.setMatrixElement(1,3,0);
	ge_test66_B_2.setMatrixElement(1,4,0);
	ge_test66_B_2.setMatrixElement(1,5,0);

	ge_test66_B_2.setMatrixElement(2,0,2);
	ge_test66_B_2.setMatrixElement(2,1,0);
	ge_test66_B_2.setMatrixElement(2,2,0);
	ge_test66_B_2.setMatrixElement(2,3,0);
	ge_test66_B_2.setMatrixElement(2,4,0);
	ge_test66_B_2.setMatrixElement(2,5,0);

	ge_test66_B_2.setMatrixElement(3,0,0);
	ge_test66_B_2.setMatrixElement(3,1,0);
	ge_test66_B_2.setMatrixElement(3,2,0);
	ge_test66_B_2.setMatrixElement(3,3,0);
	ge_test66_B_2.setMatrixElement(3,4,0);
	ge_test66_B_2.setMatrixElement(3,5,0);

	ge_test66_B_2.setMatrixElement(4,0,0);
	ge_test66_B_2.setMatrixElement(4,1,0);
	ge_test66_B_2.setMatrixElement(4,2,0);
	ge_test66_B_2.setMatrixElement(4,3,0);
	ge_test66_B_2.setMatrixElement(4,4,0);
	ge_test66_B_2.setMatrixElement(4,5,0);

	ge_test66_B_2.setMatrixElement(5,0,0);
	ge_test66_B_2.setMatrixElement(5,1,0);
	ge_test66_B_2.setMatrixElement(5,2,0);
	ge_test66_B_2.setMatrixElement(5,3,0);
	ge_test66_B_2.setMatrixElement(5,4,0);
	ge_test66_B_2.setMatrixElement(5,5,0);
	ge_test66_B_2.printMatrix();

	cout << "------------------------------" << endl;
	DynamicMatrix ge_test88_A = DynamicMatrix(8,8);
	ge_test88_A.setMatrixElement(0,0,1);
	ge_test88_A.setMatrixElement(0,1,2);
	ge_test88_A.setMatrixElement(0,2,3);
	ge_test88_A.setMatrixElement(0,3,4);
	ge_test88_A.setMatrixElement(0,4,5);
	ge_test88_A.setMatrixElement(0,5,6);
	ge_test88_A.setMatrixElement(0,6,7);
	ge_test88_A.setMatrixElement(0,7,8);

	ge_test88_A.setMatrixElement(1,0,9);
	ge_test88_A.setMatrixElement(1,1,10);
	ge_test88_A.setMatrixElement(1,2,11);
	ge_test88_A.setMatrixElement(1,3,12);
	ge_test88_A.setMatrixElement(1,4,13);
	ge_test88_A.setMatrixElement(1,5,14);
	ge_test88_A.setMatrixElement(1,6,15);
	ge_test88_A.setMatrixElement(1,7,16);

	ge_test88_A.setMatrixElement(2,0,17);
	ge_test88_A.setMatrixElement(2,1,18);
	ge_test88_A.setMatrixElement(2,2,19);
	ge_test88_A.setMatrixElement(2,3,20);
	ge_test88_A.setMatrixElement(2,4,21);
	ge_test88_A.setMatrixElement(2,5,22);
	ge_test88_A.setMatrixElement(2,6,23);
	ge_test88_A.setMatrixElement(2,7,24);

	ge_test88_A.setMatrixElement(3,0,25);
	ge_test88_A.setMatrixElement(3,1,26);
	ge_test88_A.setMatrixElement(3,2,27);
	ge_test88_A.setMatrixElement(3,3,28);
	ge_test88_A.setMatrixElement(3,4,29);
	ge_test88_A.setMatrixElement(3,5,30);
	ge_test88_A.setMatrixElement(3,6,31);
	ge_test88_A.setMatrixElement(3,7,32);

	ge_test88_A.setMatrixElement(4,0,33);
	ge_test88_A.setMatrixElement(4,1,34);
	ge_test88_A.setMatrixElement(4,2,35);
	ge_test88_A.setMatrixElement(4,3,36);
	ge_test88_A.setMatrixElement(4,4,37);
	ge_test88_A.setMatrixElement(4,5,38);
	ge_test88_A.setMatrixElement(4,6,39);
	ge_test88_A.setMatrixElement(4,7,40);

	ge_test88_A.setMatrixElement(5,0,41);
	ge_test88_A.setMatrixElement(5,1,42);
	ge_test88_A.setMatrixElement(5,2,43);
	ge_test88_A.setMatrixElement(5,3,44);
	ge_test88_A.setMatrixElement(5,4,45);
	ge_test88_A.setMatrixElement(5,5,46);
	ge_test88_A.setMatrixElement(5,6,47);
	ge_test88_A.setMatrixElement(5,7,48);

	ge_test88_A.setMatrixElement(6,0,49);
	ge_test88_A.setMatrixElement(6,1,50);
	ge_test88_A.setMatrixElement(6,2,51);
	ge_test88_A.setMatrixElement(6,3,52);
	ge_test88_A.setMatrixElement(6,4,53);
	ge_test88_A.setMatrixElement(6,5,54);
	ge_test88_A.setMatrixElement(6,6,55);
	ge_test88_A.setMatrixElement(6,7,56);

	ge_test88_A.setMatrixElement(7,0,57);
	ge_test88_A.setMatrixElement(7,1,58);
	ge_test88_A.setMatrixElement(7,2,59);
	ge_test88_A.setMatrixElement(7,3,60);
	ge_test88_A.setMatrixElement(7,4,61);
	ge_test88_A.setMatrixElement(7,5,62);
	ge_test88_A.setMatrixElement(7,6,63);
	ge_test88_A.setMatrixElement(7,7,64);
	ge_test88_A.printMatrix();

	cout << "------------------------------" << endl;
	DynamicMatrix ge_test88_B = DynamicMatrix(8,8);
	ge_test88_B.setMatrixElement(0,0,1);
	ge_test88_B.setMatrixElement(0,1,2);
	ge_test88_B.setMatrixElement(0,2,3);
	ge_test88_B.setMatrixElement(0,3,4);
	ge_test88_B.setMatrixElement(0,4,5);
	ge_test88_B.setMatrixElement(0,5,6);
	ge_test88_B.setMatrixElement(0,6,7);
	ge_test88_B.setMatrixElement(0,7,8);

	ge_test88_B.setMatrixElement(1,0,0);
	ge_test88_B.setMatrixElement(1,1,9);
	ge_test88_B.setMatrixElement(1,2,10);
	ge_test88_B.setMatrixElement(1,3,11);
	ge_test88_B.setMatrixElement(1,4,12);
	ge_test88_B.setMatrixElement(1,5,13);
	ge_test88_B.setMatrixElement(1,6,14);
	ge_test88_B.setMatrixElement(1,7,15);

	ge_test88_B.setMatrixElement(2,0,0);
	ge_test88_B.setMatrixElement(2,1,0);
	ge_test88_B.setMatrixElement(2,2,16);
	ge_test88_B.setMatrixElement(2,3,17);
	ge_test88_B.setMatrixElement(2,4,18);
	ge_test88_B.setMatrixElement(2,5,19);
	ge_test88_B.setMatrixElement(2,6,20);
	ge_test88_B.setMatrixElement(2,7,21);

	ge_test88_B.setMatrixElement(3,0,0);
	ge_test88_B.setMatrixElement(3,1,0);
	ge_test88_B.setMatrixElement(3,2,0);
	ge_test88_B.setMatrixElement(3,3,22);
	ge_test88_B.setMatrixElement(3,4,23);
	ge_test88_B.setMatrixElement(3,5,24);
	ge_test88_B.setMatrixElement(3,6,25);
	ge_test88_B.setMatrixElement(3,7,26);

	ge_test88_B.setMatrixElement(4,0,0);
	ge_test88_B.setMatrixElement(4,1,0);
	ge_test88_B.setMatrixElement(4,2,0);
	ge_test88_B.setMatrixElement(4,3,0);
	ge_test88_B.setMatrixElement(4,4,27);
	ge_test88_B.setMatrixElement(4,5,28);
	ge_test88_B.setMatrixElement(4,6,29);
	ge_test88_B.setMatrixElement(4,7,30);

	ge_test88_B.setMatrixElement(5,0,0);
	ge_test88_B.setMatrixElement(5,1,0);
	ge_test88_B.setMatrixElement(5,2,0);
	ge_test88_B.setMatrixElement(5,3,0);
	ge_test88_B.setMatrixElement(5,4,0);
	ge_test88_B.setMatrixElement(5,5,31);
	ge_test88_B.setMatrixElement(5,6,32);
	ge_test88_B.setMatrixElement(5,7,33);

	ge_test88_B.setMatrixElement(6,0,0);
	ge_test88_B.setMatrixElement(6,1,0);
	ge_test88_B.setMatrixElement(6,2,0);
	ge_test88_B.setMatrixElement(6,3,0);
	ge_test88_B.setMatrixElement(6,4,0);
	ge_test88_B.setMatrixElement(6,5,0);
	ge_test88_B.setMatrixElement(6,6,34);
	ge_test88_B.setMatrixElement(6,7,35);

	ge_test88_B.setMatrixElement(7,0,0);
	ge_test88_B.setMatrixElement(7,1,0);
	ge_test88_B.setMatrixElement(7,2,0);
	ge_test88_B.setMatrixElement(7,3,0);
	ge_test88_B.setMatrixElement(7,4,0);
	ge_test88_B.setMatrixElement(7,5,0);
	ge_test88_B.setMatrixElement(7,6,0);
	ge_test88_B.setMatrixElement(7,7,36);
	ge_test88_B.printMatrix();

	DynamicEigenValuePrinter eigenPrinter = DynamicEigenValuePrinter(&test66);

	//eigenPrinter.printEigenValues(&test66);
	//eigenPrinter.printEigenValues(&ge_test88_A,&ge_test88_B);
	//eigenPrinter.printEigenValues(&test44_A,&test44_B_2);
	eigenPrinter.printEigenValues(&ge_test66_A,&ge_test66_B_2);
};


