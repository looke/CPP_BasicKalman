/*
 * DynamicHessenbergFormularTest.cpp
 *
 *  Created on: 2017Äê5ÔÂ8ÈÕ
 *      Author: looke
 */

#include "DynamicHessenbergFormularTest.h"
#include "..\vector\dynamic\DynamicVector.h"
#include "..\matrix\basic\BasicMatrix.h"
#include "iostream"
using namespace std;


DynamicHessenbergFormularTest::DynamicHessenbergFormularTest()
{};

void DynamicHessenbergFormularTest::test()
{
	DynamicMatrix test44 = DynamicMatrix(4,4);
/*
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
*/
	test44.setMatrixElement(0,0,5);
	test44.setMatrixElement(0,1,-2);
	test44.setMatrixElement(0,2,2.8284271);
	test44.setMatrixElement(0,3,-4.2426407);

	test44.setMatrixElement(1,0,1);
	test44.setMatrixElement(1,1,0);
	test44.setMatrixElement(1,2,3.5355339);
	test44.setMatrixElement(1,3,-0.7071068);

	test44.setMatrixElement(2,0,0);
	test44.setMatrixElement(2,1,-1.41421356);
	test44.setMatrixElement(2,2,1);
	test44.setMatrixElement(2,3,0);

	test44.setMatrixElement(3,0,0);
	test44.setMatrixElement(3,1,1.41421356);
	test44.setMatrixElement(3,2,-4);
	test44.setMatrixElement(3,3,-1);

	cout << "Input OP matrix" << endl;
	test44.printMatrix();

	DynamicHessenbergFormular hessenbergFormular =  DynamicHessenbergFormular(&test44);
	hessenbergFormular.formularUpperHessnbergMatrix();

	cout << "After Trans OP matrix" << endl;
	hessenbergFormular.getOpMatrix()->printMatrix();


	DynamicMatrix QTMatrix = DynamicMatrix(4,4);
	QTMatrix.copyMatrixElementNoCheck(hessenbergFormular.getPreTransMatrix());

	DynamicMatrix QMatrix = DynamicMatrix(4,4);
	QMatrix.copyMatrixElementNoCheck(hessenbergFormular.getAfterTransMatrix());

	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(&QTMatrix,&test44);
	multip.multiplyCalc();
	test44.copyMatrixElementNoCheck(multip.getMultiplyResult());
	multip.reload(&test44,&QMatrix);
	multip.multiplyCalc();
	test44.copyMatrixElementNoCheck(multip.getMultiplyResult());
	cout << "QT*test44*Q" << endl;
	test44.printMatrix();

	/*
	hessenbergFormular.generateSubHouseholderTrans(0);

	cout << "Sub trans matrix for iterate 0" << endl;
	hessenbergFormular.getSubTransMatrix()->printMatrix();

	cout << "trans matrix for iterate 0" << endl;
	hessenbergFormular.getTransMatrix()->printMatrix();

	hessenbergFormular.upgradeSubHouseholderTrans(0);
	cout << "trans matrix for iterate 0" << endl;
	hessenbergFormular.getTransMatrix()->printMatrix();

	cout << "pre trans matrix for iterate 0" << endl;
	hessenbergFormular.getPreTransMatrix()->resetMatrixToI();
	hessenbergFormular.getPreTransMatrix()->printMatrix();

	hessenbergFormular.updatePreTransMatrix();
	cout << "pre trans matrix for iterate 0" << endl;
	hessenbergFormular.getPreTransMatrix()->printMatrix();

	cout << "after trans matrix for iterate 0" << endl;
	hessenbergFormular.getAfterTransMatrix()->resetMatrixToI();
	hessenbergFormular.getAfterTransMatrix()->printMatrix();

	hessenbergFormular.updateAfterTransMatrix();
	cout << "after trans matrix for iterate 0" << endl;
	hessenbergFormular.getAfterTransMatrix()->printMatrix();

	cout << "OP matrix for iterate 0" << endl;
	hessenbergFormular.getOpMatrix()->printMatrix();

	hessenbergFormular.updateOpMatrix();
	cout << "OP matrix for iterate 0" << endl;
	hessenbergFormular.getOpMatrix()->printMatrix();
	*/
};
