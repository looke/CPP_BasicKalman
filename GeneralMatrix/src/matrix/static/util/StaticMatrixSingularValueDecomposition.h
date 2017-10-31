/*
 * StaticMatrixSingularValueDecomposition.h
 *
 *  Created on: 2017年3月24日
 *      Author: looke
 */

#ifndef STATICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_
#define STATICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_

//#include "basic\BasicMatrix.h"

#include "basic\util\MatrixSingularValueDecomposition.h"
#include "static\StaticMatrix.h"
#include "static\util\StaticMatrixEigenValueSolver.h"
#include "static\util\StaticMatrixMultiplier.h"

class StaticMatrixSingularValueDecomposition:public MatrixSingularValueDecomposition
{
public:
	StaticMatrixSingularValueDecomposition(BasicMatrix* input_matrix);

	void init(BasicMatrix* input_matrix);
	void reload(BasicMatrix* input_matrix);

	//特征值分解
	StaticMatrixEigenValueSolver eigenValueProc;

	//矩阵乘法
	StaticMatrixMultiplier multiplyProc;

protected:
	//m*n original op matrix
	StaticMatrix opMatrix;

	//n*m transposed op matrix
	StaticMatrix opTMatrix;

	//result pool
	//m*m matrix U矩阵
	StaticMatrix UMatrix;
	//m*m matrix U矩阵对应的特征值矩阵
	StaticMatrix U_eigenValueMatrix;

	//m*n matrix
	StaticMatrix SingularValueMatrix;

	//n*n matrix V矩阵
	StaticMatrix VMatrix;
	//n*n matrix V矩阵对应的特征值矩阵
	StaticMatrix V_eigenValueMatrix;
};



#endif /* STATICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_ */
