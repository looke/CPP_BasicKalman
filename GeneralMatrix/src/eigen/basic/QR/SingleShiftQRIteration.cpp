/*
 * SingelShiftQRIteration.cpp
 *
 *  Created on: 2017��5��13��
 *      Author: looke
 */

#include "..\eigen\basic\QR\SingleShiftQRIteration.h"
#include <iostream>
using namespace std;

SingleShiftQRIteration::SingleShiftQRIteration()
{};

SingleShiftQRIteration::SingleShiftQRIteration(BasicMatrix* p_input_OpMatrix)
{
	this->init(p_input_OpMatrix);
};

void SingleShiftQRIteration::init(BasicMatrix* p_input_OpMatrix)
{};
void SingleShiftQRIteration::reload(BasicMatrix* p_input_OpMatrix)
{};

/*
 * ����hessenberg��������
 */
void SingleShiftQRIteration::generateHessenbergOpMatrix()
{
	p_HessenbergForm->reload(this->p_OpMatrix);
	p_HessenbergForm->formularUpperHessnbergMatrix();
	this->p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_HessenbergForm->getOpMatrix());

	this->p_QTMatrix_Implicit_Total->copyMatrixElementNoCheck(p_HessenbergForm->getPreTransMatrix());
	this->p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(p_HessenbergForm->getAfterTransMatrix());
};


/*
 * ��ֵλ��QR���� ��ʽ
 */
void SingleShiftQRIteration::explicit_QRIteration(double input_shiftValue)
{
	int iterationNumber = 10;

	//this->generateHessenbergOpMatrix();
	cout << "SingelShiftQRIteration--explicit_QRIteration----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int i=0;
	while (i<iterationNumber)
	{
		explicit_QRIteration_Step(input_shiftValue);
		cout << "SingelShiftQRIteration--explicit_QRIteration----OP Hessenberg Matrix after:" << i << "iteration" <<endl;
		p_OpHessenbergMatrix->printMatrix();
		i++;
	}
};

//��ֵλ��QR���� ��ʽ����
void SingleShiftQRIteration::explicit_QRIteration_Step(double input_shiftValue)
{
	//�Խ�Ԫ��ȥ�ƶ�ֵ
	p_OpHessenbergMatrix->diagonalSubtraction(input_shiftValue);
	cout << "SingelShiftQRIteration--explicit_QRIteration_Step----OP Hessenberg Matrix after Subtraction" <<endl;
	p_OpHessenbergMatrix->printMatrix();

	this->p_QRDecomp->reload(p_OpHessenbergMatrix);
	this->p_QRDecomp->calcQRMatrix();
	this->p_QMatrix_Explicit->copyMatrixElementNoCheck(this->p_QRDecomp->getQMatrix());
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_QRDecomp->getRMatrix());

	cout << "SingelShiftQRIteration--explicit_QRIteration_Step----OP Hessenberg Matrix after QRDecomp" <<endl;
	p_OpHessenbergMatrix->printMatrix();

	this->p_Multiplier->reload(p_OpHessenbergMatrix, p_QMatrix_Explicit);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());

	cout << "SingelShiftQRIteration--explicit_QRIteration_Step----OP Hessenberg Matrix after R*Q" <<endl;
	p_OpHessenbergMatrix->printMatrix();
	//�Խ�Ԫ�����ƶ�ֵ
	p_OpHessenbergMatrix->diagonalAddition(input_shiftValue);
	cout << "SingelShiftQRIteration--explicit_QRIteration_Step----OP Hessenberg Matrix after Addition" <<endl;
	p_OpHessenbergMatrix->printMatrix();
};

