/*
 * DynamicMatrixSingularValueDecomposition.h
 *
 *  Created on: 2017年3月24日
 *      Author: looke
 */

#ifndef DYNAMICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_
#define DYNAMICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_

//#include "basic\BasicMatrix.h"

//#include "basic\util\MatrixEigenValueSolver.h"
#include "basic\util\MatrixSingularValueDecomposition.h"
#include "dynamic\DynamicMatrix.h"
#include "dynamic\util\DynamicMatrixEigenValueSolver.h"
#include "dynamic\util\DynamicMatrixMultiplier.h"

class DynamicMatrixSingularValueDecomposition:public MatrixSingularValueDecomposition
{
public:
	DynamicMatrixSingularValueDecomposition(BasicMatrix* input_matrix);

	void init(BasicMatrix* input_matrix);
	void reload(BasicMatrix* input_matrix);

	//特征值分解
	DynamicMatrixEigenValueSolver eigenValueProc;

	//矩阵乘法
	DynamicMatrixMultiplier multiplyProc;

protected:
	//m*n original op matrix
	DynamicMatrix opMatrix;

	//n*m transposed op matrix
	DynamicMatrix opTMatrix;

	//result pool
	//m*m matrix U矩阵
	DynamicMatrix UMatrix;
	//m*m matrix U矩阵对应的特征值矩阵
	DynamicMatrix U_eigenValueMatrix;

	//m*n matrix
	DynamicMatrix SingularValueMatrix;

	//n*n matrix V矩阵
	DynamicMatrix VMatrix;
	//n*n matrix V矩阵对应的特征值矩阵
	DynamicMatrix V_eigenValueMatrix;
};



#endif /* DYNAMICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_ */
