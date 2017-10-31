/*
 * MatrixSquareRootSolver.h
 * Solve square roots based on Denman-Beavers Iteration.
 *
 *  Created on: 2017年2月25日
 *      Author: looke
 */

#ifndef MATRIXSQUAREROOTSOLVER_H_
#define MATRIXSQUAREROOTSOLVER_H_
#include "basic\BasicMatrix.h"
#include "basic\util\MatrixInverser.h"

class MatrixSquareRootSolver
{
public:
	MatrixSquareRootSolver(BasicMatrix* input_opMatrix);

	virtual void init(BasicMatrix* input_opMatrix);
	virtual void reload(BasicMatrix* input_opMatrix);

	bool generateSquareRootMatrix();

	void DenmanBeaversIteration();

	BasicMatrix* getSquareRootMatrix();


	void printYMatrix();
	void printZMatrix();


	int getIterationTime();


	virtual ~MatrixSquareRootSolver() {};

	//逆矩阵求解
	MatrixInverser* p_inverser;


protected:
	int iterationTime;
	int maxIterationTime; //最大迭代次数，超过此数后仍然没有获得目标精度的数据，则认为求解失败

	bool isSquareMatrix;
	int rowNumber;
	int columnNumber;
	double maxDiff;
	double threshold;

	BasicMatrix* p_YMatrix;
	BasicMatrix* p_ZMatrix;

	//放置中间过程计算结果的矩阵
	BasicMatrix* p_tempYMatrix;
	BasicMatrix* p_tempZMatrix;

};

#endif /* MATRIXINVERSER_H_ */
