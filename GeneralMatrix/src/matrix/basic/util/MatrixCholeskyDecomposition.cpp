/*
 * MatrixCholeskyDecomposition.cpp
 *
 *  Created on: 2017年3月18日
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
 * 初始化 Cholesky分解
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
 * 前提条件为输入矩阵对称正定实数矩阵
 *
 * 实现Chelosky分解，将操作矩阵分解为上三角矩阵
 * 从第一行开始计算Chelosky分解矩阵，每一行从对角线主元开始计算
 *
 * 首先计算列前位元素的对应乘积之和，再根据该行主对角元素求Chelosky分解的元素值
 */
void MatrixCholeskyDecomposition::generateDecompositionMatrix()
{

	int i=0; //标识当前正在计算的行
	int j=0; //标识当前正在计算的列
	int k=0; //标识当前正在计算的列前位元

	double preElementSum = 0; //前位元素乘积和
	double tempResult = 0;	//解算结果临时变量

	for(i=0; i<this->rowNumber; i++)
	{
		for(j=i; j<this->columnNumber; j++)
		{
			preElementSum = 0;
			//求解各个前位元素的乘积和
			for(k=i-1; k>=0; k--)
			{
				//preElementSum += this->decompMatrixPointer[k][i]*this->decompMatrixPointer[k][j];
				preElementSum += p_DecompositionMatrix->getMatrixElement(k,i) * p_DecompositionMatrix->getMatrixElement(k,j);
			}

			//求解当前元素值
			//tempResult = this->opMatrixPointer[i][j] - preElementSum;
			tempResult = this->p_opMatrix->getMatrixElement(i,j) - preElementSum;

			//主对角元素时，采用开方运算
			if(i == j)
			{
				tempResult = sqrt(tempResult);
			}
			else //非主对角元素时 采用除法运算
			{
				//tempResult = tempResult / this->decompMatrixPointer[i][i];
				tempResult = tempResult / p_DecompositionMatrix->getMatrixElement(i,i);
			}
			//更新解算结果
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
