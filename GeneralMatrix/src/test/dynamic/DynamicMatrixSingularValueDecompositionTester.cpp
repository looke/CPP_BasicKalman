/*
 * MatrixSingularValueDecompositionTester.cpp
 *
 *  Created on: 2017Äê3ÔÂ24ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "DynamicMatrixSingularValueDecompositionTester.h"
#include "dynamic\util\DynamicMatrixTransposer.h"
//#include "MatrixTransposer.h"
using namespace std;

DynamicMatrixSingularValueDecompositionTester::DynamicMatrixSingularValueDecompositionTester()
{

};

void DynamicMatrixSingularValueDecompositionTester::test()
{
	/*
	DynamicMatrix singularValueDecMatrix(2,2);

	singularValueDecMatrix.setMatrixElement(0,0,2);
	singularValueDecMatrix.setMatrixElement(0,1,1);

	singularValueDecMatrix.setMatrixElement(1,0,1);
	singularValueDecMatrix.setMatrixElement(1,1,2);
	 */

	/*
	DynamicMatrix singularValueDecMatrix(2,3);

	singularValueDecMatrix.setMatrixElement(0,0,3);
	singularValueDecMatrix.setMatrixElement(0,1,1);
	singularValueDecMatrix.setMatrixElement(0,2,1);

	singularValueDecMatrix.setMatrixElement(1,0,-1);
	singularValueDecMatrix.setMatrixElement(1,1,3);
	singularValueDecMatrix.setMatrixElement(1,2,1);
	*/


	DynamicMatrix singularValueDecMatrix(4,5);
	singularValueDecMatrix.setMatrixElement(0,0,1);
	singularValueDecMatrix.setMatrixElement(0,1,0);
	singularValueDecMatrix.setMatrixElement(0,2,0);
	singularValueDecMatrix.setMatrixElement(0,3,0);
	singularValueDecMatrix.setMatrixElement(0,4,2);

	singularValueDecMatrix.setMatrixElement(1,0,0);
	singularValueDecMatrix.setMatrixElement(1,1,0);
	singularValueDecMatrix.setMatrixElement(1,2,3);
	singularValueDecMatrix.setMatrixElement(1,3,0);
	singularValueDecMatrix.setMatrixElement(1,4,0);

	singularValueDecMatrix.setMatrixElement(2,0,0);
	singularValueDecMatrix.setMatrixElement(2,1,0);
	singularValueDecMatrix.setMatrixElement(2,2,0);
	singularValueDecMatrix.setMatrixElement(2,3,0);
	singularValueDecMatrix.setMatrixElement(2,4,0);

	singularValueDecMatrix.setMatrixElement(3,0,0);
	singularValueDecMatrix.setMatrixElement(3,1,2);
	singularValueDecMatrix.setMatrixElement(3,2,0);
	singularValueDecMatrix.setMatrixElement(3,3,0);
	singularValueDecMatrix.setMatrixElement(3,4,0);



	DynamicMatrixSingularValueDecomposition singularValueDec = DynamicMatrixSingularValueDecomposition(&singularValueDecMatrix);

	cout << "OP Matrix" << endl;
	singularValueDec.printOpMatrix();

	cout << "OP T Matrix" << endl;
	singularValueDec.printOpTMatrix();


	singularValueDec.sigularValueDecomposition(1);

	DynamicMatrix UMatrix(singularValueDecMatrix.rowNum,singularValueDecMatrix.rowNum);
	DynamicMatrix SMatrix(singularValueDecMatrix.rowNum,singularValueDecMatrix.columnNum);
	DynamicMatrix VMatrix(singularValueDecMatrix.columnNum,singularValueDecMatrix.columnNum);

	DynamicMatrix ResultMatrix(singularValueDecMatrix.rowNum,singularValueDecMatrix.columnNum);
	UMatrix.copyMatrixElementNoCheck(singularValueDec.getUMatrix());
	SMatrix.copyMatrixElementNoCheck(singularValueDec.getSingularValueMatrix());
	VMatrix.copyMatrixElementNoCheck(singularValueDec.getVMatrix());

	cout << "Test U" << endl;
	UMatrix.printMatrix();
	cout << "Test S" << endl;
	SMatrix.printMatrix();
	cout << "Test V" << endl;
	VMatrix.printMatrix();

	DynamicMatrixTransposer tr = DynamicMatrixTransposer(&VMatrix);
	tr.transposeMatrix();
	VMatrix.copyMatrixElementNoCheck(tr.getTransposeMatrix());
	cout << "Test VT" << endl;
	VMatrix.printMatrix();

	DynamicMatrixMultiplier multi = DynamicMatrixMultiplier(&UMatrix, &SMatrix);
	multi.multiplyCalc();
	ResultMatrix.copyMatrixElementNoCheck(multi.getMultiplyResult());
	cout << "Test U*S" << endl;
	ResultMatrix.printMatrix();

	multi.reload(&ResultMatrix, &VMatrix);
	multi.multiplyCalc();
	ResultMatrix.copyMatrixElementNoCheck(multi.getMultiplyResult());

	cout << "Test U*S*VT" << endl;
	ResultMatrix.printMatrix();


};

