/*
 * DoubleShiftQRIteration.cpp
 *
 *  Created on: 2017��5��17��
 *      Author: looke
 */

#include "DoubleShiftQRIteration.h"
#include <iostream>
using namespace std;

DoubleShiftQRIteration::DoubleShiftQRIteration()
{};

DoubleShiftQRIteration::DoubleShiftQRIteration(BasicMatrix* p_input_OpMatrix)
{
	this->init(p_input_OpMatrix);
};

void DoubleShiftQRIteration::init(BasicMatrix* p_input_OpMatrix)
{};

void DoubleShiftQRIteration::reload(BasicMatrix* p_input_OpMatrix)
{};


/*
 * ����hessenberg��������
 */
void DoubleShiftQRIteration::generateHessenbergOpMatrix()
{
	p_HessenbergForm->reload(this->p_OpMatrix);
	p_HessenbergForm->formularUpperHessnbergMatrix();
	this->p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_HessenbergForm->getOpMatrix());

	this->p_QTMatrix_Implicit_Total->copyMatrixElementNoCheck(p_HessenbergForm->getPreTransMatrix());
	this->p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(p_HessenbergForm->getAfterTransMatrix());
};

/*
 * ����hessenberg�������2x2�Ӿ��� ������������ֵ�ĺ��Լ��˻�
 */
void DoubleShiftQRIteration::generateWilkinsonShift()
{
	int lastRowIndex = this->p_OpHessenbergMatrix->rowNum - 1;

	double An_1n_1 = this->p_OpHessenbergMatrix->getMatrixElement(lastRowIndex-1,lastRowIndex-1);
	double Ann = this->p_OpHessenbergMatrix->getMatrixElement(lastRowIndex,lastRowIndex);

	double An_1n = this->p_OpHessenbergMatrix->getMatrixElement(lastRowIndex-1,lastRowIndex);
	double Ann_1 = this->p_OpHessenbergMatrix->getMatrixElement(lastRowIndex,lastRowIndex-1);

	this->trace = An_1n_1 + Ann;
	this->determinant = An_1n_1*Ann - An_1n*Ann_1;
};

/*
 * B = (A-pI)*(A-tI); ����hessenberg���� ����˫����λ��ľ����һ��
 */
void DoubleShiftQRIteration::generateBMatrixFirstColumn()
{
	generateWilkinsonShift();
	double a11, a12, a21, a22, a32;
	a11 = this->p_OpHessenbergMatrix->getMatrixElement(0,0);
	a12 = this->p_OpHessenbergMatrix->getMatrixElement(0,1);
	a21 = this->p_OpHessenbergMatrix->getMatrixElement(1,0);
	a22 = this->p_OpHessenbergMatrix->getMatrixElement(1,1);
	a32 = this->p_OpHessenbergMatrix->getMatrixElement(2,1);

	this->b11 = a11*a11 - a11*this->trace + this->determinant + a12*a21;
	this->b21 = a21*a11 + a21*a22 -a21*this->trace;
	this->b31 = a21*a32;
};

/*
 * Wilkinsonλ��QR���� ��ʽ ��ʼ��
 */
void DoubleShiftQRIteration::initForWilkinsonImplicitQR()
{
	this->p_QTSubMatrix_Implicit_Step->resetMatrixToI();
	this->p_QSubMatrix_Implicit_Step->resetMatrixToI();


	//����wilkinsonƫ�� trace�Լ�determinant
	//generateWilkinsonShift();

	//hessenberg���� ����˫����λ��ľ����һ��
	generateBMatrixFirstColumn();

	//˫����λ��ľ�����������Ԫ�ع�����Ԫ����
	p_TransVectorForQStep->setElement(0,this->b11);
	p_TransVectorForQStep->setElement(1,this->b21);
	p_TransVectorForQStep->setElement(2,this->b31);

	//����Q1T
	this->p_HouseholderTrans->reload(this->p_TransVectorForQStep);
	p_QTSubMatrix_Implicit_Step->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));

	//����Q1
	this->p_Transposer->reload(p_QTSubMatrix_Implicit_Step);
	this->p_Transposer->transposeMatrix();
	this->p_QSubMatrix_Implicit_Step->copyMatrixElementNoCheck(this->p_Transposer->getTransposeMatrix());

	cout << "initForWilkinsonImplicitQR---Q1T sub" << endl;
	p_QTSubMatrix_Implicit_Step->printMatrix();
	cout << "initForWilkinsonImplicitQR---Q1 sub" << endl;
	p_QSubMatrix_Implicit_Step->printMatrix();

	//���Ӿ���Q ����Ϊȫ�ߴ�Q����
	upgradeQQTSubMatrix(0);

	cout << "initForWilkinsonImplicitQR---Q1T" << endl;
	p_QTMatrix_Implicit_Step->printMatrix();
	cout << "initForWilkinsonImplicitQR---Q1" << endl;
	p_QMatrix_Implicit_Step->printMatrix();

	//��������ת������Q total
	updateTotalQQT();

	//����hessenberg����
	updateHessenbergOpMatrix_IM_QRIteration();
	cout << "initForWilkinsonImplicitQR---Q1T * Hessenberg * Q1" << endl;
	p_OpHessenbergMatrix->printMatrix();
};

