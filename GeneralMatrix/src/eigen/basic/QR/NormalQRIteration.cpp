/*
 * NormalQRIteration.cpp
 *
 *  Created on: 2017Äê5ÔÂ8ÈÕ
 *      Author: looke
 */

#include "NormalQRIteration.h"
#include <iostream>
using namespace std;

NormalQRIteration::NormalQRIteration()
{

};
NormalQRIteration::NormalQRIteration(BasicMatrix* p_input_OpMatrix)
{
	this->init(p_input_OpMatrix);
};

void NormalQRIteration::QRIteration(int itNumber)
{
	p_HessenbergForm->reload(this->p_OpMatrix);
	p_HessenbergForm->formularUpperHessnbergMatrix();
	this->p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_HessenbergForm->getOpMatrix());
	cout << "QRIteration----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int i=0;
	while (i<itNumber)
	{
		this->p_QRDecomp->reload(p_OpHessenbergMatrix);
		this->p_QRDecomp->calcQRMatrix();
		this->p_QMatrix->copyMatrixElementNoCheck(this->p_QRDecomp->getQMatrix());
		p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_QRDecomp->getRMatrix());

		this->p_Multiplier->reload(p_OpHessenbergMatrix, p_QMatrix);
		this->p_Multiplier->multiplyCalc();
		p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
		cout << "QRIteration----OP Hessenberg Matrix after:" << i << "iteration" <<endl;
		p_OpHessenbergMatrix->printMatrix();
		i++;
	}

};

void NormalQRIteration::init(BasicMatrix* p_input_OpMatrix)
{};
void NormalQRIteration::reload(BasicMatrix* p_input_OpMatrix)
{};
