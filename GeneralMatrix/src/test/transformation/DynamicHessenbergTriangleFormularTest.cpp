/*
 * DynamicHessenbergTriangleFormularTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ28ÈÕ
 *      Author: looke
 */

#include "DynamicHessenbergTriangleFormularTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\transformation\dynamic\DynamicQRDecomposition.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixTransposer.h"

#include "iostream"
using namespace std;

DynamicHessenbergTriangleFormularTest::DynamicHessenbergTriangleFormularTest()
{};

void DynamicHessenbergTriangleFormularTest::test()
{

	DynamicMatrix AMatrix = DynamicMatrix(3,3);

	AMatrix.setMatrixElement(0,0,10);
	AMatrix.setMatrixElement(0,1,1);
	AMatrix.setMatrixElement(0,2,2);

	AMatrix.setMatrixElement(1,0,1);
	AMatrix.setMatrixElement(1,1,2);
	AMatrix.setMatrixElement(1,2,-1);

	AMatrix.setMatrixElement(2,0,1);
	AMatrix.setMatrixElement(2,1,1);
	AMatrix.setMatrixElement(2,2,2);

	DynamicMatrix AMatrix_44 = DynamicMatrix(4,4);
	AMatrix_44.setMatrixElement(0,0,10);
	AMatrix_44.setMatrixElement(0,1,1);
	AMatrix_44.setMatrixElement(0,2,2);
	AMatrix_44.setMatrixElement(0,3,2);

	AMatrix_44.setMatrixElement(1,0,1);
	AMatrix_44.setMatrixElement(1,1,2);
	AMatrix_44.setMatrixElement(1,2,-1);
	AMatrix_44.setMatrixElement(1,3,-1);

	AMatrix_44.setMatrixElement(2,0,1);
	AMatrix_44.setMatrixElement(2,1,1);
	AMatrix_44.setMatrixElement(2,2,2);
	AMatrix_44.setMatrixElement(2,3,2);

	AMatrix_44.setMatrixElement(3,0,1);
	AMatrix_44.setMatrixElement(3,1,1);
	AMatrix_44.setMatrixElement(3,2,2);
	AMatrix_44.setMatrixElement(3,3,2);

	DynamicMatrix AMatrix_Hessen44 = DynamicMatrix(4,4);
	AMatrix_Hessen44.setMatrixElement(0,0,10);
	AMatrix_Hessen44.setMatrixElement(0,1,1);
	AMatrix_Hessen44.setMatrixElement(0,2,2);
	AMatrix_Hessen44.setMatrixElement(0,3,2);

	AMatrix_Hessen44.setMatrixElement(1,0,1);
	AMatrix_Hessen44.setMatrixElement(1,1,2);
	AMatrix_Hessen44.setMatrixElement(1,2,-1);
	AMatrix_Hessen44.setMatrixElement(1,3,-1);

	AMatrix_Hessen44.setMatrixElement(2,0,0);
	AMatrix_Hessen44.setMatrixElement(2,1,1);
	AMatrix_Hessen44.setMatrixElement(2,2,2);
	AMatrix_Hessen44.setMatrixElement(2,3,2);

	AMatrix_Hessen44.setMatrixElement(3,0,0);
	AMatrix_Hessen44.setMatrixElement(3,1,0);
	AMatrix_Hessen44.setMatrixElement(3,2,2);
	AMatrix_Hessen44.setMatrixElement(3,3,2);

	DynamicMatrix BMatrix = DynamicMatrix(3,3);
	DynamicMatrix BMatrix_44 = DynamicMatrix(4,4);

	DynamicMatrix BMatrix_Triangle44 = DynamicMatrix(4,4);
	BMatrix_Triangle44.setMatrixElement(0,0,10);
	BMatrix_Triangle44.setMatrixElement(0,1,1);
	BMatrix_Triangle44.setMatrixElement(0,2,2);
	BMatrix_Triangle44.setMatrixElement(0,3,2);

	BMatrix_Triangle44.setMatrixElement(1,0,0);
	BMatrix_Triangle44.setMatrixElement(1,1,2);
	BMatrix_Triangle44.setMatrixElement(1,2,-1);
	BMatrix_Triangle44.setMatrixElement(1,3,-1);

	BMatrix_Triangle44.setMatrixElement(2,0,0);
	BMatrix_Triangle44.setMatrixElement(2,1,0);
	BMatrix_Triangle44.setMatrixElement(2,2,2);
	BMatrix_Triangle44.setMatrixElement(2,3,2);

	BMatrix_Triangle44.setMatrixElement(3,0,0);
	BMatrix_Triangle44.setMatrixElement(3,1,0);
	BMatrix_Triangle44.setMatrixElement(3,2,0);
	BMatrix_Triangle44.setMatrixElement(3,3,2);

	//cout << "Input Matrix A:" << endl;
	//AMatrix_Hessen44.printMatrix();

	//cout << "Input Matrix B:" << endl;
	//BMatrix_Triangle44.printMatrix();


	DynamicHessenbergTriangleFormular hessenbergTriangle = DynamicHessenbergTriangleFormular(&AMatrix_44, &BMatrix_44);
	hessenbergTriangle.formularABMatrix();

	DynamicMatrix QMatrix_44 = DynamicMatrix(4,4);
	QMatrix_44.copyMatrixElementNoCheck(hessenbergTriangle.getMatrixQ_Total());
	cout << "Q Total" << endl;
	QMatrix_44.printMatrix();

	DynamicMatrix ZMatrix_44 = DynamicMatrix(4,4);
	ZMatrix_44.copyMatrixElementNoCheck(hessenbergTriangle.getMatrixZ_Total());
	cout << "Z Total" << endl;
	ZMatrix_44.printMatrix();

	cout << "A44" << endl;
	AMatrix_44.printMatrix();


	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(&QMatrix_44,&AMatrix_44);
	multip.multiplyCalc();
	AMatrix_44.copyMatrixElementNoCheck(multip.getMultiplyResult());
	multip.reload(&AMatrix_44,&ZMatrix_44);
	multip.multiplyCalc();
	AMatrix_44.copyMatrixElementNoCheck(multip.getMultiplyResult());
	cout << "Q*A44*Z" << endl;
	AMatrix_44.printMatrix();

	cout << "B44" << endl;
	BMatrix_44.printMatrix();

	multip.reload(&QMatrix_44,&BMatrix_44);
	multip.multiplyCalc();
	BMatrix_44.copyMatrixElementNoCheck(multip.getMultiplyResult());
	multip.reload(&BMatrix_44,&ZMatrix_44);
	multip.multiplyCalc();
	BMatrix_44.copyMatrixElementNoCheck(multip.getMultiplyResult());
	cout << "Q*B44*Z" << endl;
	BMatrix_44.printMatrix();
	/*
	DynamicQRDecomposition qrDecomp = DynamicQRDecomposition(&BMatrix);
	qrDecomp.calcQRMatrix();



	BasicMatrix* p_rMatrix = qrDecomp.getRMatrix();
	BasicMatrix* p_qtMatrix = qrDecomp.getQTMatrix();
	BasicMatrix* p_qMatrix = qrDecomp.getQMatrix();
	cout << "Input Matrix B After QR decomp:" << endl;
	cout << "QT Matrix:" << endl;
	p_qtMatrix->printMatrix();
	cout << "Q Matrix:" << endl;
	p_qMatrix->printMatrix();
	cout << "R Matrix:" << endl;
	p_rMatrix->printMatrix();
	BMatrix.copyMatrixElementNoCheck(p_rMatrix);

	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(p_qMatrix,p_rMatrix);
	multip.multiplyCalc();
	cout << "Q*R" << endl;
	multip.getMultiplyResult()->printMatrix();

	multip.reload(p_qtMatrix,&AMatrix);
	multip.multiplyCalc();
	AMatrix.copyMatrixElementNoCheck(multip.getMultiplyResult());
	cout << "QT*A" << endl;
	AMatrix.regularZeroElement();
	AMatrix.printMatrix();

	cout << "Input Matrix B for HessenBergTriangle:" << endl;
	BMatrix.regularZeroElement();
	BMatrix.printMatrix();

	DynamicHessenbergTriangleFormular hessenbergTriangle = DynamicHessenbergTriangleFormular(&AMatrix, &BMatrix);
	hessenbergTriangle.formularColumnVector(0);

	cout << "After HessenBergTriangle--- A:" << endl;
	hessenbergTriangle.getMatrixA()->printMatrix();
	cout << "After HessenBergTriangle--- B:" << endl;
	hessenbergTriangle.getMatrixB()->printMatrix();
	cout << "After HessenBergTriangle--- Q:" << endl;
	hessenbergTriangle.getMatrixQT()->printMatrix();
	cout << "After HessenBergTriangle--- Z:" << endl;
	hessenbergTriangle.getMatrixZ()->printMatrix();

	multip.reload(hessenbergTriangle.getMatrixQT(),p_qtMatrix);
	multip.multiplyCalc();
	cout << "After HessenBergTriangle--- QT" << endl;
	multip.getMultiplyResult()->printMatrix();




	cout << "Google HessenBergTriangle Example Test" << endl;

	DynamicMatrix googleAMatrix = DynamicMatrix(3,3);

	googleAMatrix.setMatrixElement(0,0,10);
	googleAMatrix.setMatrixElement(0,1,1);
	googleAMatrix.setMatrixElement(0,2,2);

	googleAMatrix.setMatrixElement(1,0,1);
	googleAMatrix.setMatrixElement(1,1,2);
	googleAMatrix.setMatrixElement(1,2,-1);

	googleAMatrix.setMatrixElement(2,0,1);
	googleAMatrix.setMatrixElement(2,1,1);
	googleAMatrix.setMatrixElement(2,2,2);

	cout << "Google HessenBergTriangle Example Test: A Matrix" << endl;
	googleAMatrix.printMatrix();

	DynamicMatrix googleQMatrix = DynamicMatrix(3,3);

	googleQMatrix.setMatrixElement(0,0,-0.1231);
	googleQMatrix.setMatrixElement(0,1,-0.9917);
	googleQMatrix.setMatrixElement(0,2,0.0378);

	googleQMatrix.setMatrixElement(1,0,-0.4924);
	googleQMatrix.setMatrixElement(1,1,0.0279);
	googleQMatrix.setMatrixElement(1,2,-0.8699);

	googleQMatrix.setMatrixElement(2,0,-0.8616);
	googleQMatrix.setMatrixElement(2,1,0.1257);
	googleQMatrix.setMatrixElement(2,2,0.4917);

	cout << "Google HessenBergTriangle Example Test: Q Matrix" << endl;
	googleQMatrix.printMatrix();


	DynamicMatrixTransposer dtr = DynamicMatrixTransposer(&googleQMatrix);
	dtr.transposeMatrix();

	DynamicMatrix googleQTMatrix = DynamicMatrix(3,3);
	googleQTMatrix.copyMatrixElementNoCheck(dtr.getTransposeMatrix());

	cout << "Google HessenBergTriangle Example Test: QT Matrix" << endl;
	googleQTMatrix.printMatrix();


	DynamicMatrix googleZMatrix = DynamicMatrix(3,3);

	googleZMatrix.setMatrixElement(0,0,1);
	googleZMatrix.setMatrixElement(0,1,0);
	googleZMatrix.setMatrixElement(0,2,0);

	googleZMatrix.setMatrixElement(1,0,0);
	googleZMatrix.setMatrixElement(1,1,-0.8944);
	googleZMatrix.setMatrixElement(1,2,-0.4472);

	googleZMatrix.setMatrixElement(2,0,0);
	googleZMatrix.setMatrixElement(2,1,0.4472);
	googleZMatrix.setMatrixElement(2,2,-0.8944);

	cout << "Google HessenBergTriangle Example Test: Z Matrix" << endl;
	googleZMatrix.printMatrix();


	//DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(&googleQTMatrix,&googleAMatrix);
	multip.reload(&googleQTMatrix,&googleAMatrix);
	multip.multiplyCalc();

	DynamicMatrix googleResultMatrix = DynamicMatrix(3,3);
	googleResultMatrix.copyMatrixElementNoCheck(multip.getMultiplyResult());

	cout << "Google HessenBergTriangle Example Test: QT * A Matrix" << endl;
	googleResultMatrix.printMatrix();



	multip.reload(&googleResultMatrix,&googleZMatrix);
	multip.multiplyCalc();
	googleResultMatrix.copyMatrixElementNoCheck(multip.getMultiplyResult());

	cout << "Google HessenBergTriangle Example Test: QT * A * Z Matrix" << endl;
	googleResultMatrix.printMatrix();
	*/
};