/*
 * ��ת���Ӿ���Q ���ݵ�ǰ��������,����Ϊȫ�ߴ�Q����
 */
void DoubleShiftQRIteration::upgradeQQTSubMatrix(int iterateNum)
{
	this->p_QTMatrix_Implicit_Step->resetMatrixToI();
	this->p_QMatrix_Implicit_Step->resetMatrixToI();

	for(int i=0,m=iterateNum; i<p_QSubMatrix_Implicit_Step->rowNum; i++,m++)
	{
		for(int j=0,n=iterateNum; j<p_QSubMatrix_Implicit_Step->columnNum; j++,n++)
		{
			p_QTMatrix_Implicit_Step->setMatrixElement(m,n,p_QTSubMatrix_Implicit_Step->getMatrixElement(i,j));
			p_QMatrix_Implicit_Step->setMatrixElement(m,n,p_QSubMatrix_Implicit_Step->getMatrixElement(i,j));
		}
	}
};

/*
 * ��Qn-1�Ӿ���,����Ϊȫ�ߴ�Q����
 */
void DoubleShiftQRIteration::upgradeQQTLastSubMatrix()
{
	int lastQIndex = p_OpHessenbergMatrix->rowNum-1;

	this->p_QTMatrix_Implicit_Step->resetMatrixToI();
	this->p_QMatrix_Implicit_Step->resetMatrixToI();

	for(int i=0,m=lastQIndex-1; i<p_QSubMatrix_Implicit_LastStep->rowNum; i++,m++)
	{
		for(int j=0,n=lastQIndex-1; j<p_QSubMatrix_Implicit_LastStep->columnNum; j++,n++)
		{
			p_QTMatrix_Implicit_Step->setMatrixElement(m,n,p_QTSubMatrix_Implicit_LastStep->getMatrixElement(i,j));
			p_QMatrix_Implicit_Step->setMatrixElement(m,n,p_QSubMatrix_Implicit_LastStep->getMatrixElement(i,j));
		}
	}
};


/*
 * ��ʽQR���� ����hessenberg��������
 */
void DoubleShiftQRIteration::updateHessenbergOpMatrix_IM_QRIteration()
{
	//����QT * OP-Hessenberg
	this->p_Multiplier->reload(p_QTMatrix_Implicit_Step, p_OpHessenbergMatrix);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//����QT * OP-Hessenberg * Q
	this->p_Multiplier->reload(p_OpHessenbergMatrix, p_QMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

/*
 * Wilkinson˫λ��QR���� ��ʽ(����Ҫ�Ƚ��о���Hessenberg��ʽ����init��reloadʱ�Ѿ����ת��)
 */
void DoubleShiftQRIteration::wilkinson_IM_QRIteration()
{
	//��������ת��ΪHessenberg����
	//this->generateHessenbergOpMatrix();
	cout << "DoubleShiftQRIteration--initForImplicitQR----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int iteratNumber = 10;
	int i = 0;
	while(i < iteratNumber)
	{
		wilkinson_IM_QRIteration_Step();
		i++;
	}
};

/*
 * Wilkinson˫λ��QR���� ��ʽ ��Ϊ�����ӿڵ���ʹ��(����Ҫ�Ƚ��о���Hessenberg��ʽ����init��reloadʱ�Ѿ����ת��)
 */
void DoubleShiftQRIteration::wilkinson_IM_QRIteration_Single()
{

	cout << "DoubleShiftQRIteration--initForImplicitQR----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	this->wilkinson_IM_QRIteration_Step();
};
/*
 * Wilkinson˫λ��QR���� ��ʽ -����
 */
void DoubleShiftQRIteration::wilkinson_IM_QRIteration_Step()
{
	this->p_QTMatrix_Implicit_Total->resetMatrixToI();
	this->p_QMatrix_Implicit_Total->resetMatrixToI();

	initForWilkinsonImplicitQR();

	//chasing bulge
	int bulgeNumber = this->p_OpHessenbergMatrix->columnNum-3;
	for(int j=0; j<bulgeNumber; j++)
	{
		//������ʽQ��QT
		double a1,a2,a3;
		a1 = this->p_OpHessenbergMatrix->getMatrixElement(j+1,j);
		a2 = this->p_OpHessenbergMatrix->getMatrixElement(j+2,j);
		a3 = this->p_OpHessenbergMatrix->getMatrixElement(j+3,j);

		this->p_TransVectorForQStep->setElement(0,a1);
		this->p_TransVectorForQStep->setElement(1,a2);
		this->p_TransVectorForQStep->setElement(2,a3);

		//����Q1T
		this->p_HouseholderTrans->reload(this->p_TransVectorForQStep);
		p_QTSubMatrix_Implicit_Step->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));

		//����Q1
		this->p_Transposer->reload(p_QTSubMatrix_Implicit_Step);
		this->p_Transposer->transposeMatrix();
		this->p_QSubMatrix_Implicit_Step->copyMatrixElementNoCheck(this->p_Transposer->getTransposeMatrix());

		cout << "wilkinson_IM_QRIteration_Step---QiT:" << j <<endl;
		p_QTSubMatrix_Implicit_Step->printMatrix();
		cout << "wilkinson_IM_QRIteration_Step---Qi:" <<  j <<endl;
		p_QSubMatrix_Implicit_Step->printMatrix();

		//���Ӿ���Q ����Ϊȫ�ߴ�Q����
		upgradeQQTSubMatrix(j+1);
		cout << "wilkinson_IM_QRIteration_Step---QiT" << j <<endl;
		p_QTMatrix_Implicit_Step->printMatrix();
		cout << "wilkinson_IM_QRIteration_Step---Qi" << j <<endl;
		p_QMatrix_Implicit_Step->printMatrix();

		//��������ת������Q total
		updateTotalQQT();

		//����hessenberg����
		updateHessenbergOpMatrix_IM_QRIteration();
		cout << "wilkinson_IM_QRIteration_Step---QiT * Hessenberg * Qi" << endl;
		p_OpHessenbergMatrix->printMatrix();
	}

	endForWilkinsonImplicitQR();
};

