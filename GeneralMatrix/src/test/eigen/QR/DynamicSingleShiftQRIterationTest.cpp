/*
 * DynamicSingelShiftQRIterationTest.cpp
 *
 *  Created on: 2017年5月13日
 *      Author: looke
 */

#include "..\test\eigen\QR\DynamicSingleShiftQRIterationTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "iostream"
using namespace std;

DynamicSingleShiftQRIterationTest::DynamicSingleShiftQRIterationTest()
{};

void DynamicSingleShiftQRIterationTest::test()
{
	cout << "DynamicSingleShiftQRIterationTest" << endl;

	DynamicMatrix test44 = DynamicMatrix(4,4);

	test44.setMatrixElement(0,0,54);
	test44.setMatrixElement(0,1,40);
	test44.setMatrixElement(0,2,10);
	test44.setMatrixElement(0,3,76);

	test44.setMatrixElement(1,0,47);
	test44.setMatrixElement(1,1,20);
	test44.setMatrixElement(1,2,94);
	test44.setMatrixElement(1,3,49);

	test44.setMatrixElement(2,0,26);
	test44.setMatrixElement(2,1,80);
	test44.setMatrixElement(2,2,94);
	test44.setMatrixElement(2,3,70);

	test44.setMatrixElement(3,0,3);
	test44.setMatrixElement(3,1,92);
	test44.setMatrixElement(3,2,83);
	test44.setMatrixElement(3,3,45);

	DynamicMatrix test33 = DynamicMatrix(3,3);

	/*
	 *实数矩阵 具有复数特征值
	test33.setMatrixElement(0,0,1);
	test33.setMatrixElement(0,1,2);
	test33.setMatrixElement(0,2,3);

	test33.setMatrixElement(1,0,3);
	test33.setMatrixElement(1,1,1);
	test33.setMatrixElement(1,2,2);

	test33.setMatrixElement(2,0,2);
	test33.setMatrixElement(2,1,3);
	test33.setMatrixElement(2,2,1);
	*/

	//特征值 9 -1 0
	test33.setMatrixElement(0,0,1);
	test33.setMatrixElement(0,1,2);
	test33.setMatrixElement(0,2,3);

	test33.setMatrixElement(1,0,2);
	test33.setMatrixElement(1,1,1);
	test33.setMatrixElement(1,2,3);

	test33.setMatrixElement(2,0,3);
	test33.setMatrixElement(2,1,3);
	test33.setMatrixElement(2,2,6);

	DynamicMatrix test22 = DynamicMatrix(2,2);

	/*
	test22.setMatrixElement(0,0,8);
	test22.setMatrixElement(0,1,2);

	test22.setMatrixElement(1,0,2);
	test22.setMatrixElement(1,1,5);
	*/
	test22.setMatrixElement(0,0,2);
	test22.setMatrixElement(0,1,1);

	test22.setMatrixElement(1,0,1);
	test22.setMatrixElement(1,1,2);
	DynamicSingleShiftQRIteration singleShiftQR = DynamicSingleShiftQRIteration(&test33);
	//singleShiftQR.rayleigh_Quotient_EX_QRIteration();
	//singleShiftQR.explicit_QRIteration(1.5);
	//singleShiftQR.implicit_QRIteration(1.5);
	//singleShiftQR.rayleigh_Quotient_IM_QRIteration();
	//singleShiftQR.generateHessenbergOpMatrix();

	DynamicMatrix Original33 = DynamicMatrix(3,3);
	DynamicMatrix QTMatrix = DynamicMatrix(3,3);
	DynamicMatrix QMatrix = DynamicMatrix(3,3);

	Original33.copyMatrixElementNoCheck(&test33);
	//cout << "DynamicSingelShiftQRIterationTest----Hessenberg before QR Step" << endl;
	//singleShiftQR.getOpHessenbergMatrix()->printMatrix();
	//Original33.printMatrix();

	//singleShiftQR.implicit_QRIteration_Step(6);
	singleShiftQR.rayleigh_Quotient_IM_QRIteration(10);
	QTMatrix.copyMatrixElementNoCheck(singleShiftQR.getQTMatrix_Total());
	QMatrix.copyMatrixElementNoCheck(singleShiftQR.getQMatrix_Total());

	DynamicMatrixMultiplier dmultip = DynamicMatrixMultiplier(&QTMatrix, &Original33);
	dmultip.multiplyCalc();
	Original33.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	dmultip.reload(&Original33, &QMatrix);
	dmultip.multiplyCalc();
	Original33.copyMatrixElementNoCheck(dmultip.getMultiplyResult());

	cout << "DynamicSingelShiftQRIterationTest----Hessenberg after One Step" << endl;
	singleShiftQR.getOpHessenbergMatrix()->printMatrix();

	cout << "DynamicSingelShiftQRIterationTest----QT * test33 * Q after One Step" << endl;
	Original33.printMatrix();

	//singleShiftQR.reload(&test44);
	//DynamicMatrix hessenberg44 = DynamicMatrix(4,4);
	//DynamicMatrix QTMatrix_44 = DynamicMatrix(4,4);
	//DynamicMatrix QMatrix_44 = DynamicMatrix(4,4);
	//hessenberg44.copyMatrixElementNoCheck(singleShiftQR.getOpHessenbergMatrix());
	//cout << "DynamicSingelShiftQRIterationTest----Hessenberg before QR Step" << endl;
	//singleShiftQR.getOpHessenbergMatrix()->printMatrix();

	//singleShiftQR.rayleigh_Quotient_IM_QRIteration(80);
	//cout << "DynamicSingelShiftQRIterationTest----Hessenberg After 10 QR Step" << endl;
	//singleShiftQR.getOpHessenbergMatrix()->printMatrix();

};


