/*
 * MatrixEigenValueSolver.h
 * 使用雅可比迭代法求解对称方阵的特征值和特征向量
 *
 *  Created on: 2017年2月26日
 *      Author: looke
 */

#ifndef MATRIXEIGENVALUESOLVER_H_
#define MATRIXEIGENVALUESOLVER_H_


#include "basic\BasicMatrix.h"
#include "basic\util\MatrixTransposer.h"
#include "basic\util\MatrixMultiplier.h"
class MatrixEigenValueSolver
{
public:

	MatrixEigenValueSolver(BasicMatrix* input_opMatrix);
	virtual void init(BasicMatrix* input_opMatrix);
	virtual void reload(BasicMatrix* input_opMatrix);

	//计算特征向量和特征值
	void calcEigenValue(int input_ratio);

	BasicMatrix* getEigenVectorMatrix();


	BasicMatrix* getEigenValueMatrix();


	void printEigenVectorMatrix();
	void printEigenValueMatrix();
	virtual ~MatrixEigenValueSolver() {};
protected:
	//判断是否对称方阵
	//bool isInputSymmetryMatrix(BasicMatrix* input_opMatrix);

	int ratio;

	int rowAndColumnNumber;
	BasicMatrix* p_operateMatrix;
	BasicMatrix* p_Jn;
	BasicMatrix* p_Jn_transopse;
	//BasicMatrix* p_An;
	BasicMatrix* p_eigenVectorMatrix;

	MatrixTransposer* p_transposer;
	MatrixMultiplier* p_multiplier;

	//计算特征向量和特征值
	void calcEigenValue();

	//查找最大非主元所在位置
	bool findMaxNoneDiagonaleElement();
	//根据最大非主元生成旋转矩阵J以及J的转置Jn
	void generateRotateMatrix_J();

	//根据旋转矩阵J以及J的转置Jn，生成特征值向量矩阵
	void generateEigenVectorMatrix();

	//使用旋转矩阵，旋转后的矩阵A
	void generateTempMatrix_A();

	//对极小非0元素强制归0
	void regularOpMatrix();

	//对所有特征向量的首元素X0进行正负对齐
	void signAlignmentForEigenVector();

	//最大非主元所在位置
	int i_maxNoneDiaElementRow;
	int j_maxNoneDiaElementColumn;

	//对称矩阵标识
	bool isSymmetryMatrix;
	//精度
	double precision;
};


#endif /* MATRIXEIGENVALUESOLVER_H_ */
