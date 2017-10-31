/*
 * DoubleShiftQZIteration.cpp
 *
 *  Created on: 2017��5��30��
 *      Author: looke
 */

#include "DoubleShiftQZIteration.h"
#include <iostream>
using namespace std;

DoubleShiftQZIteration::DoubleShiftQZIteration()
{};

DoubleShiftQZIteration::DoubleShiftQZIteration(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	this->init(p_input_OpMatrix_A, p_input_OpMatrix_B);
};

void DoubleShiftQZIteration::init(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{};

void DoubleShiftQZIteration::reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{};

//����H-T���������
void DoubleShiftQZIteration::generateHessenTriangleOpMatrix()
{
	this->p_HessenbergTriangleFormular->reload(p_OpMatrix_A, p_OpMatrix_B);
	this->p_HessenbergTriangleFormular->formularABMatrix();
	this->p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getHessenbergMatrixA());
	this->p_OpMatrix_Triangle->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getTriangleMatrixB());

	cout << "DoubleShiftQZIteration--generateHessenTriangleOpMatrix----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--generateHessenTriangleOpMatrix----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * ����A*B^-1 �������2x2�Ӿ��� ��������Wilkinson��λ��trace & determinant
 */
void DoubleShiftQZIteration::generateWilkinsonShift()
{
	//���� A*B^-1 ���2x2�Ӿ���
	p_ABInvCalc->generateABinvLast2x2(p_OpMatrix_Hessenberg,p_OpMatrix_Triangle);

	double ABinv_n_1_n_1 = p_ABInvCalc->getABinv_N_1_N_1();
	double ABinv_n_n = p_ABInvCalc->getABinv_N_N();
	double ABinv_n_1_n = p_ABInvCalc->getABinv_N_1_N();
	double ABinv_n_n_1 = p_ABInvCalc->getABinv_N_N_1();

	this->trace = ABinv_n_1_n_1 + ABinv_n_n;
	this->determinant = ABinv_n_1_n_1*ABinv_n_n - ABinv_n_1_n*ABinv_n_n_1;
};

/*
 * ���� A*B^-1 ǰ����Ԫ��
 */
void DoubleShiftQZIteration::generateABinvFirst3x2()
{
	p_ABInvCalc->generateABinvFirst3x2(p_OpMatrix_Hessenberg, p_OpMatrix_Triangle);
	this->ABinv_11 = p_ABInvCalc->getABinv11();
	this->ABinv_12 = p_ABInvCalc->getABinv12();
	this->ABinv_21 = p_ABInvCalc->getABinv21();
	this->ABinv_22 = p_ABInvCalc->getABinv22();
	this->ABinv_32 = p_ABInvCalc->getABinv32();
};

/*
 * ���� A*B^-1 ˫����λ�� ��һ��Ԫ��
 */
void DoubleShiftQZIteration::generateABinvShiftedFirstColumn()
{
	generateABinvFirst3x2();
	generateWilkinsonShift();
	this->C11 = ABinv_11*ABinv_11 - ABinv_11*this->trace + this->determinant + ABinv_12*ABinv_21;
	this->C21 = ABinv_21*ABinv_11 + ABinv_21*ABinv_22 -ABinv_21*this->trace;
	this->C31 = ABinv_21*ABinv_32;
};

/*
 * ���ݵ�ǰ�������ȣ��������Ǿ������Ͳ�λ��Ԫ��
 */
void DoubleShiftQZIteration::generateTriangleBulgeElement(int iterateNum)
{
	int startPosition = iterateNum+1;
	this->B_21 = p_OpMatrix_Triangle->getMatrixElement(startPosition+1,startPosition);
	this->B_22 = p_OpMatrix_Triangle->getMatrixElement(startPosition+1,startPosition+1);
	this->B_31 = p_OpMatrix_Triangle->getMatrixElement(startPosition+2,startPosition);
	this->B_32 = p_OpMatrix_Triangle->getMatrixElement(startPosition+2,startPosition+1);
	this->B_33 = p_OpMatrix_Triangle->getMatrixElement(startPosition+2,startPosition+2);
};

