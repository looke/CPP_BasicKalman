/*
 * tester.cpp
 *
 *  Created on: 2017Äê2ÔÂ19ÈÕ
 *      Author: looke
 */

#include <dynamic\DynamicMatrixCholeskyDecompositionTester.h>
#include <dynamic\DynamicMatrixEigenValueSolverTester.h>
#include <dynamic\DynamicMatrixSingularValueDecompositionTester.h>

#include <iostream>
#include <windows.h>
#include "..\matrix\dynamic\DynamicMatrix.h"
#include "dynamic\util\DynamicMatrixEquationSolver.h"
#include "static\StaticMatrixUnitTest.h"
#include "test\static\StaticMatrixTest.h"
#include "test\static\StaticMatrixMultipleTest.h"
#include "test\static\StaticMatrixTransposerTest.h"
#include "test\static\StaticMatrixInverserTest.h"
#include "test\static\StaticMatrixSquareRootSolverTest.h"
#include "test\static\StaticMatrixEigenValueSolverTest.h"
#include "test\static\StaticMatrixCholeskyDecompositionTest.h"
#include "test\static\StaticMatrixSingularValueDecompositionTest.h"
#include "test\calibrate\EllipseFittingTest.h"
#include "test\dynamic\DynamicMatrixTest.h"
#include "test\transformation\DynamicGivensTransformationTester.h"
#include "test\transformation\DynamicHouseholderTransformationTester.h"
#include "test\transformation\DynamicQRDecompositionTest.h"
#include "test\transformation\DynamicHessenbergTriangleFormularTest.h"
#include "test\transformation\DynamicHessenbergFormularTest.h"
#include "test\eigen\QR\DynamicNormalQRIterationTest.h"
#include "test\eigen\QR\DynamicDoubleShiftQRIterationTest.h"
#include "test\eigen\QR\DynamicSingleShiftQRIterationTest.h"
#include "test\eigen\DynamicNormalEigenSolverForRealTest.h"
#include "test\eigen\QZ\DynamicSingleShiftQZIterationTest.h"
#include "test\eigen\QZ\DynamicDoubleShiftQZIterationTest.h"
#include "test\eigen\DynamicGeneralizedEigenSolverForRealTest.h"
#include "test\eigen\DynamicEigenValuePrinterTest.h"

#include "test\calibrate\EllipseFittingByDLSTest.h"

#include <malloc.h>
#include <transformation/DynamicQZTriangleZeroChasingTest.h>
#include <vector/DynamicVectorTest.h>
#include <vector/StaticVectorTest.h>
#include <cmath>
#include "math.h"
#define PI 3.14159265
using namespace std;

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	cout << "--------------" << endl;

	//DynamicVectorTest dyVectorTest = DynamicVectorTest();
	//dyVectorTest.test();

	//DynamicMatrixTest dyMatrixTest = DynamicMatrixTest();
	//dyMatrixTest.test();

	//MatrixCholeskyDecompositionTester CholeskyTest = MatrixCholeskyDecompositionTester();
	//CholeskyTest.test();

	//MatrixEigenValueSolverTester EigenValueTest = MatrixEigenValueSolverTester();
	//EigenValueTest.test();

	//MatrixSingularValueDecompositionTester SingularValueDecTest = MatrixSingularValueDecompositionTester();
	//SingularValueDecTest.test();

	//DynamicMatrixEigenValueSolverTester EigenValueSolverTester = DynamicMatrixEigenValueSolverTester();
	//EigenValueSolverTester.test();

	//DynamicMatrixSingularValueDecompositionTester SingularValueDecTest = DynamicMatrixSingularValueDecompositionTester();
	//SingularValueDecTest.test();

	//StaticMatrixUnitTest staticMatrixunitTester = StaticMatrixUnitTest();
	//staticMatrixunitTester.test();

	//StaticVectorTest sVtest = StaticVectorTest();
	//sVtest.test();

	//StaticMatrixTest staticMatrixTester = StaticMatrixTest();
	//staticMatrixTester.test();

	//StaticMatrixMultipleTest staticMultiplierTester = StaticMatrixMultipleTest();
	//staticMultiplierTester.test();

	//StaticMatrixTransposerTest staticTransposerTester = StaticMatrixTransposerTest();
	//staticTransposerTester.test();

	//StaticMatrixInverserTest staticInversTester = StaticMatrixInverserTest();
	//staticInversTester.test();

	//StaticMatrixSquareRootSolverTest sqrtTester = StaticMatrixSquareRootSolverTest();
	//sqrtTester.test();

	//StaticMatrixEigenValueSolverTest egvTester = StaticMatrixEigenValueSolverTest();
	//egvTester.test();

	//StaticMatrixCholeskyDecompositionTest choleTester = StaticMatrixCholeskyDecompositionTest();
	//choleTester.test();

	//StaticMatrixSingularValueDecompositionTest svdTester = StaticMatrixSingularValueDecompositionTest();
	//svdTester.test();

	//EllipseFittingTest ellipseTest = EllipseFittingTest();
	//ellipseTest.test();

	//DynamicVectorTester dVtest = DynamicVectorTester();
	//dVtest.test();


	//DynamicGivensTransformationTester givensTester = DynamicGivensTransformationTester();
	//givensTester.test();

	//DynamicHouseholderTransformationTester houseHolderTester = DynamicHouseholderTransformationTester();
	//houseHolderTester.test();

	//DynamicQRDecompositionTest qrDecompTest = DynamicQRDecompositionTest();
	//qrDecompTest.test();

	//DynamicHessenbergTriangleFormularTest hessenBergTriangleTest = DynamicHessenbergTriangleFormularTest();
	//hessenBergTriangleTest.test();

	//EllipseFittingByDLSTest ellipseDLSTest = EllipseFittingByDLSTest();
	//ellipseDLSTest.test();

	//DynamicQZTriangleZeroChasingTest dZeroChasingTest = DynamicQZTriangleZeroChasingTest();
	//dZeroChasingTest.test();

	//DynamicHessenbergFormularTest hessenFormularTest = DynamicHessenbergFormularTest();
	//hessenFormularTest.test();

	//DynamicNormalQRIterationTest normQRIterateTest = DynamicNormalQRIterationTest();
	//normQRIterateTest.test();

	//DynamicSingleShiftQRIterationTest singleShiftQRIterationTest = DynamicSingleShiftQRIterationTest();
	//singleShiftQRIterationTest.test();

	//DynamicDoubleShiftQRIterationTest doubleShiftQrTest = DynamicDoubleShiftQRIterationTest();
	//doubleShiftQrTest.test();

	//DynamicNormalEigenSolverForRealTest dNormalEigen4RTest = DynamicNormalEigenSolverForRealTest();
	//dNormalEigen4RTest.test();

	//DynamicSingleShiftQZIterationTest dSingleQZIterationTest = DynamicSingleShiftQZIterationTest();
	//dSingleQZIterationTest.test();

	//DynamicDoubleShiftQZIterationTest dqzTest = DynamicDoubleShiftQZIterationTest();
	//dqzTest.test();

	DynamicGeneralizedEigenSolverForRealTest generalizedEigenTest = DynamicGeneralizedEigenSolverForRealTest();
	generalizedEigenTest.test();

	//DynamicEigenValuePrinterTest eigenPrinterTest = DynamicEigenValuePrinterTest();
	//eigenPrinterTest.test();
}

