/*
 * StaticMatrixSingularValueDecompositionTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ8ÈÕ
 *      Author: looke
 */


#include "test\static\StaticMatrixSingularValueDecompositionTest.h"
#include <iostream>
#include "basic\BasicMatrix.h"
#include "static\util\StaticMatrixTransposer.h"
#include "static\util\StaticMatrixMultiplier.h"
using namespace std;


StaticMatrixSingularValueDecompositionTest::StaticMatrixSingularValueDecompositionTest()
{};

void StaticMatrixSingularValueDecompositionTest::test()
{
	StaticMatrix testMatrix23 = StaticMatrix(2,3);
	//testMatrix23.init(2,3);
	//BasicMatrix* p_testMatrix23 = testMatrix23.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix23 = &testMatrix23;

	p_testMatrix23->setMatrixElement(0,0,3);
	p_testMatrix23->setMatrixElement(0,1,1);
	p_testMatrix23->setMatrixElement(0,2,1);

	p_testMatrix23->setMatrixElement(1,0,-1);
	p_testMatrix23->setMatrixElement(1,1,3);
	p_testMatrix23->setMatrixElement(1,2,1);

	cout << "OP Matrix" << endl;
	p_testMatrix23->printMatrix();

	StaticMatrixSingularValueDecomposition staticSVD = StaticMatrixSingularValueDecomposition(p_testMatrix23);
	staticSVD.sigularValueDecomposition(1);

	BasicMatrix* p_U = staticSVD.getUMatrix();
	BasicMatrix* p_S = staticSVD.getSingularValueMatrix();
	BasicMatrix* p_V = staticSVD.getVMatrix();

	cout << "U Matrix" << endl;
	p_U->printMatrix();
	cout << "Singular Value Matrix" << endl;
	p_S->printMatrix();
	cout << "V Matrix" << endl;
	p_V->printMatrix();

	StaticMatrixTransposer sTrans = StaticMatrixTransposer(p_V);
	sTrans.transposeMatrix();
	BasicMatrix* p_VT = sTrans.getTransposeMatrix();
	cout << "---------------VT Matrix-----------------" << endl;
	p_VT->printMatrix();

	StaticMatrixMultiplier sMulti = StaticMatrixMultiplier(p_U, p_S);
	sMulti.multiplyCalc();

	StaticMatrix USMultiResult = StaticMatrix(2,3);
	//USMultiResult.init(2,3);
	//BasicMatrix* p_multiUSResult = USMultiResult.getCurrentMatrixPointer();
	BasicMatrix* p_multiUSResult = &USMultiResult;

	p_multiUSResult->copyMatrixElementNoCheck(sMulti.getMultiplyResult());
	cout << "---------------U*S Matrix-----------------" << endl;
	p_multiUSResult->printMatrix();

	sMulti.reload(p_multiUSResult, p_VT);
	sMulti.multiplyCalc();
	BasicMatrix* p_muUSVTltiResult = sMulti.getMultiplyResult();

	cout << "---------------U*S*VT Matrix-----------------" << endl;
	p_muUSVTltiResult->printMatrix();
};
