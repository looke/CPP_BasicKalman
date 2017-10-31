/*
 * HessenbergFormular.cpp
 *
 *  Created on: 2017��5��8��
 *      Author: looke
 */

#include "HessenbergFormular.h"
#include "iostream"
using namespace std;

HessenbergFormular::HessenbergFormular()
{};

HessenbergFormular::HessenbergFormular(BasicMatrix* p_InputOpMatrix)
{
	this->init(p_InputOpMatrix);
};

/*
 * Hessenberg��ʽ��
 *
 */
void HessenbergFormular::formularUpperHessnbergMatrix()
{
	this->p_preTransMatrix->resetMatrixToI();
	this->p_afterTransMatrix->resetMatrixToI();

	if(this->p_OpMatrix->isUpperHessenbergMatrix())
	{
		return;
	}
	for(int i=0; i<this->p_OpMatrix->columnNum-2; i++)
	{
		generateSubHouseholderTrans(i);
		upgradeSubHouseholderTrans(i);
		updateOpMatrix();
		updatePreTransMatrix();
		updateAfterTransMatrix();
	}
};

//���ݵ�ǰ����  ��ʼ���ӱ任����
//void HessenbergFormular::initSubHouseholderTrans(int iterateNum)
//{
//	int rowAndColumnNumber = this->p_OpMatrix->rowNum - iterateNum;
//	this->resizeSubMatrix(rowAndColumnNumber);
//};

/*
 * ���ݵ�ǰ��������,�����Ӿ����ά��,����任�Ӿ���
 */
void HessenbergFormular::generateSubHouseholderTrans(int iterateNum)
{
	//��ʼ���任�Ӿ���
	int rowAndColumnNumber = this->p_OpMatrix->rowNum - iterateNum -1;
	this->resizeSubMatrix(rowAndColumnNumber);

	BasicVector* p_hesseColumnVector = this->p_OpMatrix->getSubMatrixHessenColumnVector(iterateNum);
	cout << "generateSubHouseholderTrans-----Current Hessen Vector:" << endl;
	p_hesseColumnVector->printVector();

	this->p_HouseholderTrans->reload(p_hesseColumnVector);
	this->p_subTransMatrix->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));

	cout << "generateSubHouseholderTrans-----Sub trans matrix for iterate:" << iterateNum <<endl;
	this->p_subTransMatrix->printMatrix();

};


/*
 * ���ӱ任��������Ϊȫά�ȱ任��
 * ���ݵ�ǰ��������,�����Ӿ����ά��,���任�Ӿ�������
 */
void HessenbergFormular::upgradeSubHouseholderTrans(int iterateNum)
{
	p_transMatrix->resetMatrixToI();

	int startIndex = iterateNum+1;
	int subTransMatrixRowColumnNumber = this->p_OpMatrix->rowNum - startIndex;

	double temp;
	for(int i=0; i<subTransMatrixRowColumnNumber; i++)
	{
		for(int j=0; j<subTransMatrixRowColumnNumber;j++)
		{
			temp = this->p_subTransMatrix->getMatrixElement(i,j);
			this->p_transMatrix->setMatrixElement(startIndex+i,startIndex+j,temp);
		}
	}
	cout << "upgradeSubHouseholderTrans-----Complete trans matrix for iterate:" << iterateNum <<endl;
	this->p_transMatrix->printMatrix();
};

/*
 * ������˱任����
 */
void HessenbergFormular::updatePreTransMatrix()
{
	this->p_Multiplier->reload(this->p_transMatrix, this->p_preTransMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_preTransMatrix->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());

	cout << "updatePreTransMatrix-----Pre trans matrix for total" << endl;
	this->p_preTransMatrix->printMatrix();

};

/*
 * �����ҳ˱任����
 */
void HessenbergFormular::updateAfterTransMatrix()
{
	this->p_Multiplier->reload(this->p_afterTransMatrix, this->p_transMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_afterTransMatrix->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());

	cout << "updateAfterTransMatrix-----After trans matrix for total" << endl;
	this->p_afterTransMatrix->printMatrix();
};

/*
 * ���²�������  pre*OP*after
 */
void HessenbergFormular::updateOpMatrix()
{
	this->p_Multiplier->reload(this->p_transMatrix, this->p_OpMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_OpMatrix->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
	cout << "updateOpMatrix-----OP matrix pre tans" << endl;
	this->p_OpMatrix->printMatrix();

	this->p_Multiplier->reload(this->p_OpMatrix, this->p_transMatrix);
	this->p_Multiplier->multiplyCalc();
	this->p_OpMatrix->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());

	cout << "updateOpMatrix-----OP matrix after tans" << endl;
	this->p_OpMatrix->printMatrix();
};

BasicMatrix* HessenbergFormular::getOpMatrix()
{
	return this->p_OpMatrix;
};

BasicMatrix* HessenbergFormular::getPreTransMatrix()
{
	return this->p_preTransMatrix;
};

BasicMatrix* HessenbergFormular::getAfterTransMatrix()
{
	return this->p_afterTransMatrix;
};

BasicMatrix* HessenbergFormular::getTransMatrix()
{
	return this->p_transMatrix;
};

BasicMatrix* HessenbergFormular::getSubTransMatrix()
{
	return this->p_subTransMatrix;
};

void HessenbergFormular::init(BasicMatrix* p_InputOpMatrix)
{};
void HessenbergFormular::reload(BasicMatrix* p_InputOpMatrix)
{};
void HessenbergFormular::resizeSubMatrix(int rowAndColumnNumber)
{};
