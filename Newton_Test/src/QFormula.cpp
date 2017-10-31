/*
 * QFormula.cpp
 *
 *  Created on: 2016Äê11ÔÂ17ÈÕ
 *      Author: looke
 */
#include "QFormula.h"
#include <iostream>
using namespace std;

QFormula::QFormula()
{
	//matrix = new int[3][3];
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[0][2] = 2;
	matrix[0][3] = 2;


	matrix[1][0] = 3;
	matrix[1][1] = 4;
	matrix[1][2] = 5;
	matrix[1][3] = 5;

	matrix[2][0] = 6;
	matrix[2][1] = 7;
	matrix[2][2] = 8;
	matrix[2][3] = 8;
};

QFormula::QFormula(int initMatrix[3][4])
{
	//matrix = new int[3][3];
	matrix[0][0] = initMatrix[0][0];
	matrix[0][1] = initMatrix[0][1];
	matrix[0][2] = initMatrix[0][2];
	matrix[0][3] = initMatrix[0][3];


	matrix[1][0] = initMatrix[1][0];
	matrix[1][1] = initMatrix[1][1];
	matrix[1][2] = initMatrix[1][2];
	matrix[1][3] = initMatrix[1][3];

	matrix[2][0] = initMatrix[2][0];
	matrix[2][1] = initMatrix[2][1];
	matrix[2][2] = initMatrix[2][2];
	matrix[2][3] = initMatrix[2][3];
};

/*
void QFormula::printMatrix(int (*p) [4])
{
	//int(*mm1)[] = **m;
	//int(*mm2)[] = &m+1;
	//int(*mm3)[] = &m+2;
	//int temp[3][3];
	//temp = p;


	cout << **p << endl;
	cout << *(*p+1) << endl;
	cout << *(*p+2) << endl;

	cout << **(p+1) << endl;
	cout << *(*(p+1)+1) << endl;
	cout << *(*(p+1)+2) << endl;

	cout << **(p+2) << endl;
	cout << *(*(p+2)+1) << endl;
	cout << *(*(p+2)+2) << endl;

	//cout << *(p+2) << endl;
	//cout << *(*m) << endl;
	//cout << *(*m+1) << endl;
	//cout << *(*m+2) << endl;

};
*/
void QFormula::getDericlayMatrix()
{
	//int(*mm1)[] = **m;
	//int(*mm2)[] = &m+1;
	//int(*mm3)[] = &m+2;
	//cout << "123" << endl;
	//cout << *(*m) << endl;
	//cout << *(*m+1) << endl;
	//cout << *(*m+2) << endl;
	cout << "456" << endl;
};

void QFormula::printMatrix(int inputMatrix[][4])
{
	int sizeofoneRow = sizeof(inputMatrix[0]);
	int sizeofMatrix = sizeof(inputMatrix);
	int rowNum = sizeof(inputMatrix)/sizeof(inputMatrix);

	cout << sizeofoneRow << endl;
	cout << sizeofMatrix << endl;
	cout << rowNum << endl;
};

void QFormula::printMatrix()
{
	//print each row
	for(int i=0; i<3; i++)
	cout << this->matrix[0][0];

};
