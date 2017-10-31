/*
 * MatrixEquationSolver.cpp
 *
 *  Created on: 2017年2月19日
 *      Author: looke
 */

#include "MatrixEquationSolver.h"
#include <iostream>
#include <malloc.h>
#include "math.h"

using namespace std;

MatrixEquationSolver::MatrixEquationSolver(BasicMatrix* input_opMatrix)
{
	this->init(input_opMatrix);
}

void MatrixEquationSolver::init(BasicMatrix* input_opMatrix)
{

};

void MatrixEquationSolver::reload(BasicMatrix* input_opMatrix)
{

};

/**
 *  高斯列主元消元法 换行过程函数
 *  交换矩阵指定两行
 *  from从0行开始
 *
 */
void MatrixEquationSolver::swapRow(int from, int to)
{
	opMatrix.swapRow(from,to);

}

/*
 * 高斯列主元消元法 查找主元所在行过程函数
 *
 * 查找列主元所在行
 *
 * 从startRow指定行开始，查找行号大于等于指定行的列主元，startRow从0开始
 * 返回列主元所在行号
 *
 */
int MatrixEquationSolver::findPivotRow(int startRow)
{
	if(startRow >= this->rowNumber)
	{
		//cout<<"Illegal row number." << endl;
		return -1;
	}
	if(startRow >= this->columnNumber)
	{
		//cout<<"Pivot not exist in this sub matrix" << endl;
		return -1;
	}

	int pivotRow = startRow;
	double maxElement = 0.0;

	for(int i=startRow; i<this->rowNumber; i++)
	{
		if(i >= this->columnNumber)
		{
			break;
		}
		if(fabs(opMatrix.getMatrixElement(i,startRow)) > fabs(maxElement))
		{
			maxElement = opMatrix.getMatrixElement(i,startRow);
			pivotRow = i;
		}
	}

	return pivotRow;

}

/*
 * 高斯列主元消元法 归一化过程函数
 *
 * 归一化指定行，该行应当为列主元所在行
 * 此函数应当在调用findPivotRow找到列主元所在行并将其换到上部以后进行
 *
 * pivotRow从0开始
 */
void MatrixEquationSolver::normalizePivotRow(int pivotRow)
{
	if(pivotRow >= this->rowNumber)
	{
		//cout<<"Illegal row number." << endl;
		return ;
	}
	if(pivotRow >= this->columnNumber)
	{
		//cout<<"Can not normalize sub matrix." << endl;
		//cout<<"PivotRow:" << pivotRow <<endl;
		//cout<<"Column number:" << this->columnNum <<endl;
		return ;
	}

	//取列主元的值作为分母
	double pivotValue = opMatrix.getMatrixElement(pivotRow,pivotRow);

	//判断分母为0的情况
	if(pivotValue == 0)
	{
		//跳过归一化
		return;
	}

	for(int i=pivotRow;i<this->columnNumber;i++)
	{
		opMatrix.setMatrixElement(pivotRow, i, opMatrix.getMatrixElement(pivotRow,i)/pivotValue);
	}
};

/*
 * 高斯列主元消元法 消元过程函数
 *
 * 从指定列主元所在行开始，对其下方的行进行消元
 * 此函数应当在调用行归一化以后进行
 *
 * pivotRow从0开始
 */
void MatrixEquationSolver::eliminateSubMatrix(int pivotRow)

{
	if(pivotRow >= this->rowNumber)
	{
		//cout<<"Illegal row number." << endl;
		return ;
	}
	if(pivotRow >= this->columnNumber)
	{
		//cout<<"Can not eliminate sub matrix." << endl;
		//cout<<"PivotRow:" << pivotRow <<endl;
		//cout<<"Column number:" << this->columnNum <<endl;
		return ;
	}
	for(int i=pivotRow+1;i<this->rowNumber;i++)
	{
		double currentPivotValue = opMatrix.getMatrixElement(i,pivotRow);
		for(int j=pivotRow; j<this->columnNumber; j++)
		{
			//matrixPointer[i][j] = matrixPointer[i][j] - currentPivotValue*matrixPointer[pivotRow][j];
			opMatrix.setMatrixElement(i, j,
					opMatrix.getMatrixElement(i,j) - currentPivotValue*opMatrix.getMatrixElement(pivotRow,j));
		}
	}
};

/*
 * 高斯列主元消元法 转化对角阵过程函数
 *
 * 将矩阵化为对角线主元都为1的上对角阵
 *
 */
