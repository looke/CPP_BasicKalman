/*
 * StaticMatrixCholeskyDecompositionTest.cpp
 *
 *  Created on: 2017Äê4ÔÂ8ÈÕ
 *      Author: looke
 */


#include "test\static\StaticMatrixCholeskyDecompositionTest.h"
#include "static\util\StaticMatrixTransposer.h"
#include <iostream>
#include "basic\BasicMatrix.h"
#include "static\util\StaticMatrixMultiplier.h"
using namespace std;


StaticMatrixCholeskyDecompositionTest::StaticMatrixCholeskyDecompositionTest()
{};

void StaticMatrixCholeskyDecompositionTest::test()
{
	StaticMatrix testMatrix33 = StaticMatrix(3,3);
	//testMatrix33.init(3,3);
	//BasicMatrix* p_testMatrix33 = testMatrix33.getCurrentMatrixPointer();
	BasicMatrix* p_testMatrix33 = &testMatrix33;

	p_testMatrix33->setMatrixElement(0,0,3);
	p_testMatrix33->setMatrixElement(0,1,2);
	p_testMatrix33->setMatrixElement(0,2,3);

	p_testMatrix33->setMatrixElement(1,0,2);
	p_testMatrix33->setMatrixElement(1,1,2);
	p_testMatrix33->setMatrixElement(1,2,0);

	p_testMatrix33->setMatrixElement(2,0,3);
	p_testMatrix33->setMatrixElement(2,1,0);
	p_testMatrix33->setMatrixElement(2,2,12);

	cout << "OP Matrix" << endl;
	p_testMatrix33->printMatrix();

	StaticMatrixCholeskyDecomposition choleDecomp = StaticMatrixCholeskyDecomposition(p_testMatrix33);
	choleDecomp.generateDecompositionMatrix();

	BasicMatrix* p_CholeMatrix = choleDecomp.getDecompositionMatrix();
	cout << "Cholesky Matrix" << endl;
	p_CholeMatrix->printMatrix();

	StaticMatrixTransposer tranposer = StaticMatrixTransposer(p_CholeMatrix);
	tranposer.transposeMatrix();
	BasicMatrix* p_CholeMatrixTrans = tranposer.getTransposeMatrix();
	cout << "Cholesky Matrix Trans" << endl;
	p_CholeMatrixTrans->printMatrix();

	StaticMatrixMultiplier multiplier = StaticMatrixMultiplier(p_CholeMatrixTrans, p_CholeMatrix);
	multiplier.multiplyCalc();
	BasicMatrix* p_MultiResult = multiplier.getMultiplyResult();
	cout << "CholeskyT * Cholesky Result" << endl;
	p_MultiResult->printMatrix();
};

