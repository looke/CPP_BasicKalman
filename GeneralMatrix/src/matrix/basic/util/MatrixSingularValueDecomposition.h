/*
 * MatrixSingularValueDecomposition.h
 *
 *  Created on: 2017年3月24日
 *      Author: looke
 */

#ifndef MATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_
#define MATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_

#include "basic\BasicMatrix.h"

#include "basic\util\MatrixEigenValueSolver.h"
#include "basic\util\MatrixMultiplier.h"

class MatrixSingularValueDecomposition
{
public:
	MatrixSingularValueDecomposition(BasicMatrix* input_matrix);

	virtual void init(BasicMatrix* input_matrix);
	virtual void reload(BasicMatrix* input_matrix);

	void sigularValueDecomposition();
	void sigularValueDecomposition(int ratio_engenValue);

	void printOpMatrix();
	void printOpTMatrix();

	BasicMatrix* getUMatrix();
	BasicMatrix* getSingularValueMatrix();
	BasicMatrix* getVMatrix();
	virtual ~MatrixSingularValueDecomposition() {};

	//特征值分解
	MatrixEigenValueSolver* p_eigenValueProc;

	//矩阵乘法
	MatrixMultiplier* p_multiplyProc;

protected:
	int rowNumber;
	int columnNumber;

	bool isDoubleEqual(double f1, double f2, double error_max);

	double fPrecision;

	//m*n original op matrix
	BasicMatrix* p_opMatrix;

	//n*m transposed op matrix
	BasicMatrix* p_opTMatrix;

	//result pool
	//m*m matrix U矩阵
	BasicMatrix* p_UMatrix;
	//m*m matrix U矩阵对应的特征值矩阵
	BasicMatrix* p_U_eigenValueMatrix;

	//m*n matrix
	BasicMatrix* p_SingularValueMatrix;

	//n*n matrix V矩阵
	BasicMatrix* p_VMatrix;
	//n*n matrix V矩阵对应的特征值矩阵
	BasicMatrix* p_V_eigenValueMatrix;

	//UV矩阵对应的特征值合并
	//double* UV_eigenValue;
};



#endif /* MATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_ */
