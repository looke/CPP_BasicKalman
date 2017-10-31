/*
 * DynamPosCalc.h
 *
 *  Created on: 2016Äê11ÔÂ29ÈÕ
 *      Author: looke
 */

#ifndef DYNAMPOSCALC_H_
#define DYNAMPOSCALC_H_

#include "StaticPosCalc.h"

class DynamPosCalc: public StaticPosCalc
{
public:
	DynamPosCalc();
	DynamPosCalc(float accValue[3], float magValue[3], float qInit[4]);
	void setMagNyz(float mag_N_Y, float mag_N_Z);

	void generateJacobiMatrix();
	void calcFX();


	void calcDynmPos();
	void test();
};

#endif /* DYNAMPOSCALC_H_ */
