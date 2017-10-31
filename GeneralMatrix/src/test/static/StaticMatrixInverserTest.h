/*
 * StaticMatrixInverserTest.h
 *
 *  Created on: 2017Äê4ÔÂ7ÈÕ
 *      Author: looke
 */

#ifndef TEST_STATIC_STATICMATRIXINVERSERTEST_H_
#define TEST_STATIC_STATICMATRIXINVERSERTEST_H_


#include "static\util\StaticMatrixInverser.h"
#include "basic\BasicMatrix.h"
#include "static\util\StaticMatrixMultiplier.h"
#include "..\matrix\static\StaticMatrix.h"

class StaticMatrixInverserTest
{
public:
	StaticMatrixInverserTest();
	void test();

	void calcBinv();
	void calcABinvLast2x2();

	void calcABinvFirst3x2();
private:

	StaticMatrix myTestMatrix33_B;
	StaticMatrix myTestMatrix33_A;

	double Binv_n_2_n_2;
	double Binv_n_2_n_1;
	double Binv_n_2_n;

	double Binv_n_1_n_1;
	double Binv_n_1_n;

	double Binv_n_n;
};


#endif /* TEST_STATIC_STATICMATRIXINVERSERTEST_H_ */
