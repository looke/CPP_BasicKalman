/*
 * DynamPosCalc.cpp
 *
 *  Created on: 2016年11月29日
 *      Author: looke
 */

#include "DynamPosCalc.h"
#include <iostream>

using namespace std;

DynamPosCalc::DynamPosCalc()
{
	// TODO Auto-generated constructor stub

};

DynamPosCalc::DynamPosCalc(float accValue[3], float magValue[3], float qInit[4]):StaticPosCalc(accValue, magValue, qInit)
{

};

void DynamPosCalc::setMagNyz(float mag_N_Y, float mag_N_Z)
{
	this->Mny = mag_N_Y;
	this->Mnz = mag_N_Z;
};

void DynamPosCalc::generateJacobiMatrix()
{
	float temp;
	//calc dF[0][0]
	temp = 2*this->q_value[1];
	this->jacobiMatrix.setMatrixElement(0,0,temp);
	//calc dF[0][1]
	temp = 2*this->q_value[0];
	this->jacobiMatrix.setMatrixElement(0,1,temp);
	//calc dF[0][2]
	temp = 2*this->q_value[3];
	this->jacobiMatrix.setMatrixElement(0,2,temp);
	//calc dF[0][3]
	temp = 2*this->q_value[2];
	this->jacobiMatrix.setMatrixElement(0,3,temp);
	//set dF[0][4]
	this->jacobiMatrix.setMatrixElement(0,4,this->fx[0]);
	//------------------------------------------------------

	//calc dF[1][0]
	temp = 2*this->magValue[0] * this->q_value[0]
	     - 2*this->magValue[1] * this->q_value[3]
	     + 2*this->magValue[2] * this->q_value[2];
	this->jacobiMatrix.setMatrixElement(1,0,temp);

	//calc dF[1][1]
	temp = 2*this->magValue[0] * this->q_value[1]
		 + 2*this->magValue[1] * this->q_value[2]
		 + 2*this->magValue[2] * this->q_value[3];
	this->jacobiMatrix.setMatrixElement(1,1,temp);

	//calc dF[1][2]
	temp = (-2)*this->magValue[0] * this->q_value[2]
         + 2*this->magValue[1] * this->q_value[1]
		 + 2*this->magValue[2] * this->q_value[0];
	this->jacobiMatrix.setMatrixElement(1,2,temp);

	//calc dF[1][3]
	temp = (-2)*this->magValue[0] * this->q_value[3]
		 - 2*this->magValue[1] * this->q_value[0]
		 + 2*this->magValue[2] * this->q_value[1];
	this->jacobiMatrix.setMatrixElement(1,3,temp);

	//set dF[1][4]
	this->jacobiMatrix.setMatrixElement(1,4,this->fx[1]);

	//------------------------------------------------------
	//calc dF[2][0]
	temp = 2*this->magValue[0] * this->q_value[3]
		 + 2*this->magValue[1] * this->q_value[0]
		 - 2*this->magValue[2] * this->q_value[1];
	this->jacobiMatrix.setMatrixElement(2,0,temp);

	//calc dF[2][1]
	temp = 2*this->magValue[0] * this->q_value[2]
		 - 2*this->magValue[1] * this->q_value[1]
		 - 2*this->magValue[2] * this->q_value[0];
	this->jacobiMatrix.setMatrixElement(2,1,temp);

	//calc dF[2][2]
	temp = 2*this->magValue[0] * this->q_value[1]
		 + 2*this->magValue[1] * this->q_value[2]
		 + 2*this->magValue[2] * this->q_value[3];
	this->jacobiMatrix.setMatrixElement(2,2,temp);

	//calc dF[2][3]
	temp = 2*this->magValue[0] * this->q_value[0]
		 - 2*this->magValue[1] * this->q_value[3]
		 + 2*this->magValue[2] * this->q_value[2];
	this->jacobiMatrix.setMatrixElement(2,3,temp);
	//set dF[2][4]
	this->jacobiMatrix.setMatrixElement(2,4,this->fx[2]);

	//------------------------------------------------------
	//calc dF[3][0]
	temp = (-2)*this->magValue[0] * this->q_value[2]
		 + 2*this->magValue[1] * this->q_value[1]
		 + 2*this->magValue[2] * this->q_value[0];
	this->jacobiMatrix.setMatrixElement(3,0,temp);

	//calc dF[3][1]
	temp = 2*this->magValue[0] * this->q_value[3]
		 + 2*this->magValue[1] * this->q_value[0]
		 - 2*this->magValue[2] * this->q_value[1];
	this->jacobiMatrix.setMatrixElement(3,1,temp);

	//calc dF[3][2]
	temp = (-2)*this->magValue[0] * this->q_value[0]
		 + 2*this->magValue[1] * this->q_value[3]
		 - 2*this->magValue[2] * this->q_value[2];
	this->jacobiMatrix.setMatrixElement(3,2,temp);

	//calc dF[3][3]
	temp = 2*this->magValue[0] * this->q_value[1]
		 + 2*this->magValue[1] * this->q_value[2]
		 + 2*this->magValue[2] * this->q_value[3];
	this->jacobiMatrix.setMatrixElement(3,3,temp);
	//set dF[3][4]
	this->jacobiMatrix.setMatrixElement(3,4,this->fx[3]);
	cout<<"Dynamic Pos Jacobi Matrix finished!" << endl;
};

