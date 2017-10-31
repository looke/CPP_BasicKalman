/*
 * StaticMatrixMultipleTest.cpp
 *
 *  Created on: 2017Äê3ÔÂ25ÈÕ
 *      Author: looke
 */

#include <iostream>
#include "basic\BasicMatrix.h"
#include "StaticMatrixMultipleTest.h"
#include "..\matrix\static\StaticMatrix.h"

using namespace std;


StaticMatrixMultipleTest::StaticMatrixMultipleTest()
{
};

void StaticMatrixMultipleTest::test()
{
	StaticMatrix leftMatrix33 = StaticMatrix(3,3);
	//leftMatrix33.init(3,3);

	//BasicMatrix* p_leftMatrix33 = leftMatrix33.getCurrentMatrixPointer();
	BasicMatrix* p_leftMatrix33 = &leftMatrix33;
	p_leftMatrix33->setMatrixElement(0,0,0.788206);
	p_leftMatrix33->setMatrixElement(0,1,-0.615412);
	p_leftMatrix33->setMatrixElement(0,2,0);

	p_leftMatrix33->setMatrixElement(1,0,0.615412);
	p_leftMatrix33->setMatrixElement(1,1,0.788206);
	p_leftMatrix33->setMatrixElement(1,2,0);

	p_leftMatrix33->setMatrixElement(2,0,0);
	p_leftMatrix33->setMatrixElement(2,1,0);
	p_leftMatrix33->setMatrixElement(2,2,1);

	cout << "Left OP Matrix33" << endl;
	p_leftMatrix33->printMatrix();

	StaticMatrix rightMatrix33 = StaticMatrix(3,3);
	//rightMatrix33.init(3,3);

	//BasicMatrix* p_rightMatrix33 = rightMatrix33.getCurrentMatrixPointer();
	BasicMatrix* p_rightMatrix33 = &rightMatrix33;
	p_rightMatrix33->setMatrixElement(0,0,4);
	p_rightMatrix33->setMatrixElement(0,1,2);
	p_rightMatrix33->setMatrixElement(0,2,2);

	p_rightMatrix33->setMatrixElement(1,0,2);
	p_rightMatrix33->setMatrixElement(1,1,5);
	p_rightMatrix33->setMatrixElement(1,2,1);

	p_rightMatrix33->setMatrixElement(2,0,2);
	p_rightMatrix33->setMatrixElement(2,1,1);
	p_rightMatrix33->setMatrixElement(2,2,6);

	cout << "Right OP Matrix" << endl;
	p_rightMatrix33->printMatrix();


	StaticMatrixMultiplier multiplier = StaticMatrixMultiplier(p_leftMatrix33, p_rightMatrix33);
	multiplier.multiplyCalc();
	BasicMatrix* p_multiResult = multiplier.getMultiplyResult();

	cout << "Multi Result" << endl;
	p_multiResult->printMatrix();


	p_leftMatrix33->copyMatrixElementNoCheck(p_multiResult);

	p_rightMatrix33->setMatrixElement(0,0,0.788206);
	p_rightMatrix33->setMatrixElement(0,1,0.615412);
	p_rightMatrix33->setMatrixElement(0,2,0);

	p_rightMatrix33->setMatrixElement(1,0,-0.615412);
	p_rightMatrix33->setMatrixElement(1,1,0.788206);
	p_rightMatrix33->setMatrixElement(1,2,0);

	p_rightMatrix33->setMatrixElement(2,0,0);
	p_rightMatrix33->setMatrixElement(2,1,0);
	p_rightMatrix33->setMatrixElement(2,2,1);

	multiplier.reload(p_leftMatrix33,p_rightMatrix33);
	multiplier.multiplyCalc();

	p_multiResult = multiplier.getMultiplyResult();
	cout << "Multi Result" << endl;
	p_multiResult->printMatrix();

/*
	StaticMatrixUnit leftMatrix22 = StaticMatrixUnit();
	leftMatrix22.init(2,2);

	BasicMatrix* p_leftMatrix22 = leftMatrix22.getCurrentMatrixPointer();
	cout << "Left OP Matrix22" << endl;
	p_leftMatrix22->printMatrix();

	StaticMatrixUnit rightMatrix22 = StaticMatrixUnit();
	rightMatrix22.init(2,2);

	BasicMatrix* p_rightMatrix22 = rightMatrix22.getCurrentMatrixPointer();
	cout << "Right OP Matrix22" << endl;
	p_rightMatrix22->printMatrix();

	multiplier.reload(p_leftMatrix22,p_rightMatrix22);
	multiplier.multiplyCalc();
	p_multiResult = multiplier.getMultiplyResult();
	cout << "Multi Result" << endl;
	p_multiResult->printMatrix();


	//2*3 3*2
	StaticMatrixUnit leftMatrix23 = StaticMatrixUnit();
	leftMatrix23.init(2,3);
	BasicMatrix* p_leftMatrix23 = leftMatrix23.getCurrentMatrixPointer();
	cout << "Left OP Matrix23" << endl;
	p_leftMatrix23->printMatrix();

	StaticMatrixUnit rightMatrix32 = StaticMatrixUnit();
	rightMatrix32.init(3,2);
	BasicMatrix* p_rightMatrix32 = rightMatrix32.getCurrentMatrixPointer();
	cout << "Right OP Matrix32" << endl;
	p_rightMatrix32->printMatrix();
	//2*3 3*2
	multiplier.reload(p_leftMatrix23, p_rightMatrix32);
	multiplier.multiplyCalc();
	p_multiResult = multiplier.getMultiplyResult();
	cout << "Multi Result" << endl;
	p_multiResult->printMatrix();

	//3*2 2*3
	multiplier.reload(p_rightMatrix32, p_leftMatrix23);
	multiplier.multiplyCalc();
	p_multiResult = multiplier.getMultiplyResult();
	cout << "Multi Result" << endl;
	p_multiResult->printMatrix();


	p_leftMatrix23->setMatrixElement(0,0,2.44949);
	p_leftMatrix23->setMatrixElement(0,1,-2.23607);
	p_leftMatrix23->setMatrixElement(0,2,0);

	p_leftMatrix23->setMatrixElement(1,0,2.44949);
	p_leftMatrix23->setMatrixElement(1,1,2.23607);
	p_leftMatrix23->setMatrixElement(1,2,0);
	cout << "Left OP Matrix23" << endl;
	p_leftMatrix23->printMatrix();

	p_leftMatrix33->setMatrixElement(0,0,0.408248);
	p_leftMatrix33->setMatrixElement(0,1,0.816496);
	p_leftMatrix33->setMatrixElement(0,2,0.408248);

	p_leftMatrix33->setMatrixElement(1,0,-0.894427);
	p_leftMatrix33->setMatrixElement(1,1,0.447214);
	p_leftMatrix33->setMatrixElement(1,2,0.00000008641);

	p_leftMatrix33->setMatrixElement(2,0,-0.182574);
	p_leftMatrix33->setMatrixElement(2,1,-0.365148);
	p_leftMatrix33->setMatrixElement(2,2,0.912871);

	cout << "Right OP Matrix33" << endl;
	p_leftMatrix33->printMatrix();

	multiplier.reload(p_leftMatrix23, p_leftMatrix33);
	multiplier.multiplyCalc();
	p_multiResult = multiplier.getMultiplyResult();
	cout << "Multi Result" << endl;
	p_multiResult->printMatrix();
	*/
};