void MatrixEquationSolver::gaussElim_ColmnPrin()
{
	int pivotRow;
	for(int i=0; i<this->rowNumber; i++)
	{
		cout << "LOOP:" << i << endl;

		pivotRow = this->findPivotRow(i);
		cout << "PivotRow:" << pivotRow << endl;

		this->swapRow(i, pivotRow);
		cout << "After swap"<< endl;
		this->opMatrix.printMatrix();

		this->normalizePivotRow(i);
		cout << "After Normalization" << endl;
		this->opMatrix.printMatrix();

		this->eliminateSubMatrix(i);
		cout << "After elimination" << endl;
		this->opMatrix.printMatrix();
	}
};

/*
 * 高斯列主元消元法 判断增广阵指定行的元素是否全为0过程函数
 *
 * 判断增广阵指定行的元素是否全为0
 * arguRowNo从0开始
 */
bool MatrixEquationSolver::isAllZeroForArgumentRow(int arguRowNo)
{
	if(arguRowNo >= this->rowNumber)
	{
		//cout << "Illegal input row No." << endl;
		return false;
	}
	int length = this->columnNumber;

	int zeroNumber = 0;

	for(int i=0; i<length; i++)
	{
		if(opMatrix.getMatrixElement(arguRowNo,i) == 0)
		{
			zeroNumber++;
		}
	}

	if(zeroNumber == length)
	{
		return true;
	}
	else
	{
		return false;
	}
};

/*
 * 高斯列主元消元法 判断系数阵指定行的元素是否全为0过程函数
 *
 * 判断系数阵指定行的元素是否全为0
 * coRowNo从0开始
 */
bool MatrixEquationSolver::isAllZeroForCoRow(int coRowNo)
{
	if(coRowNo >= this->rowNumber)
	{
			//cout << "Illegal input row No." << endl;
			return false;
	}
	int length = this->columnNumber-1;

	int zeroNumber = 0;

	for(int i=0; i<length; i++)
	{
		if(opMatrix.getMatrixElement(coRowNo,i) == 0)
		{
			zeroNumber++;
		}
	}

	if(zeroNumber == length)
	{
		return true;
	}
	else
	{
		return false;
	}

};

/*
 * 高斯列主元消元法 系数阵求秩过程函数
 *
 * 计算系数矩阵的秩
 *
 * 必须在消元过程结束后调用
 */
int MatrixEquationSolver::coefficientMatrixRank()
{
	int rank = 0;
	for(int i=0; i<this->rowNumber; i++)
	{
		if(!isAllZeroForCoRow(i))
		{
			rank++;
		}
	}
	return rank;
};

/*
 * 高斯列主元消元法 增广阵求秩过程函数
 *
 * 计算增广矩阵的秩
 *
 * 必须在消元过程结束后调用
 */
int MatrixEquationSolver::augmentedMatrixRank()
{
	int rank = 0;
	for(int i=0; i<this->rowNumber; i++)
	{
		if(!isAllZeroForArgumentRow(i))
		{
			rank++;
		}
	}
	return rank;
};


/*
 * 高斯列主元消元法 求根函数
 *
 * 计算矩阵的根
 *
 * 必须在消元过程结束后调用
 */
void MatrixEquationSolver::calcRoots()
{
	if(this->rowNumber < this->columnNumber-1)
	{
		cout << "Do not have enough row to solve." << endl;
		return;
	}

	int augRank = this->augmentedMatrixRank();
	int coRank = this->coefficientMatrixRank();
	//cout << "Argument Rank of Matrix:" << arguRank << " . Co Rank of Matrix:" << coRank <<endl;
	if(augRank > coRank)
	{
		cout << "No root exist." <<endl;
		return;
	}

	if(augRank == coRank)
	{
		cout << "Only one root exist." <<endl;
	}

	//从最末行开始，对上三角矩阵进行消元，仅保留主对角元素
	for(int i=this->rowNumber-1; i > 0; i--)
	{
		double temp = opMatrix.getMatrixElement(i,columnNumber-1);

		for(int j=i-1; j>=0; j--)
		{
			//matrixPointer[j][this->columnNumber-1] = matrixPointer[j][this->columnNumber-1] - matrixPointer[j][i]*temp;
			opMatrix.setMatrixElement(j, this->columnNumber-1,
					opMatrix.getMatrixElement(j,columnNumber-1) - opMatrix.getMatrixElement(j,i)*temp);
			opMatrix.setMatrixElement(j,i,0);
		}
	}

	for(int i=0; i < rowNumber; i++)
	{
		this->roots[i] = opMatrix.getMatrixElement(i,columnNumber-1);
	}
};

/*
 * 高斯列主元消元法 获取计算结果
 *
 * 获取矩阵的根值
 *
 * 必须在求根过程结束后调用
 */
double* MatrixEquationSolver::getRoots()
{
	return this->roots;
};


/*
 * 高斯列主元消元法 解方程组
 *
 * 求解矩阵方程组
 */
void MatrixEquationSolver::solveMatrixEquation()
{
	this->gaussElim_ColmnPrin();
	this->calcRoots();
};
