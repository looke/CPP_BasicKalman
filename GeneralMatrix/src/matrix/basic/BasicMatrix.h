/*
 * BasicMatrix.h
 *
 *  Created on: 2017年4月1日
 *      Author: looke
 */

#ifndef MATRIX_BASICMATRIX_H_
#define MATRIX_BASICMATRIX_H_

#include "..\vector\basic\BasicVector.h"
#include "math.h"

class BasicMatrix
{
public:
	BasicMatrix();
	BasicMatrix(int inputRowNum, int inputColumnNum);

	int rowNum;
	int columnNum;
	int space;

	//设置矩阵指定元素的值
	virtual void setMatrixElement(int rNum, int cNum, double val);

	//获取矩阵指定元素的值
	virtual double getMatrixElement(int rNum, int cNum);

	//获取矩阵指定元素的值(对元素值进行整形，小于精度的值直接返回0)
	virtual double getMatrixElementRegulared(int rNum, int cNum, double lowEdge);


	//打印矩阵
	virtual void printMatrix();

	//交换行
	virtual void swapRow(int from, int to);

	//交换列
	virtual void swapColumn(int from, int to);

	//交换对角线主元
	virtual void swapDiagElement(int from, int to);

	//将矩阵重置为单位矩阵
	virtual void resetMatrixToI();

	//将矩阵重置为单位矩阵
	virtual void resetMatrixToZero();

	//获取指定列向量
	virtual BasicVector* getColumnVector(int columnNo);

	//获取指定行向量
	virtual BasicVector* getRowVector(int rowNo);

	//获取指定对角子矩阵列向量
	virtual BasicVector* getSubMatrixColumnVector(int subMatrixIndex, int columnNo);

	//获取指定对角子矩阵行向量
	virtual BasicVector* getSubMatrixRowVector(int subMatrixIndex, int rowNo);

	//获取指定对角子矩阵hessenberg列向量
	virtual BasicVector* getSubMatrixHessenColumnVector(int subMatrixIndex);

	//计算两个矩阵各个元素的最大差值(检查行列数)
	double calcMaxDifferentialWithCheck(BasicMatrix* targetMatrix);

	//计算两个矩阵各个元素的最大差值(不检查行列数)
	double calcMaxDifferentialNoCheck(BasicMatrix* targetMatrix);

	//拷贝矩阵元素(检查行列数)
	bool copyMatrixElementWithCheck(BasicMatrix* input_Matrix);

	//拷贝矩阵元素(不检查行列数)
	void copyMatrixElementNoCheck(BasicMatrix* input_Matrix);

	//判断是否为对称方阵
	bool isInputSymmetryMatrix();

	//矩阵所有元素乘以入参
	void rMatrix(double r);

	//矩阵指定列的所有元素符号反转
	void reverseSignOfColumn(int columnIndex);

	//对矩阵所有元素进行整形,将绝对值小于精度的元素设置为0
	void regularZeroElement();

	//寻找主对角线上为0的元素,返回所在位置
	//如果有多个0元,返回索引值最大的那个
	int indexOfZeroOnDiagonal();

	//对角线全部元素减去指定值
	void diagonalSubtraction(double subValue);
	//对角线全部元素加上指定值
	void diagonalAddition(double addValue);

	//初始化精度信息
	void initPrecision();

	//get精度信息
	double getPrecision();

	//计算矩阵的Frobenious范数 ||A||f
	double FrobeniousNorm();

	double getLowEdge();
	//重新设定矩阵维度
	void resizeMatrix(int row, int column);

	//判断矩阵是否属于upper hessenberg矩阵 对于极小值按0处理
	bool isUpperHessenbergMatrix();
	//判断矩阵是否属于upper Triangle矩阵 对于极小值按0处理
	bool isUpperTriangleMatrix();

	virtual ~BasicMatrix() {};
protected:

	double precision;
	virtual void initMatrix();
};


#endif /* MATRIX_BASICMATRIX_H_ */
