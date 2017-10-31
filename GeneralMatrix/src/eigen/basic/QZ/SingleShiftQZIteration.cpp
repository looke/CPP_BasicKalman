/*
 * SingleShiftQZIteration.cpp
 *
 *  Created on: 2017��5��27��
 *      Author: looke
 */

#include "SingleShiftQZIteration.h"
#include <iostream>
using namespace std;

SingleShiftQZIteration::SingleShiftQZIteration()
{};

SingleShiftQZIteration::SingleShiftQZIteration(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{
	this->init(p_intput_OpMatrix_A,p_intput_OpMatrix_B);
};

void SingleShiftQZIteration::init(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{

};

void SingleShiftQZIteration::reload(BasicMatrix* p_intput_OpMatrix_A, BasicMatrix* p_intput_OpMatrix_B)
{

};


/*
 * ����H-T���������
 */
void SingleShiftQZIteration::generateHessenTriangleOpMatrix()
{
	this->p_HessenbergTriangleFormular->reload(p_OpMatrix_A, p_OpMatrix_B);
	this->p_HessenbergTriangleFormular->formularABMatrix();
	this->p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getHessenbergMatrixA());
	this->p_OpMatrix_Triangle->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getTriangleMatrixB());

	cout << "SingleShiftQZIteration--generateHessenTriangleOpMatrix----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "SingleShiftQZIteration--generateHessenTriangleOpMatrix----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * ʹ��Q�������H-T�����
 */
void SingleShiftQZIteration::updateHTMatrixByQ()
{
	cout << "SingleShiftQZIteration--updateHTMatrixByQ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "SingleShiftQZIteration--updateHTMatrixByQ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//���¾���Hessenberg A
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_OpMatrix_Hessenberg);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Triangle B
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_OpMatrix_Triangle);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "SingleShiftQZIteration--updateHTMatrixByQ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "SingleShiftQZIteration--updateHTMatrixByQ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * ʹ��Z�����ҳ�H-T�����
 */
