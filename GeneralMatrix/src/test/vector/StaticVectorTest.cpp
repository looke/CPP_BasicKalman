/*
 * StaticVectorTester.cpp
 *
 *  Created on: 2017Äê4ÔÂ22ÈÕ
 *      Author: looke
 */

#include <test/vector/StaticVectorTest.h>

#include <iostream>
using namespace std;

StaticVectorTest::StaticVectorTest()
{};

void StaticVectorTest::test()
{
	StaticVector sv_3 = StaticVector(3);
	cout<< "StaticVector3 test" << endl;
	sv_3.printVector();
	cout<< "Norm of StaticVector3: " << sv_3.getNormOfVector() << endl;
	cout<< "Norm^2 of StaticVector3: " << sv_3.getNormPowerOfVector() << endl;

	cout<< "Reset StaticVector3[2] to 3.3" << endl;
	sv_3.setElement(2,3.3);
	sv_3.printVector();
	cout<< "Norm of StaticVector3: " << sv_3.getNormOfVector() << endl;
	cout<< "Norm^2 of StaticVector3: " << sv_3.getNormPowerOfVector() << endl;
	cout<< "------------------------------" << endl;

	StaticVector sv_10 = StaticVector(10);
	cout<< "StaticVector10 test" << endl;

	sv_10.printVector();
	cout<< "StaticVector10 reset 7 to 23.3" << endl;
	sv_10.setElement(7,23.3);
	sv_10.printVector();

	StaticVector sv2_10 = StaticVector(10);
	cout<< "Another StaticVector10 sv2_10" << endl;
	sv2_10.printVector();
	cout<< "sv2_10 copy sv10" << endl;
	sv2_10.copyVector(&sv_10);
	sv2_10.printVector();
};

