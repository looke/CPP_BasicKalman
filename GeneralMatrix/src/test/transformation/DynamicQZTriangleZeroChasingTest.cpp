/*
 * DynamicHessenbergTriangleDeflationTest.cpp
 *
 *  Created on: 2017Äê5ÔÂ6ÈÕ
 *      Author: looke
 */

#include <test/transformation/DynamicQZTriangleZeroChasingTest.h>
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\dynamic\util\DynamicMatrixEigenValueSolver.h"
#include <iostream>
using namespace std;

DynamicQZTriangleZeroChasingTest::DynamicQZTriangleZeroChasingTest()
{};

void DynamicQZTriangleZeroChasingTest::test()
{
	DynamicMatrix inputMatrix_A = DynamicMatrix(4,4);
	inputMatrix_A.setMatrixElement(0,0,1);
	inputMatrix_A.setMatrixElement(0,1,1);
	inputMatrix_A.setMatrixElement(0,2,1);
	inputMatrix_A.setMatrixElement(0,3,1);

	inputMatrix_A.setMatrixElement(1,0,1);
	inputMatrix_A.setMatrixElement(1,1,1);
	inputMatrix_A.setMatrixElement(1,2,1);
	inputMatrix_A.setMatrixElement(1,3,1);

	inputMatrix_A.setMatrixElement(2,0,0);
	inputMatrix_A.setMatrixElement(2,1,1);
	inputMatrix_A.setMatrixElement(2,2,1);
	inputMatrix_A.setMatrixElement(2,3,1);

	inputMatrix_A.setMatrixElement(3,0,0);
	inputMatrix_A.setMatrixElement(3,1,0);
	inputMatrix_A.setMatrixElement(3,2,1);
	inputMatrix_A.setMatrixElement(3,3,1);
	inputMatrix_A.printMatrix();
	cout << "--------------" << endl;
	DynamicMatrix inputMatrix_B = DynamicMatrix(4,4);

	/*
	inputMatrix_B.setMatrixElement(0,0,0);
	inputMatrix_B.setMatrixElement(0,1,0);
	inputMatrix_B.setMatrixElement(0,2,2);
	inputMatrix_B.setMatrixElement(0,3,0);

	inputMatrix_B.setMatrixElement(1,0,0);
	inputMatrix_B.setMatrixElement(1,1,-1);
	inputMatrix_B.setMatrixElement(1,2,0);
	inputMatrix_B.setMatrixElement(1,3,0);

	inputMatrix_B.setMatrixElement(2,0,2);
	inputMatrix_B.setMatrixElement(2,1,0);
	inputMatrix_B.setMatrixElement(2,2,0);
	inputMatrix_B.setMatrixElement(2,3,0);

	inputMatrix_B.setMatrixElement(3,0,0);
	inputMatrix_B.setMatrixElement(3,1,0);
	inputMatrix_B.setMatrixElement(3,2,0);
	inputMatrix_B.setMatrixElement(3,3,0);
	inputMatrix_B.printMatrix();
	cout << "--------------" << endl;
	*/
	inputMatrix_B.setMatrixElement(0,0,1);
	inputMatrix_B.setMatrixElement(0,1,2);
	inputMatrix_B.setMatrixElement(0,2,3);
	inputMatrix_B.setMatrixElement(0,3,4);

	inputMatrix_B.setMatrixElement(1,0,0);
	inputMatrix_B.setMatrixElement(1,1,0);
	inputMatrix_B.setMatrixElement(1,2,6);
	inputMatrix_B.setMatrixElement(1,3,7);

	inputMatrix_B.setMatrixElement(2,0,0);
	inputMatrix_B.setMatrixElement(2,1,0);
	inputMatrix_B.setMatrixElement(2,2,8);
	inputMatrix_B.setMatrixElement(2,3,9);

	inputMatrix_B.setMatrixElement(3,0,0);
	inputMatrix_B.setMatrixElement(3,1,0);
	inputMatrix_B.setMatrixElement(3,2,0);
	inputMatrix_B.setMatrixElement(3,3,10);

	DynamicQZTriangleZeroChasing zeroChasing = DynamicQZTriangleZeroChasing(&inputMatrix_A, &inputMatrix_B);
	zeroChasing.deflate();

	cout << "After Chasing Matrix A " << endl;
	zeroChasing.getOpMatrix_A()->printMatrix();

	cout << "After Chasing Matrix B " << endl;
	zeroChasing.getOpMatrix_B()->printMatrix();

	DynamicMatrix QMatrix = DynamicMatrix(4,4);
	QMatrix.copyMatrixElementNoCheck(zeroChasing.getGivensMatrix_Q_Total());

	DynamicMatrix ZMatrix = DynamicMatrix(4,4);
	ZMatrix.copyMatrixElementNoCheck(zeroChasing.getGivensMatrix_Z_Total());

	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(&QMatrix,&inputMatrix_A);
	multip.multiplyCalc();
	inputMatrix_A.copyMatrixElementNoCheck(multip.getMultiplyResult());
	multip.reload(&inputMatrix_A,&ZMatrix);
	multip.multiplyCalc();
	inputMatrix_A.copyMatrixElementNoCheck(multip.getMultiplyResult());

	cout << "Q * Input Matrix A * Z" << endl;
	inputMatrix_A.printMatrix();

	multip.reload(&QMatrix,&inputMatrix_B);
	multip.multiplyCalc();
	inputMatrix_B.copyMatrixElementNoCheck(multip.getMultiplyResult());
	multip.reload(&inputMatrix_B,&ZMatrix);
	multip.multiplyCalc();
	inputMatrix_B.copyMatrixElementNoCheck(multip.getMultiplyResult());
	cout << "Q * Input Matrix B * Z" << endl;
	inputMatrix_B.printMatrix();


	/*
	cout << "OP A" << endl;
	deflater.getOpMatrix_A()->printMatrix();
	cout << "OP B" << endl;
	deflater.getOpMatrix_B()->printMatrix();

	cout << "Generate Sub:0" << endl;
	deflater.generateSubMatrix(0);

	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();

	cout << "Index of Zeros in Sub B" << endl;
	cout << deflater.getOpSubMatrix_B()->indexOfZeroOnDiagonal() << endl;

	deflater.generateGivensSubMatrixForB(2);

	deflater.updateSubOpMatrix_A_By_G();
	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();

	deflater.updateSubOpMatrix_B_By_G();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();

	deflater.generateGivensSubMatrixForA(2);

	deflater.updateSubOpMatrix_A_By_Z();
	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();

	deflater.updateSubOpMatrix_B_By_Z();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();

	cout << "Givens Matrix G Step" << endl;
	deflater.getGivensMatrix_G_Step()->printMatrix();

	deflater.upgradeGivensSubMatrix_G();
	cout << "Givens Matrix G Step" << endl;
	deflater.getGivensMatrix_G_Step()->printMatrix();

	cout << "Givens Matrix Z Step" << endl;
	deflater.getGivensMatrix_Z_Step()->printMatrix();
	deflater.upgradeGivensSubMatrix_Z();
	cout << "Givens Matrix Z Step" << endl;
	deflater.getGivensMatrix_Z_Step()->printMatrix();


	cout << "Givens Matrix G Iterate" << endl;
	deflater.getGivensMatrix_G_Iterate()->printMatrix();
	deflater.updateGivensMatrix_Iterate_G();
	cout << "Givens Matrix G Iterate" << endl;
	deflater.getGivensMatrix_G_Iterate()->printMatrix();

	cout << "Givens Matrix Z Iterate" << endl;
	deflater.getGivensMatrix_Z_Iterate()->printMatrix();
	deflater.updateGivensMatrix_Iterate_Z();
	cout << "Givens Matrix Z Iterate" << endl;
	deflater.getGivensMatrix_Z_Iterate()->printMatrix();


	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();
	deflater.generateGivensSubMatrixForB(3);

	deflater.updateSubOpMatrix_A_By_G();
	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();

	deflater.updateSubOpMatrix_B_By_G();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();

	deflater.generateGivensSubMatrixForA(3);

	deflater.updateSubOpMatrix_A_By_Z();
	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();

	deflater.updateSubOpMatrix_B_By_Z();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();

	cout << "Givens Matrix G Step" << endl;
	deflater.getGivensMatrix_G_Step()->printMatrix();

	deflater.upgradeGivensSubMatrix_G();
	cout << "Givens Matrix G Step" << endl;
	deflater.getGivensMatrix_G_Step()->printMatrix();

	cout << "Givens Matrix Z Step" << endl;
	deflater.getGivensMatrix_Z_Step()->printMatrix();
	deflater.upgradeGivensSubMatrix_Z();
	cout << "Givens Matrix Z Step" << endl;
	deflater.getGivensMatrix_Z_Step()->printMatrix();


	cout << "Givens Matrix G Iterate" << endl;
	deflater.getGivensMatrix_G_Iterate()->printMatrix();
	deflater.updateGivensMatrix_Iterate_G();
	cout << "Givens Matrix G Iterate" << endl;
	deflater.getGivensMatrix_G_Iterate()->printMatrix();

	cout << "Givens Matrix Z Iterate" << endl;
	deflater.getGivensMatrix_Z_Iterate()->printMatrix();
	deflater.updateGivensMatrix_Iterate_Z();
	cout << "Givens Matrix Z Iterate" << endl;
	deflater.getGivensMatrix_Z_Iterate()->printMatrix();

	deflater.generateGivensSubMatrixForA_last();

	deflater.updateSubOpMatrix_A_By_Z();
	cout << "SUB OP A" << endl;
	deflater.getOpSubMatrix_A()->printMatrix();

	deflater.updateSubOpMatrix_B_By_Z();
	cout << "SUB OP B" << endl;
	deflater.getOpSubMatrix_B()->printMatrix();

	cout << "Givens Matrix Z Step" << endl;
	deflater.getGivensMatrix_Z_Step()->printMatrix();
	deflater.upgradeGivensSubMatrix_Z();
	cout << "Givens Matrix Z Step" << endl;
	deflater.getGivensMatrix_Z_Step()->printMatrix();

	cout << "Givens Matrix Z Iterate" << endl;
	deflater.getGivensMatrix_Z_Iterate()->printMatrix();
	deflater.updateGivensMatrix_Iterate_Z();
	cout << "Givens Matrix Z Iterate" << endl;
	deflater.getGivensMatrix_Z_Iterate()->printMatrix();

	deflater.updateOpMatrix_A_By_G();
	deflater.updateOpMatrix_A_By_Z();
	deflater.updateOpMatrix_B_By_G();
	deflater.updateOpMatrix_B_By_Z();

	deflater.updateGivensMatrix_Total_G();
	deflater.updateGivensMatrix_Total_Z();

	deflater.getOpMatrix_A()->printMatrix();
	deflater.getOpMatrix_B()->printMatrix();


	cout << "Generate Sub:1" << endl;
	deflater.generateSubMatrix(1);

	//deflater.resizeSubMatrix(2);

	deflater.getGivensSubMatrix_G_Step()->printMatrix();
	deflater.getGivensSubMatrix_Z_Step()->printMatrix();

	deflater.getOpSubMatrix_A()->printMatrix();
	deflater.getOpSubMatrix_B()->printMatrix();

	cout << "Index of Zeros in Sub B" << endl;
	cout << deflater.getOpSubMatrix_B()->indexOfZeroOnDiagonal() << endl;
	*/
	/*
	DynamicMatrix deflated_A = DynamicMatrix(4,4);
	DynamicMatrix deflated_B = DynamicMatrix(4,4);
	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(deflater.getGivensMatrix_G_Iterate(),&inputMatrix_A);

	multip.multiplyCalc();

	deflated_A.copyMatrixElementNoCheck(multip.getMultiplyResult());

	multip.reload(&deflated_A, deflater.getGivensMatrix_Z_Iterate());
	multip.multiplyCalc();

	deflated_A.copyMatrixElementNoCheck(multip.getMultiplyResult());

	cout << "G A Z Iterate" << endl;
	deflated_A.printMatrix();

	multip.reload(deflater.getGivensMatrix_G_Iterate(), &inputMatrix_B);
	multip.multiplyCalc();
	deflated_B.copyMatrixElementNoCheck(multip.getMultiplyResult());
	multip.reload(&deflated_B, deflater.getGivensMatrix_Z_Iterate());
	multip.multiplyCalc();
	deflated_B.copyMatrixElementNoCheck(multip.getMultiplyResult());
	cout << "G B Z Iterate" << endl;
	deflated_B.printMatrix();
	*/
};