void SingleShiftQZIteration::updateHTMatrixByZ()
{
	cout << "SingleShiftQZIteration--updateHTMatrixByZ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "SingleShiftQZIteration--updateHTMatrixByZ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//���¾���Hessenberg A
	this->p_Multiplier->reload(p_OpMatrix_Hessenberg, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Triangle B
	this->p_Multiplier->reload(p_OpMatrix_Triangle, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "SingleShiftQZIteration--updateHTMatrixByZ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "SingleShiftQZIteration--updateHTMatrixByZ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * �����ۺ�ת������Q/Z Total(��Step�ϲ���Total)
 */
void SingleShiftQZIteration::updateQZMatrix_Total()
{
	//���¾���Q total
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_QMatrix_Implicit_Total);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Z total
	this->p_Multiplier->reload(p_ZMatrix_Implicit_Total, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_ZMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

/*
 * ��ʼ����ʽ����
 * ִ����ʽ������һ������H-T����ԵĴζԽ������γ�һ��ͻ����λ
 */
void SingleShiftQZIteration::initForImplicitQZ(double input_ShiftValue)
{
	cout << "SingleShiftQZIteration--initForImplicitQZ" << endl;
	p_QMatrix_Implicit_Step->resetMatrixToI();
	p_ZMatrix_Implicit_Step->resetMatrixToI();

	//QZ������λ A*B^-1 ��һ��
	double temp_old_a00 = this->p_OpMatrix_Hessenberg->getMatrixElement(0,0);
	double temp_old_a10 = this->p_OpMatrix_Hessenberg->getMatrixElement(1,0);

	double temp_old_b00 = this->p_OpMatrix_Triangle->getMatrixElement(0,0);


	double temp_new_a00 = temp_old_a00/temp_old_b00 - input_ShiftValue;
	double temp_new_a10 = temp_old_a10/temp_old_b00;

	//���µ�һ��
	this->p_OpMatrix_Hessenberg->setMatrixElement(0,0,temp_new_a00);
	this->p_OpMatrix_Hessenberg->setMatrixElement(1,0,temp_new_a10);

	//������ʽQ
	BasicVector* p_firstColumnVector = this->p_OpMatrix_Hessenberg->getColumnVector(0);
	p_GivensTrans->reload(p_firstColumnVector);
	this->p_QMatrix_Implicit_Step->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixPreMultiple(1));

	//��ԭHessenberg����
	this->p_OpMatrix_Hessenberg->setMatrixElement(0,0,temp_old_a00);
	this->p_OpMatrix_Hessenberg->setMatrixElement(1,0,temp_old_a10);

	//����H-T�����
	this->updateHTMatrixByQ();

	//������ʽZ
	BasicVector* p_secondRowVector = this->p_OpMatrix_Triangle->getRowVector(1);
	p_GivensTrans->reload(p_secondRowVector);
	this->p_ZMatrix_Implicit_Step->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixAfterMultiple(0));

	//����H-T�����
	this->updateHTMatrixByZ();

	//�����ۺ�ת������Q\Z Total
	updateQZMatrix_Total();

	cout << "SingleShiftQZIteration--initForImplicitQZ-----END" << endl;

};

//��ֵλ��QZ���� ��ʽ����
void SingleShiftQZIteration::implicit_QZIteration_Step(double input_shiftValue)
{
	p_QMatrix_Implicit_Total->resetMatrixToI();
	p_ZMatrix_Implicit_Total->resetMatrixToI();

	this->initForImplicitQZ(input_shiftValue);

	int bulgeNumber = this->p_OpMatrix_Hessenberg->columnNum-2;

	for(int j=0; j<bulgeNumber; j++)
	{
		//������ʽQ
		BasicVector* p_columnVector = this->p_OpMatrix_Hessenberg->getColumnVector(j);
		p_GivensTrans->reload(p_columnVector);
		this->p_QMatrix_Implicit_Step->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixPreMultiple(j+2));
		//����H-T�����
		this->updateHTMatrixByQ();

		//������ʽZ
		BasicVector* p_secondRowVector = this->p_OpMatrix_Triangle->getRowVector(j+2);
		p_GivensTrans->reload(p_secondRowVector);
		this->p_ZMatrix_Implicit_Step->copyMatrixElementNoCheck(p_GivensTrans->getGivensMatrixAfterMultiple(j+1));
		//����H-T�����
		this->updateHTMatrixByZ();

		//�����ۺ�ת������Q\Z Total
		updateQZMatrix_Total();
	}

};

//��ֵλ��QZ���� ��ʽ
void SingleShiftQZIteration::implicit_QZIteration(double input_shiftValue)
{
	//generateHessenTriangleOpMatrix();
	int i=0;
	while (i<10)
	{
		implicit_QZIteration_Step(input_shiftValue);
		cout << "SingleShiftQZIteration--implicit_QZIteration----OP Hessenberg Matrix after:" << i << "iteration" <<endl;
		p_OpMatrix_Hessenberg->printMatrix();
		i++;
	}
};
//��ֵrayleigh��λ��QZ���� ��ʽ
void SingleShiftQZIteration::rayleigh_Quotient_IM_QZIteration(int iterateNum)
{
	//generateHessenTriangleOpMatrix();

	int rayleighValueIndex = p_OpMatrix_Hessenberg->rowNum - 1;
	double rayleighValue;
	int i=0;
	while (i<iterateNum)
	{
		rayleighValue = p_OpMatrix_Hessenberg->getMatrixElement(rayleighValueIndex,rayleighValueIndex);
		implicit_QZIteration_Step(rayleighValue);
		//cout << "SingleShiftQZIteration--rayleigh_Quotient_IM_QRIteration----OP Hessenberg Matrix after:" << i << "iteration" <<endl;
		//p_OpMatrix_Hessenberg->printMatrix();
		i++;
	}
};

//��ֵrayleigh��λ��QZ���� ��ʽ ����
void SingleShiftQZIteration::rayleigh_Quotient_IM_QZIteration_Step()
{
	//����A*B^-1 ���½�Ԫ�� ��Ϊ����λ��ֵ
	p_ABInvCalc->generateABinvLastOne(p_OpMatrix_Hessenberg, p_OpMatrix_Triangle);
	double rayleighValue = p_ABInvCalc->getABinv_N_N();

	implicit_QZIteration_Step(rayleighValue);
};

//��ȡQ ����ת������
BasicMatrix* SingleShiftQZIteration::getQMatrix_Total()
{
	return this->p_QMatrix_Implicit_Total;
};

//��ȡZ ����ת������
BasicMatrix* SingleShiftQZIteration::getZMatrix_Total()
{
	return this->p_ZMatrix_Implicit_Total;
};
