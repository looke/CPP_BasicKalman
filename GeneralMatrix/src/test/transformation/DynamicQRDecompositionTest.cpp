/*
 * DynamicQRDecompositionTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ27ÈÕ
 *      Author: looke
 */

#include "DynamicQRDecompositionTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "iostream"
using namespace std;

DynamicQRDecompositionTest::DynamicQRDecompositionTest()
{};


void DynamicQRDecompositionTest::test()
{
	DynamicMatrix test33 = DynamicMatrix(3,3);
	/*
	test33.setMatrixElement(0,0,0);
	test33.setMatrixElement(0,1,3);
	test33.setMatrixElement(0,2,1);

	test33.setMatrixElement(1,0,0);
	test33.setMatrixElement(1,1,4);
	test33.setMatrixElement(1,2,-2);

	test33.setMatrixElement(2,0,2);
	test33.setMatrixElement(2,1,1);
	test33.setMatrixElement(2,2,1);
	*/
	test33.setMatrixElement(0,0,1);
	test33.setMatrixElement(0,1,1);
	test33.setMatrixElement(0,2,1);

	test33.setMatrixElement(1,0,2);
	test33.setMatrixElement(1,1,-1);
	test33.setMatrixElement(1,2,-1);

	test33.setMatrixElement(2,0,2);
	test33.setMatrixElement(2,1,-4);
	test33.setMatrixElement(2,2,5);

	/*
	test33.setMatrixElement(0,0,0);
	test33.setMatrixElement(0,1,0);
	test33.setMatrixElement(0,2,2);

	test33.setMatrixElement(1,0,0);
	test33.setMatrixElement(1,1,-1);
	test33.setMatrixElement(1,2,0);

	test33.setMatrixElement(2,0,2);
	test33.setMatrixElement(2,1,0);
	test33.setMatrixElement(2,2,0);
	*/
	DynamicMatrix test44 = DynamicMatrix(4,4);
	test44.setMatrixElement(0,0,0);
	test44.setMatrixElement(0,1,0);
	test44.setMatrixElement(0,2,2);
	test44.setMatrixElement(0,3,0);

	test44.setMatrixElement(1,0,0);
	test44.setMatrixElement(1,1,-1);
	test44.setMatrixElement(1,2,0);
	test44.setMatrixElement(1,3,0);

	test44.setMatrixElement(2,0,2);
	test44.setMatrixElement(2,1,0);
	test44.setMatrixElement(2,2,0);
	test44.setMatrixElement(2,3,0);

	test44.setMatrixElement(3,0,0);
	test44.setMatrixElement(3,1,0);
	test44.setMatrixElement(3,2,0);
	test44.setMatrixElement(3,3,0);

	DynamicMatrix test44_upTriangle = DynamicMatrix(4,4);
	test44_upTriangle.setMatrixElement(0,0,1);
	test44_upTriangle.setMatrixElement(0,1,2);
	test44_upTriangle.setMatrixElement(0,2,3);
	test44_upTriangle.setMatrixElement(0,3,4);

	test44_upTriangle.setMatrixElement(1,0,0);
	test44_upTriangle.setMatrixElement(1,1,5);
	test44_upTriangle.setMatrixElement(1,2,6);
	test44_upTriangle.setMatrixElement(1,3,7);

	test44_upTriangle.setMatrixElement(2,0,0);
	test44_upTriangle.setMatrixElement(2,1,0);
	test44_upTriangle.setMatrixElement(2,2,8);
	test44_upTriangle.setMatrixElement(2,3,9);

	test44_upTriangle.setMatrixElement(3,0,0);
	test44_upTriangle.setMatrixElement(3,1,0);
	test44_upTriangle.setMatrixElement(3,2,0);
	test44_upTriangle.setMatrixElement(3,3,10);


	cout << "Test Matrix 3*3: OP Matrix" << endl;
	test33.printMatrix();

	cout << "Test Matrix 4*4: OP Matrix" << endl;
	test44.printMatrix();

	BasicMatrix* p_houseHolderMatrix;
	BasicMatrix* p_OpMatrix;
	BasicMatrix* p_QMatrix;
	BasicMatrix* p_QTMatrix;

	DynamicQRDecomposition qRDecomp = DynamicQRDecomposition(&test44_upTriangle);

	p_houseHolderMatrix = qRDecomp.getHouseholderMatrix();
	p_OpMatrix = qRDecomp.getRMatrix();
	p_QMatrix = qRDecomp.getQMatrix();
	p_QTMatrix  = qRDecomp.getQTMatrix();

	cout << "Before Start QR Decomp OPMatrix:" << endl;
	p_OpMatrix->printMatrix();
	cout << "Before Start QR Decomp HouseHolderMatrix:" << endl;
	p_houseHolderMatrix->printMatrix();
	cout << "Before Start QR Decomp QMatrix:" << endl;
	p_QMatrix->printMatrix();
	cout << "Before Start QR Decomp QTMatrix:" << endl;
	p_QTMatrix->printMatrix();

	qRDecomp.calcQRMatrix();

	/*
	qRDecomp.generateHouseholderMatrix(0);
	p_houseHolderMatrix = qRDecomp.getHouseholderMatrix();
	cout << "Test Matrix 3*3: HouseHolder Matrix For Column 0" << endl;
	p_houseHolderMatrix->printMatrix();
	qRDecomp.updateMatrix();

	cout << "QR Decomp IT:1 OPMatrix:" << endl;
	p_OpMatrix->printMatrix();
	cout << "QR Decomp IT:1 HouseHolderMatrix:" << endl;
	p_houseHolderMatrix->printMatrix();
	cout << "QR Decomp IT:1 Decomp QMatrix:" << endl;
	p_QMatrix->printMatrix();
	cout << "QR Decomp IT:1 Decomp QTMatrix:" << endl;
	p_QTMatrix->printMatrix();



	DynamicMatrix test33_it1 = DynamicMatrix(3,3);
	test33_it1.setMatrixElement(0,0,2);
	test33_it1.setMatrixElement(0,1,1);
	test33_it1.setMatrixElement(0,2,2);

	test33_it1.setMatrixElement(1,0,0);
	test33_it1.setMatrixElement(1,1,4);
	test33_it1.setMatrixElement(1,2,-2);

	test33_it1.setMatrixElement(2,0,0);
	test33_it1.setMatrixElement(2,1,3);
	test33_it1.setMatrixElement(2,2,1);
	qRDecomp.reload(&test33_it1);

	qRDecomp.generateHouseholderMatrix(1);
	p_houseHolderMatrix = qRDecomp.getHouseholderMatrix();
	cout << "Test Matrix 3*3: HouseHolder Matrix For Column 2" << endl;
	p_houseHolderMatrix->printMatrix();
	qRDecomp.updateMatrix();
	cout << "QR Decomp IT:2 OPMatrix:" << endl;
	p_OpMatrix->printMatrix();
	cout << "QR Decomp IT:2 HouseHolderMatrix:" << endl;
	p_houseHolderMatrix->printMatrix();
	cout << "QR Decomp IT:2 Decomp QMatrix:" << endl;
	p_QMatrix->printMatrix();
	cout << "QR Decomp IT:2 Decomp QTMatrix:" << endl;
	p_QTMatrix->printMatrix();

*/
	cout << "After QR Decomp OPMatrix:" << endl;
	p_OpMatrix->printMatrix();
	cout << "After QR Decomp HouseHolderMatrix:" << endl;
	p_houseHolderMatrix->printMatrix();
	cout << "After QR Decomp Decomp QMatrix:" << endl;
	p_QMatrix->printMatrix();
	cout << "After QR Decomp Decomp QTMatrix:" << endl;
	p_QTMatrix->printMatrix();

	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(p_OpMatrix,p_QTMatrix);
	multip.multiplyCalc();
	cout << "QRQT multi:" << endl;
	multip.getMultiplyResult()->printMatrix();

	multip.reload(p_QMatrix,p_OpMatrix);
	multip.multiplyCalc();
	cout << "QR multi:" << endl;
	multip.getMultiplyResult()->printMatrix();

	//DynamicMatrix test44_it1 = DynamicMatrix(4,4);
	//test44_it1.copyMatrixElementNoCheck(multip.getMultiplyResult());

	//multip.reload(&test44_it1,p_QTMatrix);
	//multip.multiplyCalc();
	//cout << "QRQT multi:" << endl;
	//multip.getMultiplyResult()->printMatrix();
};