/*
 * Wilkinsonλ��QR���� ��ʽ ��β���һ�ε���
 */
void DoubleShiftQRIteration::endForWilkinsonImplicitQR()
{
	int lastQIndex = p_OpHessenbergMatrix->rowNum-1;
	//������ʽQ��QT
	double an1,an2;
	an1 = this->p_OpHessenbergMatrix->getMatrixElement(lastQIndex-1,lastQIndex-2);
	an2 = this->p_OpHessenbergMatrix->getMatrixElement(lastQIndex,lastQIndex-2);

	this->p_TransVectorForQ_LastStep->setElement(0,an1);
	this->p_TransVectorForQ_LastStep->setElement(1,an2);

	this->p_GivensTrans->reload(p_TransVectorForQ_LastStep);
	this->p_QTSubMatrix_Implicit_LastStep->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixPreMultiple(1));

	this->p_Transposer->reload(p_QTSubMatrix_Implicit_LastStep);
	this->p_Transposer->transposeMatrix();
	this->p_QSubMatrix_Implicit_LastStep->copyMatrixElementNoCheck(this->p_Transposer->getTransposeMatrix());

	cout << "endForWilkinsonImplicitQR---Qn_1T Sub:" <<endl;
	p_QTSubMatrix_Implicit_LastStep->printMatrix();
	cout << "endForWilkinsonImplicitQR---Qn_1 Sub:" << endl;
	p_QSubMatrix_Implicit_LastStep->printMatrix();

	//���Ӿ�������Ϊȫ�ߴ�ת������
	upgradeQQTLastSubMatrix();
	cout << "endForWilkinsonImplicitQR---Qn_1T" <<endl;
	p_QTMatrix_Implicit_Step->printMatrix();
	cout << "endForWilkinsonImplicitQR---Qn_1" << endl;
	p_QMatrix_Implicit_Step->printMatrix();

	//��������ת������Q total
	updateTotalQQT();

	//����hessenberg����
	updateHessenbergOpMatrix_IM_QRIteration();
	cout << "endForWilkinsonImplicitQR---Qn_1T * Hessenberg * Qn_1" << endl;
	p_OpHessenbergMatrix->printMatrix();
};

/*
 * ��������ת������Q QT
 */
void DoubleShiftQRIteration::updateTotalQQT()
{
	//����QT_Step * QT_Total
	this->p_Multiplier->reload(p_QTMatrix_Implicit_Step, p_QTMatrix_Implicit_Total);
	this->p_Multiplier->multiplyCalc();
	this->p_QTMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//����Q_Total * Q_Step
	this->p_Multiplier->reload(p_QMatrix_Implicit_Total, p_QMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

BasicMatrix* DoubleShiftQRIteration::getOpHessenbergMatrix()
{
	return this->p_OpHessenbergMatrix;
};

//��ȡ����ת������
BasicMatrix* DoubleShiftQRIteration::getQTMatrix_Total()
{
	return this->p_QTMatrix_Implicit_Total;
};

BasicMatrix* DoubleShiftQRIteration::getQMatrix_Total()
{
	return this->p_QMatrix_Implicit_Total;
};