//��ֵλ��QR���� ��ʽ ��ʼ��
void SingleShiftQRIteration::initForImplicitQR(double input_shiftValue)
{
	this->p_QTMatrix_Implicit_Step->resetMatrixToI();
	this->p_QMatrix_Implicit_Step->resetMatrixToI();
	//������λ
	double temp_old = this->p_OpHessenbergMatrix->getMatrixElement(0,0);
	double temp_new = temp_old - input_shiftValue;
	this->p_OpHessenbergMatrix->setMatrixElement(0,0,temp_new);

	//������ʽQ��QT
	BasicVector* p_firstColumnVector = this->p_OpHessenbergMatrix->getColumnVector(0);
	p_GivensTrans->reload(p_firstColumnVector);

	this->p_QTMatrix_Implicit_Step->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixPreMultiple(1));
	this->p_Transposer->reload(p_QTMatrix_Implicit_Step);
	this->p_Transposer->transposeMatrix();
	this->p_QMatrix_Implicit_Step->copyMatrixElementNoCheck(this->p_Transposer->getTransposeMatrix());

	cout << "SingelShiftQRIteration--initForImplicitQR----QTMatrix_Implicit_Step" <<endl;
	p_QTMatrix_Implicit_Step->printMatrix();
	cout << "SingelShiftQRIteration--initForImplicitQR----QMatrix_Implicit_Step" <<endl;
	p_QMatrix_Implicit_Step->printMatrix();
	//��ԭHessenberg����
	this->p_OpHessenbergMatrix->setMatrixElement(0,0,temp_old);

	//����Hessenberg����
	this->updateHessenbergOpMatrix_IM_QRIteration();
	cout << "SingelShiftQRIteration--initForImplicitQR----QTMatrix_Implicit_Total" <<endl;
	p_QTMatrix_Implicit_Total->printMatrix();
	cout << "SingelShiftQRIteration--initForImplicitQR----QMatrix_Implicit_Total" <<endl;
	p_QMatrix_Implicit_Total->printMatrix();

	//��������ת������Q QT
	this->updateQQTMatrix_Total_IM_QRIteration();
	cout << "SingelShiftQRIteration--initForImplicitQR----QTMatrix_Implicit_Total" <<endl;
	p_QTMatrix_Implicit_Total->printMatrix();
	cout << "SingelShiftQRIteration--initForImplicitQR----QMatrix_Implicit_Total" <<endl;
	p_QMatrix_Implicit_Total->printMatrix();
	//�˴��Ѿ��γ���ʽ����QR�����ĳ�ʼ����������
	cout << "SingelShiftQRIteration--initForImplicitQR----OP Hessenberg Matrix after init"<<endl;
	p_OpHessenbergMatrix->printMatrix();
};

//��ʽQR���� ����hessenberg��������
void SingleShiftQRIteration::updateHessenbergOpMatrix_IM_QRIteration()
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

//��ֵλ��QR���� ��ʽ
void SingleShiftQRIteration::implicit_QRIteration(double input_shiftValue)
{
	//��������ת��ΪHessenberg����
	//this->generateHessenbergOpMatrix();
	cout << "SingelShiftQRIteration--initForImplicitQR----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int iteratNumber = 10;
	int i = 0;
	while(i < iteratNumber)
	{
		implicit_QRIteration_Step(input_shiftValue);
		cout << "SingelShiftQRIteration--implicit_QRIteration----OP Hessenberg Matrix after: " << i << " iteration" <<endl;
		p_OpHessenbergMatrix->printMatrix();
		i++;
	}
};

//��ֵλ��QR���� ��ʽ
void SingleShiftQRIteration::implicit_QRIteration_Step(double input_shiftValue)
{
	//p_QTMatrix_Implicit_Total->resetMatrixToI();
	//p_QMatrix_Implicit_Total->resetMatrixToI();
	initForImplicitQR(input_shiftValue);

	int bulgeNumber = this->p_OpHessenbergMatrix->columnNum-2;
	for(int j=0; j<bulgeNumber; j++)
	{
		//������ʽQ��QT
		BasicVector* p_columnVector = this->p_OpHessenbergMatrix->getColumnVector(j);
		p_GivensTrans->reload(p_columnVector);

		this->p_QTMatrix_Implicit_Step->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixPreMultiple(j+2));
		this->p_Transposer->reload(p_QTMatrix_Implicit_Step);
		this->p_Transposer->transposeMatrix();
		this->p_QMatrix_Implicit_Step->copyMatrixElementNoCheck(this->p_Transposer->getTransposeMatrix());

		//����Hessenberg����
		this->updateHessenbergOpMatrix_IM_QRIteration();

		//��������ת������Q QT
		this->updateQQTMatrix_Total_IM_QRIteration();
	}
};

/*
 * ������λ��QR���� ��ʽ
 */
