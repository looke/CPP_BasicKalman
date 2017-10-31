/*
 * Test.cpp
 *
 *  Created on: 2016年11月17日
 *      Author: looke
 */
#include <iostream>
#include <windows.h>
//#include "QFormula.h"
//#include "MyMatrix.h"
#include "StaticPosCalc.h"
#include "DynamPosCalc.h"
#include <malloc.h>
#include <cmath>
#include "math.h"
#define PI 3.14159265
using namespace std;

int main()
{
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	/*
	float test_matrix_1[3][4];
	test_matrix_1[0][0] = 1;
	test_matrix_1[0][1] = 1;
	test_matrix_1[0][2] = 2;
	test_matrix_1[0][3] = 2;


	test_matrix_1[1][0] = 3;
	test_matrix_1[1][1] = 4;
	test_matrix_1[1][2] = 5;
	test_matrix_1[1][3] = 5;

	test_matrix_1[2][0] = 4;
	test_matrix_1[2][1] = 2;
	test_matrix_1[2][2] = 8;
	test_matrix_1[2][3] = 8;

	float test_matrix_2[4][5];
	test_matrix_2[0][0] = 2;
	test_matrix_2[0][1] = 3;
	test_matrix_2[0][2] = 11;
	test_matrix_2[0][3] = 5;
	test_matrix_2[0][4] = 2;

	test_matrix_2[1][0] = 1;
	test_matrix_2[1][1] = 1;
	test_matrix_2[1][2] = 5;
	test_matrix_2[1][3] = 2;
	test_matrix_2[1][4] = 1;

	test_matrix_2[2][0] = 2;
	test_matrix_2[2][1] = 1;
	test_matrix_2[2][2] = 3;
	test_matrix_2[2][3] = 2;
	test_matrix_2[2][4] = -3;

	test_matrix_2[3][0] = 1;
	test_matrix_2[3][1] = 1;
	test_matrix_2[3][2] = 3;
	test_matrix_2[3][3] = 4;
	test_matrix_2[3][4] = -3;

	test_matrix_1[3][0] = 6;
	test_matrix_1[3][1] = 7;
	test_matrix_1[3][2] = 8;
	test_matrix_1[3][3] = 8;
	*/

	/*
	QFormula q;
	//q.QFormula();
	//q.printMatrix(&test_matrix_1[0]);
	//q.printMatrix(test_matrix_1);
	//q.matrix[0][0] = 11;
	cout<<"my matrix 1:"<<endl;

	MyMatrix testMatrix(3,4);
	testMatrix.printMatrix();
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<4;j++)
		{
			testMatrix.setMatrixElement(i,j,test_matrix_1[i][j]);
		}
	}
	cout<<"my matrix 1 after set:"<<endl;
	testMatrix.printMatrix();
	testMatrix.gaussElim_ColmnPrin();


	cout<<"my matrix 2:"<<endl;
	MyMatrix testMatrix_2(4,5);
	testMatrix_2.printMatrix();
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<5;j++)
		{
			testMatrix_2.setMatrixElement(i,j,test_matrix_2[i][j]);
		}
	}
	cout<<"my matrix 2 after set:"<<endl;
	testMatrix_2.printMatrix();
	testMatrix_2.gaussElim_ColmnPrin();
	testMatrix_2.calcRoots();

	int row = testMatrix.findPivotRow(0);
	cout<<"my matrix 1 pivot:"<< row <<endl;

	testMatrix.swapRow(row,0);
	cout<<"my matrix 1 after swap pivot:"<<endl;
	testMatrix.printMatrix();

	testMatrix.normalizePivotRow(0);
	cout<<"my matrix 1 after normalize pivot:"<<endl;
	testMatrix.printMatrix();

	testMatrix.eliminateSubMatrix(0);
	cout<<"my matrix 1 after eliminate:"<<endl;
	testMatrix.printMatrix();


	cout<<"my matrix 2:"<<endl;
	MyMatrix testMatrix2(3,4);
	testMatrix2.printMatrix();
	testMatrix2.copyMatrix(testMatrix.getMatrixPointer());

	cout << "Pivot row of 0:" << testMatrix2.findPivotRow(0) <<endl;

	testMatrix2.swapRow(0,2);
	cout<<"after swap 0,2" << endl;
	testMatrix2.printMatrix();
	cout << "Pivot row of 0:" << testMatrix2.findPivotRow(0) <<endl;
	//testMatrix.copyMatrix(tMatrix_p);

	MyMatrix testMatrix3(3,2);
	cout<<"my matrix 3:"<<endl;
	testMatrix3.printMatrix();
	cout << "testMatrix3 Pivot row of 0:" << testMatrix3.findPivotRow(0) <<endl;
	cout << "testMatrix3 Pivot row of 1:" << testMatrix3.findPivotRow(1) <<endl;
	cout << "testMatrix3 Pivot row of 2:" << testMatrix3.findPivotRow(2) <<endl;



	//测试原始地理坐标下，计算出的四元数
	float acc[3] = {0,0,-1};
	float mag[3] = {0,1,0};
	float qStart[4] = {1,0,0,0};

	StaticPosCalc myStaticPos(acc, mag, qStart);
	myStaticPos.test();
	*/

	//测试原始地理坐标绕y轴转30度下，计算出的四元数
	//float acc_180z[3] = {-0.5,0,-0.866};



	/*
	//俯仰角
	float acc_pitch = 30 *PI/180;
	float mag_Sensor_b_y = cos(mag_Sensor_b_Inclination);
	float mag_Sensor_b_z = sin(mag_Sensor_b_Inclination) * cos(acc_pitch);
	mag_Sensor_b_z = 0-mag_Sensor_b_z;
	float mag_Sensor_b_x = sin(mag_Sensor_b_Inclination) * sin(acc_pitch);
	mag_Sensor_b_x = 0 -mag_Sensor_b_x;

	float acc_x = sin(acc_pitch);
	acc_x = 0 - acc_x;
	float acc_z = cos(acc_pitch);
	acc_z = 0 - acc_z;

	float acc_180z[3] = {acc_x,0,acc_z};
	float mag_180z[3] = {mag_Sensor_b_x,mag_Sensor_b_y,mag_Sensor_b_z};

	*/

	/*
	//偏航角
	float acc_yaw = 5 * PI/180;
	float mag_Sensor_b_y = cos(mag_Sensor_b_Inclination) * cos(acc_yaw);
	float mag_Sensor_b_z = sin(mag_Sensor_b_Inclination);
	mag_Sensor_b_z = 0-mag_Sensor_b_z;
	float mag_Sensor_b_x = cos(mag_Sensor_b_Inclination) * sin(acc_yaw);

	float acc_180z[3] = {0,0,-1};
	float mag_180z[3] = {mag_Sensor_b_x,mag_Sensor_b_y,mag_Sensor_b_z};
	*/

	//Mag传感器地磁倾角
	float mag_Sensor_b_Inclination = 52 *PI/180;

	//横滚角
	float acc_roll = 5 * PI/180;
	float mag_Sensor_b_y = cos(mag_Sensor_b_Inclination - acc_roll);
	float mag_Sensor_b_z = sin(mag_Sensor_b_Inclination - acc_roll);
	mag_Sensor_b_z = 0-mag_Sensor_b_z;
	float mag_Sensor_b_x = 0;

	float acc_y = sin(acc_roll);
	float acc_z = cos(acc_roll);
	acc_z = 0 - acc_z;

	float acc_180z[3] = {0,acc_y,acc_z};
	float mag_180z[3] = {mag_Sensor_b_x,mag_Sensor_b_y,mag_Sensor_b_z};


	//初始位置位于y轴转N度
	float y_rotate = 11*PI/180;
	float Q0 = cos(y_rotate/2);
	float Q2 = sin(y_rotate/2);
	Q2 = 0-Q2;
	float qStart_180z[4] = {Q0,0,Q2,0};

	DWORD start;
	DWORD stop;

	StaticPosCalc myStaticPos(acc_180z, mag_180z, qStart_180z);
	myStaticPos.setPrecision(0.05);
	start = GetTickCount();
	myStaticPos.test();
	stop = GetTickCount();
	DWORD eclipseTime = stop - start;
	cout << "Total Time Eclipse:" << eclipseTime << endl;
	/*
	 *
	StaticPosCalc myStaticPos_180z(acc_180z, mag_180z, qStart_180z);
	myStaticPos_180z.test_Euler();
	myStaticPos_180z.test();

	DynamPosCalc myDynamPos(acc_180z, mag_180z, qStart_180z);

	//Mag地磁倾角
	float mag_n_Inclination = 53*PI/180;
	float mag_n_y = cos(mag_n_Inclination);
	float mag_n_z = sin(mag_n_Inclination);
	mag_n_z = 0-mag_n_z;
	myDynamPos.setMagNyz(mag_n_y,mag_n_z);
	myDynamPos.setPrecision(0.2);
	myDynamPos.test();
	*/
	return 0;
}

