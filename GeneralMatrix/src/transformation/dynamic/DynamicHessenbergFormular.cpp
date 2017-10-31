/*
 * DynamicHessenbergFormular.cpp
 *
 *  Created on: 2017Äê5ÔÂ8ÈÕ
 *      Author: looke
 */


#include "DynamicHessenbergFormular.h"

//DynamicHessenbergFormular::DynamicHessenbergFormular()
//{};

DynamicHessenbergFormular::DynamicHessenbergFormular(BasicMatrix* p_InputOpMatrix):dMultiplier(p_InputOpMatrix,p_InputOpMatrix),dHouseholderTrans()
{
	this->init(p_InputOpMatrix);
};

void DynamicHessenbergFormular::init(BasicMatrix* p_InputOpMatrix)
{
	opMatrix = DynamicMatrix(p_InputOpMatrix->rowNum, p_InputOpMatrix->columnNum);
	opMatrix.copyMatrixElementNoCheck(p_InputOpMatrix);
	this->p_OpMatrix = &opMatrix;

	preTransMatrix = DynamicMatrix(p_InputOpMatrix->rowNum, p_InputOpMatrix->columnNum);
	this->p_preTransMatrix = &preTransMatrix;

	afterTransMatrix = DynamicMatrix(p_InputOpMatrix->rowNum, p_InputOpMatrix->columnNum);
	this->p_afterTransMatrix = &afterTransMatrix;

	transMatrix = DynamicMatrix(p_InputOpMatrix->rowNum, p_InputOpMatrix->columnNum);
	this->p_transMatrix = &transMatrix;

	subTransMatrix = DynamicMatrix(p_InputOpMatrix->rowNum, p_InputOpMatrix->columnNum);
	this->p_subTransMatrix = &subTransMatrix;

	this->p_HouseholderTrans = &dHouseholderTrans;
	this->p_Multiplier = &dMultiplier;
};
void DynamicHessenbergFormular::reload(BasicMatrix* p_InputOpMatrix)
{
	if(this->p_OpMatrix->rowNum == p_InputOpMatrix->rowNum && this->p_OpMatrix->columnNum == p_InputOpMatrix->columnNum)
	{
		this->p_OpMatrix->copyMatrixElementNoCheck(p_InputOpMatrix);
		this->p_preTransMatrix->resetMatrixToI();
		this->p_afterTransMatrix->resetMatrixToI();
		this->p_transMatrix->resetMatrixToI();
		this->p_subTransMatrix->resetMatrixToI();
	}
	else
	{
		this->init(p_InputOpMatrix);
	}

};

void DynamicHessenbergFormular::resizeSubMatrix(int rowAndColumnNumber)
{
	this->subTransMatrix = 	DynamicMatrix(rowAndColumnNumber,rowAndColumnNumber);
	this->p_subTransMatrix = &subTransMatrix;
};

