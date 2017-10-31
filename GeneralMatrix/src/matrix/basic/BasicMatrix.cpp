/*
 * BasicMatrix.cpp
 *
 *  Created on: 2017年4月1日
 *      Author: looke
 */


#include "BasicMatrix.h"
#include <iostream>

using namespace std;


BasicMatrix::BasicMatrix()
{
	//this->precision = 0.0000000001;
};


BasicMatrix::BasicMatrix(int inputRowNum, int inputColumnNum)
{
	//this->precision = 0.0000000001;
	if(inputRowNum > 0 && inputColumnNum >0)
	{
		this->rowNum = inputRowNum;
		this->columnNum = inputColumnNum;
		//call the default constructor
		//this->initMatrix();
	}
	else
	{
		cout<<"Illegal in put row/column numbers!" << endl;
		cout<<"Using default row/column number construct Matrix!" << endl;
		//BasicMatrix();
	}
};

void BasicMatrix::initMatrix()
{};

void BasicMatrix::printMatrix()
{

};


void BasicMatrix::setMatrixElement(int rNum, int cNum, double val)
{

};

double BasicMatrix::getMatrixElement(int rNum, int cNum)
{
};

//获取矩阵指定元素的值(对元素值进行整形，小于精度的值直接返回0)
double BasicMatrix::getMatrixElementRegulared(int rNum, int cNum, double lowEdge)
{};

/*
 * 交换指定两行
 */
void BasicMatrix::swapRow(int from, int to)
{

};

/*
 *交换指定两列
 */
void BasicMatrix::swapColumn(int from, int to)
{

};

//交换对角线主元
void BasicMatrix::swapDiagElement(int from, int to)
{

};


/*
 * 将矩阵重置为单位阵
 */
void BasicMatrix::resetMatrixToI()
{

};

/*
 * 将矩阵重置为0阵
 */
void BasicMatrix::resetMatrixToZero()
{

};

//获取指定列向量
BasicVector* BasicMatrix::getColumnVector(int columnNo)
{};

//获取指定行向量
BasicVector* BasicMatrix::getRowVector(int rowNo)
{};

//获取指定对角子矩阵列向量
BasicVector* BasicMatrix::getSubMatrixColumnVector(int subMatrixIndex, int columnNo)
{};

//获取指定对角子矩阵行向量
BasicVector* BasicMatrix::getSubMatrixRowVector(int subMatrixIndex, int rowNo)
{};
//获取指定对角子矩阵hessenberg列向量
BasicVector* BasicMatrix::getSubMatrixHessenColumnVector(int subMatrixIndex)
{};
/*
 * 计算矩阵对应元素最大差异(检查行列数)
 */
double BasicMatrix::calcMaxDifferentialWithCheck(BasicMatrix* targetMatrix)
{
	if(targetMatrix->rowNum == this->rowNum && targetMatrix->columnNum == this->columnNum)
	{
		double aMatrixElement = 0;
		double bMatrixElement = 0;
		double tempDiff = 0;
		double maxDiff = 0;

		for(int i=0; i<this->rowNum; i++)
		{
			for(int j=0; j<this->columnNum; j++)
			{
				//计算两个矩阵对应元素的差值的绝对值
				aMatrixElement = this->getMatrixElement(i,j);
				bMatrixElement = targetMatrix->getMatrixElement(i,j);
				tempDiff = aMatrixElement-bMatrixElement;
				if(tempDiff < 0)
				{
					tempDiff = 0 - tempDiff;
				}

				//对比最大差值，根据结果更新最大差值
				if(maxDiff < tempDiff)
				{
					maxDiff = tempDiff;
				}
			}
		}
		return maxDiff;
	}
	else
	{
		return -1;
	}
};

/*
 * 计算矩阵对应元素最大差异(不检查行列数)
 */
double BasicMatrix::calcMaxDifferentialNoCheck(BasicMatrix* targetMatrix)
{
	double aMatrixElement = 0;
	double bMatrixElement = 0;
	double tempDiff = 0;
	double maxDiff = 0;

	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			//计算两个矩阵对应元素的差值的绝对值
			aMatrixElement = this->getMatrixElement(i,j);
			bMatrixElement = targetMatrix->getMatrixElement(i,j);
			tempDiff = aMatrixElement-bMatrixElement;
			if(tempDiff < 0)
			{
				tempDiff = 0 - tempDiff;
			}

			//对比最大差值，根据结果更新最大差值
			if(maxDiff < tempDiff)
			{
				maxDiff = tempDiff;
			}
		}
	}
	return maxDiff;
};

/*
 * 拷贝矩阵元素 检查行列数
 *
 * 若输入矩阵行列数一致，则执行拷贝并返回1
 *
 * 若输入矩阵行列数不一致，则直接返回0
 */
bool BasicMatrix::copyMatrixElementWithCheck(BasicMatrix* input_Matrix)
{
	if(this->rowNum == input_Matrix->rowNum &&
		this->columnNum== input_Matrix->columnNum)
	{
		for(int i=0; i<this->rowNum;i++)
		{
			for(int j=0; j<this->columnNum; j++)
			{
				this->setMatrixElement(i,j, input_Matrix->getMatrixElement(i,j));
			}
		}
		return 1;
	}
	return 0;
};

/*
 * 拷贝矩阵元素 不检查行列数
 *
 * 若输入矩阵行列数一致，则执行拷贝
 *
 * 若输入矩阵行列数不一致，则会出现异常
 */
