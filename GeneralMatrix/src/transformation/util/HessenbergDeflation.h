/*
 * HessenbergDeflation.h
 *
 *  Created on: 2017Äê6ÔÂ1ÈÕ
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_HESSENBERGDEFLATION_H_
#define TRANSFORMATION_BASIC_HESSENBERGDEFLATION_H_

#include "..\matrix\basic\BasicMatrix.h"
class HessenbergDeflation
{
public:
	HessenbergDeflation();

	bool findNewDeflationPoint(BasicMatrix* p_HessenbergMatrix, int deflationStart, int deflationEnd);

	int getNewDeflationStart();
	int getNewDeflationEnd();
protected:
	int deflateStart_new;
	int deflateEnd_new;
};

#endif /* TRANSFORMATION_BASIC_HESSENBERGDEFLATION_H_ */