void DynamPosCalc::calcFX()
{
	//使用1个加速计等式，加上3个磁力计等式
	//F[0]
	this->fx[0] = this->calcACC_eq1();
	this->fx[0] = 0-(this->fx[0]);

	//F[1]
	this->fx[1] = this->calcMag_eq0();
	this->fx[1] = 0-(this->fx[1]);

	//F[2]
	this->fx[2] = this->calcMag_eq1();
	this->fx[2] = this->Mny - this->fx[2];
	//this->fx[2] = 0-(this->fx[2]);

	//F[3]
	this->fx[3] = this->calcMag_eq2();
	this->fx[3] = this->Mnz - this->fx[3];
	//this->fx[3] = 0-(this->fx[3]);
	cout<<"Dynamic Pos Fx finished!" << endl;
};
/*
void DynamPosCalc::calcF0()
{
	// 2Q2Q3 + 2Q0Q1 + Ay
	this->fx[0] = 2*this->q_value[2]*this->q_value[3]
				+ 2*this->q_value[0]*this->q_value[1]
				+ this->accValue[1];
};

void DynamPosCalc::calcF1()
{
	// MAGx * (Q0^2 + Q1^2 - Q2^2 - Q3^2)
	float part1 = this->q_value[0]*this->q_value[0]
				+ this->q_value[1]*this->q_value[1]
				- this->q_value[2]*this->q_value[2]
				- this->q_value[3]*this->q_value[3];

	part1 = this->magValue[0] * part1;

	// MAGy * (2Q1Q2 - 2Q0Q3)
	float part2 = 2*this->q_value[1]*this->q_value[2]
				- 2*this->q_value[0]*this->q_value[3];
	part2 = this->magValue[1] * part2;

	// MAGz * (2Q1Q3 + 2Q0Q2)
	float part3 = 2*this->q_value[1]*this->q_value[3]
				+ 2*this->q_value[0]*this->q_value[2];
	part3 = this->magValue[2] * part3;

	this->fx[1] = part1 + part2 + part3;
};

void DynamPosCalc::calcF2()
{
	// MAGx * (2Q1Q2 + 2Q0Q3)
	float part1 = 2*this->q_value[1]*this->q_value[2]
			    + 2*this->q_value[0]*this->q_value[3];
	part1 = this->magValue[0] * part1;

		// MAGy * (Q0^2 - Q1^2 + Q2^2 - Q3^2)
	float part2 = this->q_value[0]*this->q_value[0]
			    - this->q_value[1]*this->q_value[1]
			    + this->q_value[2]*this->q_value[2]
			    - this->q_value[3]*this->q_value[3];
	part2 = this->magValue[1] * part2;

		// MAGz * (2Q2Q3 - 2Q0Q1)
	float part3 = 2*this->q_value[2]*this->q_value[3]
			    - 2*this->q_value[0]*this->q_value[1];
	part3 = this->magValue[2] * part3;

	this->fx[2] = part1 + part2 + part3;
};

void DynamPosCalc::calcF3()
{
	// MAGx * (2Q1Q3 - 2Q0Q2)
	float part1 = 2*this->q_value[1]*this->q_value[3]
			    - 2*this->q_value[0]*this->q_value[2];
	part1 = this->magValue[0] * part1;

	// MAGy * (2Q2Q3 + 2Q0Q1)
	float part2 = 2*this->q_value[2]*this->q_value[3]
			    + 2*this->q_value[0]*this->q_value[1];
	part2 = this->magValue[1] * part2;

		// MAGz * (Q0^2 - Q1^2 - Q2^2 + Q3^2)
	float part3 = this->q_value[0]*this->q_value[0]
			    - this->q_value[1]*this->q_value[1]
			    - this->q_value[2]*this->q_value[2]
			    + this->q_value[3]*this->q_value[3];
	part3 = this->magValue[2] * part3;
	this->fx[3] = part1 + part2 + part3;
};
*/
void DynamPosCalc::calcDynmPos()
{
	//初始化Q值，从初始值开始，迭代计算姿态
	while (!StaticPosCalc::isPrcisionReached())
	{
		//StaticPosCalc::printCurrentQaut();
		//StaticPosCalc::printCurrentDeltaQ();

		this->calcFX();
		this->generateJacobiMatrix();
		StaticPosCalc::calcRootsJacobiMatrix();

		StaticPosCalc::updateDeltaQFromJacobiRoot();
		this->q_value[0] += this->q_deltaValue[0];
		this->q_value[1] += this->q_deltaValue[1];
		this->q_value[2] += this->q_deltaValue[2];
		this->q_value[3] += this->q_deltaValue[3];
	}

};

void DynamPosCalc::test()
{
	//this->calcFX();
	//this->generateJacobiMatrix();
	//this->printJacobiMatrix();
	//this->calcRootsJacobiMatrix();
	//this->updateDeltaQFromJacobiRoot();

	this->calcDynmPos();
	//StaticPosCalc::printCurrentQaut();
	StaticPosCalc::test_Euler();
};