/*
 * ��Q�Ӿ�����ݵ�ǰ��������,����Ϊȫ�ߴ�Q����
 */
void DoubleShiftQZIteration::upgradeQSubMatrix(int iterateNum)
{
	this->p_QMatrix_Implicit_Step->resetMatrixToI();
	int startPosition = iterateNum+1;

	cout << "DoubleShiftQZIteration--upgradeQSubMatrix----Before Update" << endl;
	p_QSubMatrix_Implicit_Step_3->printMatrix();

	for(int i=0,m=startPosition; i<p_QSubMatrix_Implicit_Step_3->rowNum; i++,m++)
	{
		for(int j=0,n=startPosition; j<p_QSubMatrix_Implicit_Step_3->columnNum; j++,n++)
		{
			p_QMatrix_Implicit_Step->setMatrixElement(m,n,p_QSubMatrix_Implicit_Step_3->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeQSubMatrix----After Update" << endl;
	p_QMatrix_Implicit_Step->printMatrix();
};

/*
 * ��Z�Ӿ�����ݵ�ǰ��������,����Ϊȫ�ߴ�Z����
 */
void DoubleShiftQZIteration::upgradeZSubMatrix(int iterateNum)
{
	this->p_ZMatrix_Implicit_Step->resetMatrixToI();
	int startPosition = iterateNum+1;

	cout << "DoubleShiftQZIteration--upgradeZSubMatrix----Before Update" << endl;
	p_ZSubMatrix_Implicit_Step_3->printMatrix();

	for(int i=0,m=startPosition; i<p_ZSubMatrix_Implicit_Step_3->rowNum; i++,m++)
	{
		for(int j=0,n=startPosition; j<p_ZSubMatrix_Implicit_Step_3->columnNum; j++,n++)
		{
			p_ZMatrix_Implicit_Step->setMatrixElement(m,n,p_ZSubMatrix_Implicit_Step_3->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeZSubMatrix----After Update" << endl;
	p_ZMatrix_Implicit_Step->printMatrix();
};
/*
 * ��2x2 Q�Ӿ�������Ϊ 3x3 Q�Ӿ��� 2x2λ������
 */
void DoubleShiftQZIteration::upgradeQMiniToSubMatrix_RightEnd()
{
	p_QSubMatrix_Implicit_Step_3->resetMatrixToI();

	cout << "DoubleShiftQZIteration--upgradeQMiniToSubMatrix_RightEnd----Before Update" << endl;
	p_QSubMatrix_Implicit_Step_2->printMatrix();

	for(int i=0; i<p_QSubMatrix_Implicit_Step_2->rowNum;i++)
	{
		for(int j=0; j<p_QSubMatrix_Implicit_Step_2->columnNum;j++)
		{
			p_QSubMatrix_Implicit_Step_3->setMatrixElement(i+1, j+1, p_QSubMatrix_Implicit_Step_2->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeQMiniToSubMatrix_RightEnd----After Update" << endl;
	p_QSubMatrix_Implicit_Step_3->printMatrix();
};

/*
 * ��2x2 Z�Ӿ�������Ϊ 3x3 Z�Ӿ��� 2x2λ������
 */
void DoubleShiftQZIteration::upgradeZMiniToSubMatrix_RightEnd()
{
	p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_RightEnd----Before Update" << endl;
	p_ZSubMatrix_Implicit_Step_2->printMatrix();

	for(int i=0; i<p_ZSubMatrix_Implicit_Step_2->rowNum;i++)
	{
		for(int j=0; j<p_ZSubMatrix_Implicit_Step_2->columnNum;j++)
		{
			p_ZSubMatrix_Implicit_Step_3->setMatrixElement(i+1, j+1, p_ZSubMatrix_Implicit_Step_2->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_RightEnd----After Update" << endl;
	p_ZSubMatrix_Implicit_Step_3->printMatrix();
};

/*
 * ��2x2 Z�Ӿ�������Ϊ 3x3 Z�Ӿ��� 2x2λ������
 */
void DoubleShiftQZIteration::upgradeZMiniToSubMatrix_LeftTop()
{
	p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_LeftTop----Before Update" << endl;
	p_ZSubMatrix_Implicit_Step_2->printMatrix();

	for(int i=0; i<p_ZSubMatrix_Implicit_Step_2->rowNum;i++)
	{
		for(int j=0; j<p_ZSubMatrix_Implicit_Step_2->columnNum;j++)
		{
			p_ZSubMatrix_Implicit_Step_3->setMatrixElement(i, j, p_ZSubMatrix_Implicit_Step_2->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_LeftTop----After Update" << endl;
	p_ZSubMatrix_Implicit_Step_3->printMatrix();

};

/*
 * ʹ��Q�����ҳ�H-T�����
 */
void DoubleShiftQZIteration::updateHTMatrixByQ()
{
	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//���¾���Hessenberg A
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_OpMatrix_Hessenberg);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Triangle B
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_OpMatrix_Triangle);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};


/*
 * ʹ��Z�����ҳ�H-T�����
 */
void DoubleShiftQZIteration::updateHTMatrixByZ()
{
	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//���¾���Hessenberg A
	this->p_Multiplier->reload(p_OpMatrix_Hessenberg, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Triangle B
	this->p_Multiplier->reload(p_OpMatrix_Triangle, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * �����ۺ�ת������Q Total(��Step�ϲ���Total)
 */
void DoubleShiftQZIteration::updateQMatrix_Total()
{
	//���¾���Q total
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_QMatrix_Implicit_Total);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

/*
 * �����ۺ�ת������Z Total(��Step�ϲ���Total)
 */
void DoubleShiftQZIteration::updateZMatrix_Total()
{
	//���¾���Z total
	this->p_Multiplier->reload(p_ZMatrix_Implicit_Total, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_ZMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

//Wilkinsonλ��QZ���� ��ʽ ��ʼ��
void DoubleShiftQZIteration::initForWilkinsonImplicitQZ()
{
	//Qi �Ӿ��� ��ʽ���� �ֲ� Qi�������OP���� 3x3
	p_QSubMatrix_Implicit_Step_3->resetMatrixToI();

	//Zi �Ӿ��� ��ʽ���� �ֲ� QTi�����ҳ�OP���� 3x3
	p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();
	//Zi �Ӿ��� ��ʽ���� �ֲ� QT�����ҳ�OP���� 2x2
	p_ZSubMatrix_Implicit_Step_2->resetMatrixToI();

	//��������A*B^-1 ˫����λ��ĵ�һ��
	generateABinvShiftedFirstColumn();

	//˫����λ��ľ�����������Ԫ�ع�����Ԫ����
	p_TransVectorForQStep_3->setElement(0,this->C11);
	p_TransVectorForQStep_3->setElement(1,this->C21);
	p_TransVectorForQStep_3->setElement(2,this->C31);

	//����Qת������3ά�Ӿ���
	this->p_HouseholderTrans->reload(this->p_TransVectorForQStep_3);
	p_QSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));
	//Q�Ӿ�������
	upgradeQSubMatrix(-1);
	//Q��˸���HT�����
	updateHTMatrixByQ();
	//��������ת������Q Total
	updateQMatrix_Total();


	//�������ȼ���Zת������3ά�Ӿ���
	//���ڼ�����ʽ˫��QZ��������ת������Zi������---3ά
	generateTriangleBulgeElement(-1);
	p_TransVectorForZStep_3->setElement(0,this->B_31);
	p_TransVectorForZStep_3->setElement(1,this->B_32);
	p_TransVectorForZStep_3->setElement(2,this->B_33);
	this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_3);
	p_ZSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
	//Z�Ӿ�������
	upgradeZSubMatrix(-1);
	//Z�ҳ˸���HT�����
	updateHTMatrixByZ();
	//��������ת������Z Total
	updateZMatrix_Total();

	//��μ���Zת������2ά�Ӿ���
	//���ڼ�����ʽ˫��QZ��������ת������Zi������---2ά
	generateTriangleBulgeElement(-1);
	p_TransVectorForZStep_2->setElement(0,this->B_21);
	p_TransVectorForZStep_2->setElement(1,this->B_22);
	this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_2);
	p_ZSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
	//2ά�任��������Ϊ3ά
	upgradeZMiniToSubMatrix_LeftTop();
	//Z�Ӿ�������
	upgradeZSubMatrix(-1);
	//Z�ҳ˸���HT�����
	updateHTMatrixByZ();
	//��������ת������Z Total
	updateZMatrix_Total();

	//����Z������¹���Triangle-B����Ӧ���ָ������Ǹ�ʽ

	cout << "initForWilkinsonImplicitQZ---Q * Hessenberg * Z" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "initForWilkinsonImplicitQZ---Q * Triangle * Z" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * Wilkinsonλ��QZ���� ��ʽ ���ֵ���
 */
void DoubleShiftQZIteration::wilkinson_IM_QZIteration_Step()
{
	//����Q\Z ����ת������
	this->p_QMatrix_Implicit_Total->resetMatrixToI();
	this->p_ZMatrix_Implicit_Total->resetMatrixToI();
	//��ʼ������һ��
	initForWilkinsonImplicitQZ();

	//���Ͳ�������
	int bulgeNumber = this->p_OpMatrix_Hessenberg->columnNum - 3;

	for(int j=0; j<bulgeNumber; j++)
	{
		//������ʽQ
		double a1,a2,a3;
		a1 = this->p_OpMatrix_Hessenberg->getMatrixElement(j+1,j);
		a2 = this->p_OpMatrix_Hessenberg->getMatrixElement(j+2,j);
		a3 = this->p_OpMatrix_Hessenberg->getMatrixElement(j+3,j);

		//˫����λ��ľ�����������Ԫ�ع�����Ԫ����
		p_TransVectorForQStep_3->setElement(0,a1);
		p_TransVectorForQStep_3->setElement(1,a2);
		p_TransVectorForQStep_3->setElement(2,a3);

		//����Qת������3ά�Ӿ���
		this->p_HouseholderTrans->reload(this->p_TransVectorForQStep_3);
		p_QSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));
		//Q�Ӿ�������
		upgradeQSubMatrix(j);
		//Q��˸���HT�����
		updateHTMatrixByQ();
		//��������ת������Q Total
		updateQMatrix_Total();

		//�������ȼ���Zת������3ά�Ӿ���
		//���ڼ�����ʽ˫��QZ��������ת������Zi������---3ά
		generateTriangleBulgeElement(j);
		p_TransVectorForZStep_3->setElement(0,this->B_31);
		p_TransVectorForZStep_3->setElement(1,this->B_32);
		p_TransVectorForZStep_3->setElement(2,this->B_33);
		this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_3);
		p_ZSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
		//Z�Ӿ�������
		upgradeZSubMatrix(j);
		//Z�ҳ˸���HT�����
		updateHTMatrixByZ();
		//��������ת������Z Total
		updateZMatrix_Total();

		//��μ���Zת������2ά�Ӿ���
		//���ڼ�����ʽ˫��QZ��������ת������Zi������---2ά
		generateTriangleBulgeElement(j);
		p_TransVectorForZStep_2->setElement(0,this->B_21);
		p_TransVectorForZStep_2->setElement(1,this->B_22);
		this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_2);
		p_ZSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
		//2ά�任��������Ϊ3ά
		upgradeZMiniToSubMatrix_LeftTop();
		//Z�Ӿ�������
		upgradeZSubMatrix(j);
		//Z�ҳ˸���HT�����
		updateHTMatrixByZ();
		//��������ת������Z Total
		updateZMatrix_Total();

		//����Z������¹���Triangle-B����Ӧ���ָ������Ǹ�ʽ
		cout << "wilkinson_IM_QZIteration_Step---Q * Hessenberg * Z" << endl;
		this->p_OpMatrix_Hessenberg->printMatrix();
		cout << "wilkinson_IM_QZIteration_Step---Q * Triangle * Z" << endl;
		this->p_OpMatrix_Triangle->printMatrix();
	}

	endForWilkinsonImplicitQZ();
};

/*
 * Wilkinson˫λ��QZ���� ��ʽ -��β���һ������
 */
void DoubleShiftQZIteration::endForWilkinsonImplicitQZ()
{
	int lastQIndex = p_OpMatrix_Hessenberg->rowNum-1;
	//������ʽQ
	double an1,an2;
	an1 = this->p_OpMatrix_Hessenberg->getMatrixElement(lastQIndex-1,lastQIndex-2);
	an2 = this->p_OpMatrix_Hessenberg->getMatrixElement(lastQIndex,lastQIndex-2);

	p_TransVectorForQStep_2->setElement(0,an1);
	p_TransVectorForQStep_2->setElement(1,an2);
	this->p_HouseholderTrans->reload(this->p_TransVectorForQStep_2);
	p_QSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));
	//2ά�任��������Ϊ3ά
	upgradeQMiniToSubMatrix_RightEnd();
	//Q�Ӿ�������Ϊȫά��
	upgradeQSubMatrix(lastQIndex-3);
	//Q��˸���HT�����
	updateHTMatrixByQ();
	//��������ת������Q Total
	updateQMatrix_Total();

	//������ʽ Z
	double bn1,bn2;
	bn1 = this->p_OpMatrix_Triangle->getMatrixElement(lastQIndex,lastQIndex-1);
	bn2 = this->p_OpMatrix_Triangle->getMatrixElement(lastQIndex,lastQIndex);
	p_TransVectorForZStep_2->setElement(0,bn1);
	p_TransVectorForZStep_2->setElement(1,bn2);
	this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_2);
	p_ZSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
	//2ά�任��������Ϊ3ά
	upgradeZMiniToSubMatrix_RightEnd();
	//Z�Ӿ�������Ϊȫά��
	upgradeZSubMatrix(lastQIndex-3);
	//Z�ҳ˸���HT�����
	updateHTMatrixByZ();
	//��������ת������Z Total
	updateZMatrix_Total();

	//����QZ������¹���H-Triangle ����Ӧ���ָ�H-T��ʽ
	cout << "endForWilkinsonImplicitQZ---Q * Hessenberg * Z" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "endForWilkinsonImplicitQZ---Q * Triangle * Z" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

};

/*
 * Wilkinsonλ��QZ���� ��ʽ ���ֵ�������ӿ� (����Ҫ�Բ����������H-T��ʽ�� init/reloadʱ�Ѿ����H-T��ʽ��)
 */
void DoubleShiftQZIteration::wilkinson_IM_QZIteration_Single()
{
	//��������ת��ΪHessenberg����
	//this->generateHessenTriangleOpMatrix();
	cout << "DoubleShiftQZIteration--initForImplicitQR----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--initForImplicitQR----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
	wilkinson_IM_QZIteration_Step();
};

/*
 * Wilkinsonλ��QZ���� ��ʽ 10���������� (����Ҫ�Բ����������H-T��ʽ�� init/reloadʱ�Ѿ����H-T��ʽ��)
 */
void DoubleShiftQZIteration::wilkinson_IM_QZIteration()
{
	//��������ת��ΪHessenberg-Triangle����
	//this->generateHessenTriangleOpMatrix();
	cout << "DoubleShiftQZIteration--H-T Format----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--H-T Format----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	int iteratNumber = 100;
	int i = 0;
	while(i < iteratNumber)
	{
		wilkinson_IM_QZIteration_Step();
		i++;
	}
};

BasicMatrix* DoubleShiftQZIteration::getQMatrix_Total()
{
	return this->p_QMatrix_Implicit_Total;
};

BasicMatrix* DoubleShiftQZIteration::getZMatrix_Total()
{
	return this->p_ZMatrix_Implicit_Total;
};
