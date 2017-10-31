/*
 * DynamicNormalEigenSolverForRealTest.cpp
 *
 *  Created on: 2017Äê5ÔÂ23ÈÕ
 *      Author: looke
 */


#include "DynamicNormalEigenSolverForRealTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include <time.h>
#include "iostream"
using namespace std;

DynamicNormalEigenSolverForRealTest::DynamicNormalEigenSolverForRealTest()
{};

void DynamicNormalEigenSolverForRealTest::test()
{
	cout << "DynamicNormalEigenSolverForRealTest" << endl;

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
	test44.setMatrixElement(3,2,12);
	test44.setMatrixElement(3,3,13);

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
	clock_t start,ends;
	DynamicMatrix test66QT = DynamicMatrix(6,6);
	DynamicMatrix test66Q = DynamicMatrix(6,6);
	//bool hasDeflationStart_NEW;
	//bool hasFinishedCalc;
	DynamicNormalEigenSolverForReal dNormalEigenSolver4R = DynamicNormalEigenSolverForReal(&test44);
	//dNormalEigenSolver4R.generateHessenbergOpMatrix();

	start=clock();
	dNormalEigenSolver4R.calcEigenValue();
	ends=clock();

	cout<<"DynamicNormalEigenSolverForRealTest----calcEigenValue eclipse:" << ends-start << endl;
	/*
	test66QT.copyMatrixElementNoCheck(dNormalEigenSolver4R.getQTMatrix_Total());
	test66Q.copyMatrixElementNoCheck(dNormalEigenSolver4R.getQMatrix_Total());

	DynamicMatrixMultiplier dmultip = DynamicMatrixMultiplier(&test66QT, &test66);
	dmultip.multiplyCalc();
	test66.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	dmultip.reload(&test66, &test66Q);
	dmultip.multiplyCalc();
	test66.copyMatrixElementNoCheck(dmultip.getMultiplyResult());

	cout << "DynamicNormalEigenSolverForRealTest----QT*test66*Q" << endl;
	test66.printMatrix();

	cout << "DynamicNormalEigenSolverForRealTest----QT*test66*Q ----- Regular" << endl;
	test66.regularZeroElement();
	test66.printMatrix();

	cout << "DynamicNormalEigenSolverForRealTest:---1----init Hessenberg" << endl;
	dNormalEigenSolver4R.getOpHessenbergMatrix()->printMatrix();
	cout << "DynamicNormalEigenSolverForRealTest:---1--END--init Hessenberg" << endl;

	cout << "DynamicNormalEigenSolverForRealTest:---2----initEigenCalcMatrix" << endl;
	dNormalEigenSolver4R.initEigenCalcMatrix();
	cout << "DynamicNormalEigenSolverForRealTest:---2----OpHessenbergMatrix_deflated" << endl;
	dNormalEigenSolver4R.getOpHessenbergMatrix_deflated()->printMatrix();
	cout << "DynamicNormalEigenSolverForRealTest:---2----QTMatrix_Deflated_Iteration" << endl;
	dNormalEigenSolver4R.getQTMatrix_Deflated_Iteration()->printMatrix();
	cout << "DynamicNormalEigenSolverForRealTest:---2----QMatrix_Deflated_Iteration" << endl;
	dNormalEigenSolver4R.getQMatrix_Deflated_Iteration()->printMatrix();
	cout << "DynamicNormalEigenSolverForRealTest:---2--END--initEigenCalcMatrix" << endl;

	cout << "DynamicNormalEigenSolverForRealTest:---3----findNewDeflationPoint" << endl;
	hasDeflationStart_NEW = dNormalEigenSolver4R.findNewDeflationPoint();
	cout << "DynamicNormalEigenSolverForRealTest:---3----has new DeflationStart:" << hasDeflationStart_NEW << endl;
	cout << "DynamicNormalEigenSolverForRealTest:---3--END--findNewDeflationPoint" << endl;

	cout << "DynamicNormalEigenSolverForRealTest:---4----hasFinishedIteration" << endl;
	hasFinishedCalc = dNormalEigenSolver4R.hasFinishedIteration();
	cout << "DynamicNormalEigenSolverForRealTest:---4----hasFinishedCalc:" << hasFinishedCalc << endl;
	cout << "DynamicNormalEigenSolverForRealTest:---4--END--hasFinishedIteration" << endl;
	*/
};

