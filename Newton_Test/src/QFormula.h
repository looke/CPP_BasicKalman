/*
 * QFormula.h
 *
 *  Created on: 2016Äê11ÔÂ17ÈÕ
 *      Author: looke
 */

//#ifndef QFORMULA_H_
//#define QFORMULA_H_

class QFormula
{
public:
	QFormula();
	QFormula(int initMatrix[3][4]);

	void getDericlayMatrix();

	//void printMatrix(int (*p) [4]);
	void printMatrix(int matrix[][4]);
	void printMatrix();

private:
	int matrix[3][4];

};

//#endif /* QFORMULA_H_ */
