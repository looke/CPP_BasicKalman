/*
 * DynamicMatrixSingularValueDecomposition.h
 *
 *  Created on: 2017��3��24��
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

	//����ֵ�ֽ�
	DynamicMatrixEigenValueSolver eigenValueProc;

	//����˷�
	DynamicMatrixMultiplier multiplyProc;

protected:
	//m*n original op matrix
	DynamicMatrix opMatrix;

	//n*m transposed op matrix
	DynamicMatrix opTMatrix;

	//result pool
	//m*m matrix U����
	DynamicMatrix UMatrix;
	//m*m matrix U�����Ӧ������ֵ����
	DynamicMatrix U_eigenValueMatrix;

	//m*n matrix
	DynamicMatrix SingularValueMatrix;

	//n*n matrix V����
	DynamicMatrix VMatrix;
	//n*n matrix V�����Ӧ������ֵ����
	DynamicMatrix V_eigenValueMatrix;
};



#endif /* DYNAMICMATRIX_MATRIXSINGULARVALUEDECOMPOSITION_H_ */