void BasicMatrix::copyMatrixElementNoCheck(BasicMatrix* input_Matrix)
{
	for(int i=0; i<this->rowNum;i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			this->setMatrixElement(i,j, input_Matrix->getMatrixElement(i,j));
		}
	}
};

/*
 * 判断是否为对称方阵
 */
bool BasicMatrix::isInputSymmetryMatrix()
{
	if(this->rowNum == this->columnNum)
	{
		for(int i=0; i<this->rowNum; i++)
		{
			for(int j=i; j<this->columnNum; j++)
			{
				if(i==j)
				{
					continue;
				}
				if(this->getMatrixElement(i,j) != this->getMatrixElement(j,i))
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
};

//矩阵所有元素乘以入参
void BasicMatrix::rMatrix(double r)
{
	for(int i=0; i<this->rowNum;i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			this->setMatrixElement(i,j, this->getMatrixElement(i,j)*r);
		}
	}
};

//矩阵指定列的所有元素符号反转
void BasicMatrix::reverseSignOfColumn(int columnIndex)
{
	for(int i=0; i<this->rowNum;i++)
	{
		this->setMatrixElement(i,columnIndex, 0 - this->getMatrixElement(i,columnIndex));
	}
};

//对矩阵所有元素进行整形,将绝对值小于精度的元素设置为0
void BasicMatrix::regularZeroElement()
{
	double normF = this->FrobeniousNorm();
	double lowEdge = normF * this->precision;
	double temp;
	for(int i=0; i<this->rowNum;i++)
	{
		for(int j=0; j<this->columnNum;j++)
		{
			temp = fabs(this->getMatrixElement(i,j));
			if(temp < lowEdge)
			{
				this->setMatrixElement(i,j,0.0);
			}
		}
	}
};

//寻找主对角线上为0的元素,返回所在位置
//如果有多个0元,返回索引值最大的那个(最靠近右下角的)
int BasicMatrix::indexOfZeroOnDiagonal()
{
	double temp;
	for(int i=this->rowNum-1; i>=0;i--)
	{
		temp = fabs(this->getMatrixElement(i,i));
		if(temp < this->precision)
		{
			return i;
		}
	}
	return -1;
};

/*
 * 对角线全部元素减去指定值
 */
void BasicMatrix::diagonalSubtraction(double subValue)
{
	double temp;
	for(int i=0; i<this->rowNum; i++)
	{
		temp = this->getMatrixElement(i,i);
		temp = temp - subValue;
		this->setMatrixElement(i,i,temp);
	}
};

/*
 * 对角线全部元素加上指定值
 */
void BasicMatrix::diagonalAddition(double addValue)
{
	double temp;
	for(int i=0; i<this->rowNum; i++)
	{
		temp = this->getMatrixElement(i,i);
		temp = temp + addValue;
		this->setMatrixElement(i,i,temp);
	}
};

/*
 * 初始化精度信息
 */
void BasicMatrix::initPrecision()
{
	int size = sizeof(double);

	switch(size)
	{
		case 4: //4字节32位 23位浮点位 log2^23 小数点后7位精度
		{
			this->precision = 0.0000001;
			break;
		}
		case 8: //8字节64位 52位浮点位 log2^52 小数点后15位精度
		{
			this->precision = 0.000000000000001;
			break;
		}
		default:
			this->precision = 0.0000001;
	}
};

//get精度信息
double BasicMatrix::getPrecision()
{
	return this->precision;
};

/*
 * 计算矩阵的Frobenious范数 ||A||f 矩阵元素绝对值的平方和再开平方
 */
double BasicMatrix::FrobeniousNorm()
{
	double normValue = 0.0;
	double temp;
	for(int i=0; i<this->rowNum; i++)
	{
		for(int j=0; j<this->columnNum; j++)
		{
			temp = fabs(this->getMatrixElement(i,j));
			normValue = normValue + temp*temp;
		}
	}

	normValue = sqrt(normValue);
	return normValue;
};

/*
 * 重新设定矩阵维度
 */
void BasicMatrix::resizeMatrix(int row, int column)
{
	if(row < this->space && column < this->space)
	{
		this->rowNum = row;
		this->columnNum = column;
		this->resetMatrixToI();
	}
};

double BasicMatrix::getLowEdge()
{
	return this->FrobeniousNorm() * this->precision;
};
/*
 * //判断矩阵是否属于upper hessenberg矩阵 对于极小值按0处理
 */
bool BasicMatrix::isUpperHessenbergMatrix()
{
	if(this->rowNum != this->columnNum)
	{
		return false;
	}

	double normF = this->FrobeniousNorm();
	double lowEdge = normF * this->precision;

	double temp;
	for(int i=rowNum-1; i>=0; i--)
	{
		for(int j=i-2; j>=0; j--)
		{
			temp = this->getMatrixElementRegulared(i,j,lowEdge);
			if(0 != temp)
			{
				return false;
			}
		}
	}
	return true;

};

/*
 * 判断矩阵是否属于upper Triangle矩阵 对于极小值按0处理
 */
bool BasicMatrix::isUpperTriangleMatrix()
{
	if(this->rowNum != this->columnNum)
	{
		return false;
	}
	double normF = this->FrobeniousNorm();
	double lowEdge = normF * this->precision;

	double temp;
	for(int i=rowNum-1; i>=0; i--)
	{
		for(int j=i-1; j>=0; j--)
		{
			temp = this->getMatrixElementRegulared(i,j,lowEdge);
			if(0 != temp)
			{
				return false;
			}
		}
	}
	return true;
};
