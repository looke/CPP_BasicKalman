/*
 * MatrixCholeskyDecomposition.cpp
 *
 *  Created on: 2017��3��18��
 *      Author: looke
 */
#include <iostream>
#include "math.h"
#include <cmath>
#include "MatrixCholeskyDecomposition.h"
using namespace std;

//MatrixCholeskyDecomposition::MatrixCholeskyDecomposition()
//{};
/*
 * ��ʼ�� Cholesky�ֽ�
 */
MatrixCholeskyDecomposition::MatrixCholeskyDecomposition(BasicMatrix* input_opMatrix)
{

	this->init(input_opMatrix);
};
/*
void MatrixCholeskyDecomposition::init(BasicMatrix* input_opMatrix)
{};

void MatrixCholeskyDecomposition::reload(BasicMatrix* input_opMatrix)
{};
*/
/*
 * ǰ������Ϊ�������Գ�����ʵ������
 *
 * ʵ��Chelosky�ֽ⣬����������ֽ�Ϊ�����Ǿ���
 * �ӵ�һ�п�ʼ����Chelosky�ֽ����ÿһ�дӶԽ�����Ԫ��ʼ����
 *
 * ���ȼ�����ǰλԪ�صĶ�Ӧ�˻�֮�ͣ��ٸ��ݸ������Խ�Ԫ����Chelosky�ֽ��Ԫ��ֵ
 */
void MatrixCholeskyDecomposition::generateDecompositionMatrix()
{

	int i=0; //��ʶ��ǰ���ڼ������
	int j=0; //��ʶ��ǰ���ڼ������
	int k=0; //��ʶ��ǰ���ڼ������ǰλԪ

	double preElementSum = 0; //ǰλԪ�س˻���
	double tempResult = 0;	//��������ʱ����

	for(i=0; i<this->rowNumber; i++)
	{
		for(j=i; j<this->columnNumber; j++)
		{
			preElementSum = 0;
			//������ǰλԪ�صĳ˻���
			for(k=i-1; k>=0; k--)
			{
				//preElementSum += this->decompMatrixPointer[k][i]*this->decompMatrixPointer[k][j];
				preElementSum += p_DecompositionMatrix->getMatrixElement(k,i) * p_DecompositionMatrix->getMatrixElement(k,j);
			}

			//��⵱ǰԪ��ֵ
			//tempResult = this->opMatrixPointer[i][j] - preElementSum;
			tempResult = this->p_opMatrix->getMatrixElement(i,j) - preElementSum;

			//���Խ�Ԫ��ʱ�����ÿ�������
			if(i == j)
			{
				tempResult = sqrt(tempResult);
			}
			else //�����Խ�Ԫ��ʱ ���ó�������
			{
				//tempResult = tempResult / this->decompMatrixPointer[i][i];
				tempResult = tempResult / p_DecompositionMatrix->getMatrixElement(i,i);
			}
			//���½�����
			this->p_DecompositionMatrix->setMatrixElement(i,j,tempResult);
		}

		cout << "Current Decomposition:" << endl;
		this->p_DecompositionMatrix->printMatrix();
		cout << "----------------------" << endl;
	}
};


void MatrixCholeskyDecomposition::printDecompositionMatrix()
{
	this->p_DecompositionMatrix->printMatrix();
};
void MatrixCholeskyDecomposition::printOpMatrix()
{
	this->p_opMatrix->printMatrix();
};

BasicMatrix* MatrixCholeskyDecomposition::getDecompositionMatrix()
{
	return this->p_DecompositionMatrix;
};
