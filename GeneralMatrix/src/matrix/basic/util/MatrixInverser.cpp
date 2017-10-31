/*
 * MatrixInverser.cpp
 *
 *  Created on: 2017年2月27日
 *      Author: looke
 */

#include "MatrixInverser.h"
#include <iostream>
using namespace std;

MatrixInverser::MatrixInverser(BasicMatrix* input_opMatrix)
{
	this->isFullRank = false;
	this->isSquareMatrix = false;
	this->init(input_opMatrix);
};

/*
 * 	初始化各项参数、矩阵
 */
void MatrixInverser::init(BasicMatrix* opMatrix)
{

};
/*
 * 重新装填操作矩阵，初始化各项参数
 * 避免重新申请对象
 */
void MatrixInverser::reload(BasicMatrix* opMatrix)
{

};

/*
 * 打印逆矩阵
 */
void MatrixInverser::printInverseMatrix()
{
	this->p_inverseMatrix->printMatrix();
};

void MatrixInverser::printOpMatrix()
{
	this->p_operateMatrix->printMatrix();
};



/*
 * 生成逆矩阵
 * 初等行列式变换
 */
void MatrixInverser::generateInverseMatrix()
{
	//非方阵不进行求逆矩阵操作
	if(!this->isSquareMatrix)
	{
		return;
	}
	cout << "Start Invers" << endl;


	//对操作矩阵进行归一化以及消元 伴随矩阵同步操作
	for(int i=0; i<this->rowNumber; i++)
	{
		this->unZeroPivotRow(i);
		this->normalizePivotRow(i);
		this->eliminateSubMatrix(i);
		cout << "After normalize and sub eliminate: " << i << endl;
		this->p_operateMatrix->printMatrix();
		cout << "-----------------------" << endl;
		this->p_inverseMatrix->printMatrix();
	}



	for(int i=this->rowNumber-1; i>0; i--)
	{
		this->eliminateUpperMatrix(i);
		cout << "After up eliminate: " << i << endl;
		this->p_operateMatrix->printMatrix();
		cout << "-----------------------" << endl;
		this->p_inverseMatrix->printMatrix();
	}

	//判断是否满秩
	int rank = 0;
	for(int i=0; i<this->rowNumber; i++)
	{
		if(0 != this->p_operateMatrix->getMatrixElement(i,i))
		{
			rank++;
		}
	}
	if(rank == this->rowNumber)
	{
		this->isFullRank = true;
	}

};

/*
 * 判断指定行的对角线主元是否为0,若为0则交换到其他主元非0行
 *
 */
void MatrixInverser::unZeroPivotRow(int pivotRow)
{
	//首先对矩阵进行整理,避免首对角线主元为0
	if(0 == this->p_operateMatrix->getMatrixElement(pivotRow,pivotRow))
	{
		int i=pivotRow;
		while(i<this->rowNumber)
		{
			if(0 != this->p_operateMatrix->getMatrixElement(i,pivotRow))
			{
				break;
			}
			i++;
		}
		this->p_operateMatrix->swapRow(0,i);
		this->p_inverseMatrix->swapRow(0,i);
	}
	cout << "After swap" << endl;
	this->p_operateMatrix->printMatrix();
	cout << "-----------------------" << endl;
	this->p_inverseMatrix->printMatrix();
};


/*
 * 归一化指定行，该行应当为列主元所在行
 *
 * 同时也会处理协矩阵
 * pivotRow从0开始
 */
void MatrixInverser::normalizePivotRow(int pivotRow)
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
	//double pivotValue = this->opMatrixPointer[pivotRow][pivotRow];
	double pivotValue = this->p_operateMatrix->getMatrixElement(pivotRow, pivotRow);
	//判断分母为0的情况
	if(pivotValue == 0)
	{
		//跳过归一化
		return;
	}

	for(int i=pivotRow;i<this->columnNumber;i++)
	{
		//处理待操作矩阵
		//this->opMatrixPointer[pivotRow][i] = this->opMatrixPointer[pivotRow][i]/pivotValue;
		p_operateMatrix->setMatrixElement(pivotRow, i, p_operateMatrix->getMatrixElement(pivotRow, i)/pivotValue);

	}
	//处理协矩阵
	for(int j=0;j<this->columnNumber;j++)
	{
		//this->invMatrixPointer[pivotRow][j] = this->invMatrixPointer[pivotRow][j]/pivotValue;
		p_inverseMatrix->setMatrixElement(pivotRow, j, p_inverseMatrix->getMatrixElement(pivotRow, j)/pivotValue);

	}

};


/*
 * 从指定列主元所在行开始，对其下方的行进行消元
 * 此函数应当在调用行归一化以后进行
 *
 * pivotRow从0开始
 */
void MatrixInverser::eliminateSubMatrix(int pivotRow)

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
	double currentPivotValue;
	for(int i=pivotRow+1; i<this->rowNumber; i++)
	{
		//currentPivotValue = opMatrixPointer[i][pivotRow];
		currentPivotValue = p_operateMatrix->getMatrixElement(i, pivotRow);
		for(int j=0; j<this->columnNumber; j++)
		{
			//opMatrixPointer[i][j] = opMatrixPointer[i][j] - currentPivotValue*opMatrixPointer[pivotRow][j];
			p_operateMatrix->setMatrixElement(i,j, p_operateMatrix->getMatrixElement(i,j) - currentPivotValue*p_operateMatrix->getMatrixElement(pivotRow,j));

			//invMatrixPointer[i][j] = invMatrixPointer[i][j]- currentPivotValue*invMatrixPointer[pivotRow][j];
			p_inverseMatrix->setMatrixElement(i,j,p_inverseMatrix->getMatrixElement(i,j) - currentPivotValue*p_inverseMatrix->getMatrixElement(pivotRow,j));
		}
	}
};


/*
 * 从指定行开始，对其上方的行进行消元
 * 此函数应当在调用子矩阵消元以后进行
 *
 * startRow从矩阵最末行开始
 */
void MatrixInverser::eliminateUpperMatrix(int startRow)
{
	double temp;
	//从指定行开始，对上三角矩阵进行消元，仅保留主对角元素
	for(int i=startRow-1; i >= 0; i--)
	{
		//temp = this->opMatrixPointer[i][startRow];
		temp = p_operateMatrix->getMatrixElement(i,startRow);
		//this->opMatrixPointer[i][startRow] = 0;
		p_operateMatrix->setMatrixElement(i,startRow,0);
		for(int j=0; j<this->columnNumber; j++)
		{
			//this->invMatrixPointer[i][j] = invMatrixPointer[i][j] - this->invMatrixPointer[startRow][j]*temp;
			p_inverseMatrix->setMatrixElement(i,j, p_inverseMatrix->getMatrixElement(i,j) - p_inverseMatrix->getMatrixElement(startRow,j)*temp);
		}
	}
};

BasicMatrix* MatrixInverser::getInverseMatrix()
{
	return this->p_inverseMatrix;
};
bool MatrixInverser::isOpMatrixFullRank()
{
	return this->isFullRank;
};
