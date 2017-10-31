/*
 * MatrixSingularValueDecomposition.cpp
 *
 *  Created on: 2017年3月24日
 *      Author: looke
 */

#include "MatrixSingularValueDecomposition.h"
//#include <malloc.h>
#include <iostream>
#include "math.h"
using namespace std;

/*
 * SVD分解 构造函数
 */
MatrixSingularValueDecomposition::MatrixSingularValueDecomposition(BasicMatrix* input_matrix)
{
	//this->MatrixSingularValueDecomposition();
	this->init(input_matrix);
};

/*
 * SVD分解 初始化过程
 *
 * 输入m*n操作矩阵
 *
 */
void MatrixSingularValueDecomposition::init(BasicMatrix* input_matrix)
{

};

/*
 * 重新装载
 */
void MatrixSingularValueDecomposition::reload(BasicMatrix* input_matrix)
{

};

/*
 * ratio_engenValue:计算特征值和特征向量时对操作矩阵的缩放比例
 *
 * SVD分解过程
 * 1.计算U=A*AT
 * 2.计算U的特征值与特征向量
 * 3.计算V=AT*A
 * 4.计算V的特征值与特征向量
 * 5.合并 U V特征值矩阵
 * 6.计算S
 *
 */
void MatrixSingularValueDecomposition::sigularValueDecomposition(int ratio_engenValue)
{
	//计算 A*AT
	this->p_multiplyProc->reload(p_opMatrix,p_opTMatrix);
	this->p_multiplyProc->multiplyCalc();
	//A*AT的结果赋值给UMatrix
	this->p_UMatrix->copyMatrixElementNoCheck(p_multiplyProc->getMultiplyResult());

	cout << "-------------A*AT-------------" << endl;
	this->p_UMatrix->printMatrix();

	//计算A*AT的特征值及特征向量
	this->p_eigenValueProc->reload(p_UMatrix);
	p_eigenValueProc->calcEigenValue(ratio_engenValue);

	//拷贝特征向量矩阵到UMatrix
	this->p_UMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenVectorMatrix());

	//拷贝特征值矩阵到U_eigenValueMatrix
	this->p_U_eigenValueMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenValueMatrix());

	cout << "-------------A*AT EigenVector-------------" << endl;
	this->p_UMatrix->printMatrix();
	cout << "-------------A*AT EigenValue-------------" << endl;
	this->p_U_eigenValueMatrix->printMatrix();

	cout << "-----------------------------------------" << endl;

	//计算 AT*A
	this->p_multiplyProc->reload(p_opTMatrix,p_opMatrix);
	this->p_multiplyProc->multiplyCalc();
	// AT*A的结果赋值给VMatrix
	this->p_VMatrix->copyMatrixElementNoCheck(p_multiplyProc->getMultiplyResult());
	cout << "-------------AT*A-------------" << endl;
	this->p_VMatrix->printMatrix();

	//计算AT*A的特征值及特征向量
	this->p_eigenValueProc->reload(p_VMatrix);
	p_eigenValueProc->calcEigenValue(ratio_engenValue);

	//拷贝特征向量矩阵到UMatrix
	this->p_VMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenVectorMatrix());

	//拷贝特征值矩阵到U_eigenValueMatrix
	this->p_V_eigenValueMatrix->copyMatrixElementNoCheck(p_eigenValueProc->getEigenValueMatrix());

	cout << "-------------AT*A EigenVector-------------" << endl;
	this->p_VMatrix->printMatrix();
	cout << "-------------AT*A EigenValue-------------" << endl;
	this->p_V_eigenValueMatrix->printMatrix();

	//根据特征值大小，生成奇异值S矩阵
	this->p_SingularValueMatrix->resetMatrixToZero();

	BasicMatrix* eigenValueMatrixPointer;
	if(p_U_eigenValueMatrix->rowNum > p_V_eigenValueMatrix->rowNum)
	{
		eigenValueMatrixPointer = p_U_eigenValueMatrix;
	}
	else
	{
		eigenValueMatrixPointer = p_V_eigenValueMatrix;
	}

	for(int i=0; i<p_SingularValueMatrix->rowNum && i<p_SingularValueMatrix->columnNum; i++)
	{
		//double数据与0对比，精度fPrecision
		if(this->isDoubleEqual(eigenValueMatrixPointer->getMatrixElement(i,i), 0, this->fPrecision))
		{
			p_SingularValueMatrix->setMatrixElement(i,i,0);
		}
		else
		{
			p_SingularValueMatrix->setMatrixElement(i,i,sqrt(eigenValueMatrixPointer->getMatrixElement(i,i)));
		}
	}

	cout << "Singular Value Matrix:" << endl;
	this->p_SingularValueMatrix->printMatrix();
};

/*
void MatrixSingularValueDecomposition::sigularValueDecomposition(int ratio_engenValue)
{

};
*/

/*
 * 打印操作矩阵
 */
void MatrixSingularValueDecomposition::printOpMatrix()
{
	this->p_opMatrix->printMatrix();
};

/*
 * 打印操作矩阵的转置
 */
void MatrixSingularValueDecomposition::printOpTMatrix()
{
	this->p_opTMatrix->printMatrix();
};

/*
 * 判断浮点数是否相等，精度为error_max
 */
bool MatrixSingularValueDecomposition::isDoubleEqual(double f1, double f2, double error_max)
{
	double error = fabs(fabs(f1)-fabs(f2));
	if(error < error_max)
	{
		return 1;
	}
	else
		return 0;
};

BasicMatrix* MatrixSingularValueDecomposition::getUMatrix()
{
	return this->p_UMatrix;
};

BasicMatrix* MatrixSingularValueDecomposition::getSingularValueMatrix()
{
	return this->p_SingularValueMatrix;
};

BasicMatrix* MatrixSingularValueDecomposition::getVMatrix()
{
	return this->p_VMatrix;
};
