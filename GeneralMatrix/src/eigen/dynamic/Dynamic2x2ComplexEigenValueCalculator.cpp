/*
 * Dynamic2x2ComplexEigenValueCalculator.cpp
 *
 *  Created on: 2017Äê6ÔÂ3ÈÕ
 *      Author: looke
 */

#include "..\eigen\dynamic\Dynamic2x2ComplexEigenValueCalculator.h"
#include "math.h"
#include "iostream"
using namespace std;
Dynamic2x2ComplexEigenValueCalculator::Dynamic2x2ComplexEigenValueCalculator()
{
	this->opMatrix_2x2 = DynamicMatrix(2,2);

};

void Dynamic2x2ComplexEigenValueCalculator::printEigenValue(BasicMatrix* input_OpMatrix_2x2)
{
	opMatrix_2x2.copyMatrixElementNoCheck(input_OpMatrix_2x2);

	double a,b,c,d,realPart,complexPart;
	a = this->opMatrix_2x2.getMatrixElement(0,0);
	b = this->opMatrix_2x2.getMatrixElement(0,1);
	c = this->opMatrix_2x2.getMatrixElement(1,0);
	d = this->opMatrix_2x2.getMatrixElement(1,1);

	realPart = 0.5*a + 0.5*d;
	complexPart = 0.5*a + 0.5*d;
	complexPart = complexPart*complexPart;
	complexPart = complexPart-a*d + b*c;

	if(complexPart < 0)
	{
		complexPart = 0 - complexPart;
		complexPart = sqrt(complexPart);

		cout << realPart <<"+"<<complexPart<<"i" << endl;
		cout << realPart <<"-"<<complexPart<<"i" << endl;
	}
	else
	{
		complexPart = sqrt(complexPart);
		cout << realPart + complexPart << endl;
		cout << realPart - complexPart << endl;
	}


};
