/*
 * HouseholderTransformation.cpp
 *
 *  Created on: 2017��4��24��
 *      Author: looke
 */

#include "HouseholderTransformation.h"
#include <iostream>
using namespace std;
HouseholderTransformation::HouseholderTransformation()
{};

HouseholderTransformation::HouseholderTransformation(BasicVector* p_input_Vector)
{
	this->init(p_input_Vector);
};


void HouseholderTransformation::init(BasicVector* p_input_Vector)
{

};

void HouseholderTransformation::reload(BasicVector* p_input_Vector)
{

};


/*
 * ������������������Householder����ת��Ϊ��һ��Ȼ������e1
 * ���Householder�����Ӧ������Ϊ����������
 * �ҳ�Householder�����Ӧ������Ϊ����������
 */
BasicMatrix* HouseholderTransformation::getHouseholderMatrixToE1(bool isReverseElement)
{
	cout << "Input Vector for Calc Householder matrix---HouseholderMatrixToE1" << endl;
	this->p_HouseholderVector->printVector();

	//int size = this->p_HouseholderVector->getDimension();
	double norm_X = this->p_HouseholderVector->getNormOfVector();
	double X_0 = this->p_HouseholderVector->getElement(0);

	//��ֹԪ�ط�����ͬ��������
	if(X_0 > 0 && isReverseElement)
	{
		norm_X = 0 - norm_X;
	}
	//����X-aE1 (aΪnorm_X)
	this->p_HouseholderVector->setElement(0, X_0-norm_X);
	//���Դ�ӡ
	cout << "Vector U for Calc Householder matrix" << endl;
	this->p_HouseholderVector->printVector();

	generateHouseholderMatrixByVector();
	/*
	double normPower_U = this->p_HouseholderVector->getNormPowerOfVector();
	double temp;
	for(int i=0; i<size; i++)
	{
		for(int j=i; j<size; j++)
		{
			temp = 2*this->p_HouseholderVector->getElement(i) * this->p_HouseholderVector->getElement(j);

			if(0 == normPower_U)
			{
				temp = 0;
			}
			else
			{
				temp = temp/normPower_U;
			}


			if(j == i)
			{
				//�Խ���Ԫ��
				temp = 1 - temp;
			}
			else
			{
				temp = 0 - temp;
			}
			this->p_HouseholderMatrix->setMatrixElement(i,j,temp);
			this->p_HouseholderMatrix->setMatrixElement(j,i,temp);
		}
	}
	*/
	return this->p_HouseholderMatrix;
};

/*
 * ����Householder Vector ��������Householder���� W = I-U*UT
 */
void HouseholderTransformation::generateHouseholderMatrixByVector()
{
	int size = this->p_HouseholderVector->getDimension();
	double normPower_U = this->p_HouseholderVector->getNormPowerOfVector();

	double temp;
	for(int i=0; i<size; i++)
	{
		for(int j=i; j<size; j++)
		{
			temp = 2*this->p_HouseholderVector->getElement(i) * this->p_HouseholderVector->getElement(j);

			if(0 == normPower_U)
			{
				temp = 0;
			}
			else
			{
				temp = temp/normPower_U;
			}


			if(j == i)
			{
				//�Խ���Ԫ��
				temp = 1 - temp;
			}
			else
			{
				temp = 0 - temp;
			}
			this->p_HouseholderMatrix->setMatrixElement(i,j,temp);
			this->p_HouseholderMatrix->setMatrixElement(j,i,temp);
		}
	}
};


/*
 * ������������������Householder����ת��Ϊ��n��Ȼ������en
 * ���Householder�����Ӧ������Ϊ����������
 * �ҳ�Householder�����Ӧ������Ϊ����������
 */
BasicMatrix* HouseholderTransformation::getHouseholderMatrixToEn(bool isReverseElement)
{
	cout << "Input Vector for Calc Householder matrix---HouseholderMatrixToEn" << endl;
	this->p_HouseholderVector->printVector();

	int size = this->p_HouseholderVector->getDimension();
	double norm_X = this->p_HouseholderVector->getNormOfVector();
	double X_n = this->p_HouseholderVector->getElement(size-1);

	//��ֹԪ�ط�����ͬ��������
	if(X_n > 0 && isReverseElement)
	{
		norm_X = 0 - norm_X;
	}
	//����X-aEn (aΪnorm_X)
	this->p_HouseholderVector->setElement(size-1, X_n-norm_X);
	//���Դ�ӡ
	cout << "Vector U for Calc Householder matrix" << endl;
	this->p_HouseholderVector->printVector();

	generateHouseholderMatrixByVector();
	return this->p_HouseholderMatrix;
};
