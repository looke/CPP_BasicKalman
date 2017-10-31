/*
 * DynamicNormalQRIteration.cpp
 *
 *  Created on: 2017Äê5ÔÂ8ÈÕ
 *      Author: looke
 */

#include "DynamicNormalQRIteration.h"

DynamicNormalQRIteration::DynamicNormalQRIteration(BasicMatrix* p_intput_OpMatrix):dMultiplier(p_intput_OpMatrix,p_intput_OpMatrix),QRDecomp(p_intput_OpMatrix),dHessenbergForm(p_intput_OpMatrix)
{
	this->init(p_intput_OpMatrix);
};


void DynamicNormalQRIteration::init(BasicMatrix* p_intput_OpMatrix)
{
	//²Ù×÷¾ØÕó
	this->opMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->opMatrix.copyMatrixElementNoCheck(p_intput_OpMatrix);
	this->p_OpMatrix = &opMatrix;

	//Hessenberg¾ØÕó
	this->opHessenbergMatrix  = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_OpHessenbergMatrix = &opHessenbergMatrix;

	//Q ¾ØÕó
	this->qMatrix = DynamicMatrix(p_intput_OpMatrix->rowNum, p_intput_OpMatrix->columnNum);
	this->p_QMatrix = &qMatrix;

	this->p_Multiplier = &this->dMultiplier;
	this->p_QRDecomp = &this->QRDecomp;
	this->p_HessenbergForm = &this->dHessenbergForm;

};

void DynamicNormalQRIteration::reload(BasicMatrix* p_intput_OpMatrix)
{
	if(this->p_OpMatrix->rowNum == p_intput_OpMatrix->rowNum && this->p_OpMatrix->columnNum == p_intput_OpMatrix->columnNum)
	{
		this->p_OpMatrix->copyMatrixElementNoCheck(p_intput_OpMatrix);
		this->p_OpHessenbergMatrix->resetMatrixToI();
		this->p_QMatrix->resetMatrixToI();
	}
	else
	{
		this->init(p_intput_OpMatrix);
	}
};