void SingleShiftQRIteration::rayleigh_Quotient_EX_QRIteration()
{
	int iterationNumber = 10;

	//this->generateHessenbergOpMatrix();
	cout << "SingelShiftQRIteration--rayleigh_Quotient_EX_QRIteration----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int rayleighValueIndex = p_OpHessenbergMatrix->rowNum - 1;
	double rayleighValue;
	int i=0;
	while (i<iterationNumber)
	{
		rayleighValue = p_OpHessenbergMatrix->getMatrixElement(rayleighValueIndex,rayleighValueIndex);
		explicit_QRIteration_Step(rayleighValue);
		cout << "SingelShiftQRIteration--rayleigh_Quotient_EX_QRIteration----OP Hessenberg Matrix after:" << i << "iteration" <<endl;
		p_OpHessenbergMatrix->printMatrix();
		i++;
	}
};

//������λ��QR���� ��ʽ 10�ε���
void SingleShiftQRIteration::rayleigh_Quotient_IM_QRIteration()
{
	this->rayleigh_Quotient_IM_QRIteration(10);
}

//������λ��QR���� ��ʽ ָ����������
void SingleShiftQRIteration::rayleigh_Quotient_IM_QRIteration(int iterateNum)
{
	int iterationNumber = iterateNum;

	//this->generateHessenbergOpMatrix();
	cout << "SingelShiftQRIteration--rayleigh_Quotient_IM_QRIteration----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int rayleighValueIndex = p_OpHessenbergMatrix->rowNum - 1;
	double rayleighValue;
	int i=0;
	while (i<iterationNumber)
	{
		rayleighValue = p_OpHessenbergMatrix->getMatrixElement(rayleighValueIndex,rayleighValueIndex);
		implicit_QRIteration_Step(rayleighValue);
		cout << "SingelShiftQRIteration--rayleigh_Quotient_IM_QRIteration----OP Hessenberg Matrix after:" << i << "iteration" <<endl;
		p_OpHessenbergMatrix->printMatrix();
		i++;
	}
};

//������λ��QR���� ��ʽ ����-ÿ�ε��������¼���Totalת�þ���
void SingleShiftQRIteration::rayleigh_Quotient_IM_QRIteration_Step()
{
	//this->generateHessenbergOpMatrix();
	cout << "SingelShiftQRIteration--rayleigh_Quotient_IM_QRIteration Step----OP Hessenberg Matrix" << endl;
	this->p_OpHessenbergMatrix->printMatrix();

	int rayleighValueIndex = p_OpHessenbergMatrix->rowNum - 1;
	double rayleighValue= p_OpHessenbergMatrix->getMatrixElement(rayleighValueIndex,rayleighValueIndex);

	p_QTMatrix_Implicit_Total->resetMatrixToI();
	p_QMatrix_Implicit_Total->resetMatrixToI();
	implicit_QRIteration_Step(rayleighValue);
	cout << "SingelShiftQRIteration--rayleigh_Quotient_IM_QRIteration Step----OP Hessenberg Matrix" <<endl;
	p_OpHessenbergMatrix->printMatrix();
};

/*
 * �����ۺ�ת������Q QT Total
 */
void SingleShiftQRIteration::updateQQTMatrix_Total_IM_QRIteration()
{
	//��������ۺϾ��� QT_Step * QT_Total
	this->p_Multiplier->reload(p_QTMatrix_Implicit_Step, p_QTMatrix_Implicit_Total);
	this->p_Multiplier->multiplyCalc();
	p_QTMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//�����ҳ��ۺϾ��� Q_Total * Q_Step
	this->p_Multiplier->reload(p_QMatrix_Implicit_Total, p_QMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

BasicMatrix* SingleShiftQRIteration::getOpHessenbergMatrix()
{
	return this->p_OpHessenbergMatrix;
};

/*
 * ��ȡ����ת������ QT
 */
BasicMatrix* SingleShiftQRIteration::getQTMatrix_Total()
{
	return this->p_QTMatrix_Implicit_Total;
};

/*
 * ��ȡ����ת������ Q
 */
BasicMatrix* SingleShiftQRIteration::getQMatrix_Total()
{
	return this->p_QMatrix_Implicit_Total;
};
