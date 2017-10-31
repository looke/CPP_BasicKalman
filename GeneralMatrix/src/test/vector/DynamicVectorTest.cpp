/*
 * DynamicVectorTester.cpp
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: looke
 */

#include <test/vector/DynamicVectorTest.h>
#include <iostream>
using namespace std;

DynamicVectorTest::DynamicVectorTest()
{

};

void DynamicVectorTest::test()
{
	DynamicVector dv = DynamicVector(11);
	dv.printVector();
	int size = dv.getDimension();
	cout << "Dimension of dv:" << size << endl;
	cout << "Norm of dv:" << dv.getNormOfVector() << endl;
	cout << "Norm^2 of dv:" << dv.getNormPowerOfVector() << endl;



	cout << "reset dv[1] to 3.3" << endl;
	dv.setElement(1,3.3);
	dv.printVector();


	cout << "---------------DV2-----------" << endl;
	DynamicVector dv2 = DynamicVector(11);
	dv2.printVector();


	cout << "--------DV1 Copy DV2-----------" << endl;
	dv.copyVector(&dv2);
	dv.printVector();

};
