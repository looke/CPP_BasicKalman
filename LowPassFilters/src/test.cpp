/*
 * test.cpp
 *
 *  Created on: 2016Äê12ÔÂ3ÈÕ
 *      Author: looke
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "LowPassFilter1Order.h"
using namespace std;
int main()
{
	LowPassFilter1Order myLowPassFilter(0.2);
	//myLowPassFilter.resetFilter();
	for(int i=0;i<100;i++)
	{
		cout << myLowPassFilter.apply(2.0) << endl;
	}

	srand((unsigned)time(NULL));
	float temp;
	for(int j=0;j<100;j++)
	{
		temp = rand() / double(RAND_MAX);
		temp = temp + 2;
		cout << "temp:" << temp << endl;
		cout << "Filtered:" << myLowPassFilter.apply(temp) << endl;
	}


	return 1;
}

