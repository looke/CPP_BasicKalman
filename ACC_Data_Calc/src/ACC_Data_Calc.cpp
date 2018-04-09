//============================================================================
// Name        : ACC_Data_Calc.cpp
// Author      : Looke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#define SensitivityOf1G_2GScale  16384
#define SensitivityOf1G_4GScale  8192
#define SensitivityOf1G_8GScale  4096
#define SensitivityOf1G_16GScale 2048
#define ACC_1G 9.8

#include <iostream>
using namespace std;

int main()
{
	double circleDistance = 0.165;
	double gearMotor = 76;
	double gearSensor = 24;
	double lineNumber = 500;

	double timerCLK = 36000000;

	double T1_CLK_Num = 30261;
	double T2_CLK_Num = 42239;

	double lengthUnit = gearMotor*lineNumber/gearSensor;
	lengthUnit = circleDistance / lengthUnit;

	double T1 = T1_CLK_Num/timerCLK;
	double T2 = T2_CLK_Num/timerCLK;

	double speedT1 = lengthUnit/T1;
	double speedT2 = lengthUnit/T2;
	double speedDiff = speedT1 - speedT2;
	double Acc = speedDiff / T2;

	double shiftValue = Acc*SensitivityOf1G_2GScale/ACC_1G;

	cout << "Speed T1:" << endl;
	cout << speedT1 << endl;
	cout << "Speed T2:" << endl;
	cout << speedT2 << endl;
	cout << "ACC:" << endl; // prints !!!Hello World!!!
	cout << Acc << endl;
	cout << "Shift Calc:" << endl;
	cout << shiftValue << endl;

	return 0;
}
