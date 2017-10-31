/*
 * DynamicDoubleShiftQRIterationTest.cpp
 *
 *  Created on: 2017Äê5ÔÂ18ÈÕ
 *      Author: looke
 */

#include "DynamicDoubleShiftQRIterationTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "iostream"
using namespace std;

DynamicDoubleShiftQRIterationTest::DynamicDoubleShiftQRIterationTest()
{

};

void DynamicDoubleShiftQRIterationTest::test()
{
	int size = sizeof(double);
	cout << "Double Size:" << size <<endl;

	cout << "DynamicDoubleShiftQRIterationTest" << endl;

	DynamicMatrix test44 = DynamicMatrix(4,4);

	test44.setMatrixElement(0,0,1);
	test44.setMatrixElement(0,1,2);
	test44.setMatrixElement(0,2,3);
	test44.setMatrixElement(0,3,4);

	test44.setMatrixElement(1,0,5);
	test44.setMatrixElement(1,1,6);
	test44.setMatrixElement(1,2,7);
	test44.setMatrixElement(1,3,8);

	test44.setMatrixElement(2,0,0);
	test44.setMatrixElement(2,1,9);
	test44.setMatrixElement(2,2,10);
	test44.setMatrixElement(2,3,11);

	test44.setMatrixElement(3,0,0);
	test44.setMatrixElement(3,1,0);
	test44.setMatrixElement(3,2,-12);
	test44.setMatrixElement(3,3,13);

	DynamicMatrix test44_Original = DynamicMatrix(4,4);
	test44_Original.copyMatrixElementNoCheck(&test44);

	DynamicMatrix test44_QTMatrix = DynamicMatrix(4,4);
	DynamicMatrix test44_QMatrix = DynamicMatrix(4,4);

	DynamicMatrix test33 = DynamicMatrix(3,3);
	test33.setMatrixElement(0,0,1);
	test33.setMatrixElement(0,1,2);
	test33.setMatrixElement(0,2,3);

	test33.setMatrixElement(1,0,4);
	test33.setMatrixElement(1,1,5);
	test33.setMatrixElement(1,2,6);

	test33.setMatrixElement(2,0,0);
	test33.setMatrixElement(2,1,7);
	test33.setMatrixElement(2,2,8);


	DynamicDoubleShiftQRIteration doubleShiftQR = DynamicDoubleShiftQRIteration(&test44);
//	doubleShiftQR.generateHessenbergOpMatrix();
//	cout << "DynamicDoubleShiftQRIterationTest----After Hessenberg Form" << endl;
	//doubleShiftQR.getOpHessenbergMatrix()->printMatrix();
	doubleShiftQR.wilkinson_IM_QRIteration();
	test44_QTMatrix.copyMatrixElementNoCheck(doubleShiftQR.getQTMatrix_Total());
	test44_QMatrix.copyMatrixElementNoCheck(doubleShiftQR.getQMatrix_Total());

	DynamicMatrixMultiplier dmultip = DynamicMatrixMultiplier(&test44_QTMatrix,&test44_Original);
	dmultip.multiplyCalc();
	test44_Original.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	dmultip.reload(&test44_Original, &test44_QMatrix);
	dmultip.multiplyCalc();
	test44_Original.copyMatrixElementNoCheck(dmultip.getMultiplyResult());

	cout << "QT * Orignal * Q" << endl;
	test44_Original.printMatrix();

	//doubleShiftQR.reload(&test33);
	//doubleShiftQR.wilkinson_IM_QRIteration();
	/*
	test44.copyMatrixElementNoCheck(doubleShiftQR.getOpHessenbergMatrix());
	test44.printMatrix();

	DynamicMatrix testQT = DynamicMatrix(4,4);
	DynamicMatrix testQ = DynamicMatrix(4,4);

	doubleShiftQR.wilkinson_IM_QRIteration_Step();

	testQT.copyMatrixElementNoCheck(doubleShiftQR.getQTMatrix_Total());
	testQ.copyMatrixElementNoCheck(doubleShiftQR.getQMatrix_Total());

	DynamicMatrixMultiplier dmultip = DynamicMatrixMultiplier(&testQT, &test44);
	dmultip.multiplyCalc();
	test44.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	dmultip.reload(&test44, &testQ);
	dmultip.multiplyCalc();
	test44.copyMatrixElementNoCheck(dmultip.getMultiplyResult());

	cout << "DynamicDoubleShiftQRIterationTest----Hessenberg after One Step" << endl;
	doubleShiftQR.getOpHessenbergMatrix()->printMatrix();

	cout << "DynamicDoubleShiftQRIterationTest----QT * test44 * Q after One Step" << endl;
	test44.printMatrix();
	*/
};


