/*
 * DynamicHouseholderTransformationTester.cpp
 *
 *  Created on: 2017Äê4ÔÂ24ÈÕ
 *      Author: looke
 */

#include "DynamicHouseholderTransformationTester.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "..\matrix\dynamic\util\DynamicMatrixMultiplier.h"
#include "iostream"
using namespace std;

DynamicHouseholderTransformationTester::DynamicHouseholderTransformationTester()
{

};

void DynamicHouseholderTransformationTester::test()
{
	DynamicVector testVector = DynamicVector(3);
	testVector.setElement(0,12.0);
	testVector.setElement(1,6.0);
	testVector.setElement(2,-4.0);

	cout << "Test Vector" << endl;
	testVector.printVector();

	DynamicMatrix testMatrix = DynamicMatrix(3,3);

	testMatrix.setMatrixElement(0,0,12);
	testMatrix.setMatrixElement(0,1,1);
	testMatrix.setMatrixElement(0,2,1);

	testMatrix.setMatrixElement(1,0,6);
	testMatrix.setMatrixElement(1,1,1);
	testMatrix.setMatrixElement(1,2,1);

	testMatrix.setMatrixElement(2,0,-4);
	testMatrix.setMatrixElement(2,1,1);
	testMatrix.setMatrixElement(2,2,1);

	BasicMatrix* p_HouseholderMatrix_E1;
	BasicMatrix* p_HouseholderMatrix_En;

	DynamicHouseholderTransformation houseHolder = DynamicHouseholderTransformation(&testVector);
	p_HouseholderMatrix_E1 = houseHolder.getHouseholderMatrixToE1(true);
	cout << "Test Vector to E1" << endl;
	p_HouseholderMatrix_E1->printMatrix();

	DynamicMatrixMultiplier dmultip = DynamicMatrixMultiplier(p_HouseholderMatrix_E1, &testMatrix);
	dmultip.multiplyCalc();
	cout << "p_HouseholderMatrix_E1 * Test Matrix_33" << endl;
	dmultip.getMultiplyResult()->printMatrix();

	DynamicMatrix testMatrix_44 = DynamicMatrix(4,4);

	testMatrix_44.setMatrixElement(0,0,1);
	testMatrix_44.setMatrixElement(0,1,1);
	testMatrix_44.setMatrixElement(0,2,1);
	testMatrix_44.setMatrixElement(0,3,1);

	testMatrix_44.setMatrixElement(1,0,12);
	testMatrix_44.setMatrixElement(1,1,1);
	testMatrix_44.setMatrixElement(1,2,1);
	testMatrix_44.setMatrixElement(1,3,1);

	testMatrix_44.setMatrixElement(2,0,6);
	testMatrix_44.setMatrixElement(2,1,1);
	testMatrix_44.setMatrixElement(2,2,1);
	testMatrix_44.setMatrixElement(2,3,1);

	testMatrix_44.setMatrixElement(3,0,-4);
	testMatrix_44.setMatrixElement(3,1,1);
	testMatrix_44.setMatrixElement(3,2,1);
	testMatrix_44.setMatrixElement(3,3,1);

	DynamicMatrix testMatrix_44_toE1 = DynamicMatrix(4,4);
	testMatrix_44_toE1.resetMatrixToI();

	for(int i=0; i<p_HouseholderMatrix_E1->rowNum;i++)
	{
		for(int j=0; j<p_HouseholderMatrix_E1->columnNum;j++)
		{
			testMatrix_44_toE1.setMatrixElement(i+1, j+1, p_HouseholderMatrix_E1->getMatrixElement(i,j));
		}
	}
	cout << "Test Matrix_44 " << endl;
	testMatrix_44.printMatrix();
	cout << "Test Matrix_44_toE1 " << endl;
	testMatrix_44_toE1.printMatrix();

	dmultip.reload(&testMatrix_44_toE1, &testMatrix_44);
	dmultip.multiplyCalc();
	cout << "Matrix_44_toE1 * Test Matrix_44" << endl;
	dmultip.getMultiplyResult()->printMatrix();

	houseHolder.reload(&testVector);
	p_HouseholderMatrix_En = houseHolder.getHouseholderMatrixToEn(true);
	cout << "Test Vector to En" << endl;
	p_HouseholderMatrix_En->printMatrix();


	cout << "Test Matrix 1" << endl;
	testMatrix.printMatrix();

	dmultip.reload(p_HouseholderMatrix_En, &testMatrix);
	dmultip.multiplyCalc();
	cout << "Householder En * Test Matrix" << endl;
	dmultip.getMultiplyResult()->printMatrix();

	DynamicMatrix testMatrix_2 = DynamicMatrix(3,3);

	testMatrix_2.setMatrixElement(0,0,12);
	testMatrix_2.setMatrixElement(0,1,6);
	testMatrix_2.setMatrixElement(0,2,-4);

	testMatrix_2.setMatrixElement(1,0,1);
	testMatrix_2.setMatrixElement(1,1,1);
	testMatrix_2.setMatrixElement(1,2,1);

	testMatrix_2.setMatrixElement(2,0,1);
	testMatrix_2.setMatrixElement(2,1,1);
	testMatrix_2.setMatrixElement(2,2,1);

	cout << "Test Matrix_2 for row" << endl;
	testMatrix_2.printMatrix();
	dmultip.reload(&testMatrix_2,p_HouseholderMatrix_En);
	dmultip.multiplyCalc();
	cout << "Test Matrix_2 * Householder_En" << endl;
	dmultip.getMultiplyResult()->printMatrix();

	DynamicMatrix testMatrix_2_44 = DynamicMatrix(4,4);

	testMatrix_2_44.setMatrixElement(0,0,1);
	testMatrix_2_44.setMatrixElement(0,1,1);
	testMatrix_2_44.setMatrixElement(0,2,1);
	testMatrix_2_44.setMatrixElement(0,3,1);

	testMatrix_2_44.setMatrixElement(1,0,1);
	testMatrix_2_44.setMatrixElement(1,1,1);
	testMatrix_2_44.setMatrixElement(1,2,1);
	testMatrix_2_44.setMatrixElement(1,3,1);

	testMatrix_2_44.setMatrixElement(2,0,1);
	testMatrix_2_44.setMatrixElement(2,1,12);
	testMatrix_2_44.setMatrixElement(2,2,6);
	testMatrix_2_44.setMatrixElement(2,3,-4);

	testMatrix_2_44.setMatrixElement(3,0,1);
	testMatrix_2_44.setMatrixElement(3,1,1);
	testMatrix_2_44.setMatrixElement(3,2,1);
	testMatrix_2_44.setMatrixElement(3,3,1);

	DynamicMatrix testMatrix_2_44_toEn = DynamicMatrix(4,4);
	testMatrix_2_44_toEn.resetMatrixToI();
	for(int i=0; i<p_HouseholderMatrix_En->rowNum;i++)
	{
		for(int j=0; j<p_HouseholderMatrix_En->columnNum;j++)
		{
			testMatrix_2_44_toEn.setMatrixElement(i+1, j+1, p_HouseholderMatrix_En->getMatrixElement(i,j));
		}
	}
	cout << "Test testMatrix_2_44 " << endl;
	testMatrix_2_44.printMatrix();
	cout << "Test testMatrix_2_44_toEn " << endl;
	testMatrix_2_44_toEn.printMatrix();

	dmultip.reload(&testMatrix_2_44,&testMatrix_2_44_toEn);
	dmultip.multiplyCalc();
	cout << "Test testMatrix_2_44 * testMatrix_2_44_toEn" << endl;
	dmultip.getMultiplyResult()->printMatrix();

	DynamicVector testVector_22 = DynamicVector(2);
	testVector_22.setElement(0,12.0);
	testVector_22.setElement(1,6.0);
	cout << "Test testVector_22" << endl;
	testVector_22.printVector();
	houseHolder.reload(&testVector_22);

	DynamicMatrix testMatrix_22 = DynamicMatrix(2,2);

	testMatrix_22.setMatrixElement(0,0,12);
	testMatrix_22.setMatrixElement(0,1,1);

	testMatrix_22.setMatrixElement(1,0,6);
	testMatrix_22.setMatrixElement(1,1,1);
	cout << "Test testMatrix_22" << endl;
	testMatrix_22.printMatrix();

	p_HouseholderMatrix_E1 = houseHolder.getHouseholderMatrixToE1(true);
	cout << "Test Vector to E1" << endl;
	p_HouseholderMatrix_E1->printMatrix();

	dmultip.reload(p_HouseholderMatrix_E1, &testMatrix_22);
	dmultip.multiplyCalc();
	cout << "p_HouseholderMatrix_E1 * Test Matrix_22" << endl;
	dmultip.getMultiplyResult()->printMatrix();


	cout << "Householder Trans Multip test" << endl;

	testVector.setElement(0,7.0);
	testVector.setElement(1,6.0);
	testVector.setElement(2,-4.0);

	testVector_22.setElement(0,5.0);
	testVector_22.setElement(1,3.0);

	houseHolder.reload(&testVector);


	DynamicMatrix householderTrans_33 = DynamicMatrix(3,3);
	householderTrans_33.copyMatrixElementNoCheck(houseHolder.getHouseholderMatrixToEn(true));
	cout << "Householder Trans33" << endl;
	householderTrans_33.printMatrix();

	houseHolder.reload(&testVector_22);
	DynamicMatrix householderTrans_22 = DynamicMatrix(2,2);
	householderTrans_22.copyMatrixElementNoCheck(houseHolder.getHouseholderMatrixToEn(true));
	cout << "Householder Trans22" << endl;
	householderTrans_22.printMatrix();

	DynamicMatrix householderTrans_33_from22 = DynamicMatrix(3,3);
	householderTrans_33_from22.resetMatrixToI();

	for(int i=0; i<householderTrans_22.rowNum;i++)
	{
		for(int j=0; j<householderTrans_22.columnNum;j++)
		{
			householderTrans_33_from22.setMatrixElement(i, j, householderTrans_22.getMatrixElement(i,j));
		}
	}
	cout << "Householder Trans33_from22" << endl;
	householderTrans_33_from22.printMatrix();


	testMatrix.setMatrixElement(0,0,1);
	testMatrix.setMatrixElement(0,1,1);
	testMatrix.setMatrixElement(0,2,1);

	testMatrix.setMatrixElement(1,0,5);
	testMatrix.setMatrixElement(1,1,3);
	testMatrix.setMatrixElement(1,2,11);

	testMatrix.setMatrixElement(2,0,7);
	testMatrix.setMatrixElement(2,1,6);
	testMatrix.setMatrixElement(2,2,-4);

	cout << "Householder TestMatrix" << endl;
	testMatrix.printMatrix();

	DynamicMatrix householderTrans_result = DynamicMatrix(3,3);

	dmultip.reload(&testMatrix,&householderTrans_33_from22);
	dmultip.multiplyCalc();
	householderTrans_result.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	cout << "TestMatrix * householderTrans_33_from22  " << endl;
	householderTrans_result.printMatrix();

	dmultip.reload(&householderTrans_result,&householderTrans_33);
	dmultip.multiplyCalc();
	householderTrans_result.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	cout << "TestMatrix*householderTrans_33_from22 * householderTrans_33" << endl;
	householderTrans_result.printMatrix();
/*
	dmultip.reload(&householderTrans_33,&testMatrix);
	dmultip.multiplyCalc();
	householderTrans_result.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	cout << "householderTrans_33 * TestMatrix" << endl;
	householderTrans_result.printMatrix();

	dmultip.reload(&householderTrans_33_from22,&householderTrans_result);
	dmultip.multiplyCalc();
	householderTrans_result.copyMatrixElementNoCheck(dmultip.getMultiplyResult());
	cout << "householderTrans_33_from22 * householderTrans_33 * TestMatrix" << endl;
	householderTrans_result.printMatrix();
	*/
};
