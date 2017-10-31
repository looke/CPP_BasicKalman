/*
 * MatrixSquareRootSolver.h
 * Solve square roots based on Denman-Beavers Iteration.
 *
 *  Created on: 2017��2��25��
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

	//��������
	MatrixInverser* p_inverser;


protected:
	int iterationTime;
	int maxIterationTime; //������������������������Ȼû�л��Ŀ�꾫�ȵ����ݣ�����Ϊ���ʧ��

	bool isSquareMatrix;
	int rowNumber;
	int columnNumber;
	double maxDiff;
	double threshold;

	BasicMatrix* p_YMatrix;
	BasicMatrix* p_ZMatrix;

	//�����м���̼������ľ���
	BasicMatrix* p_tempYMatrix;
	BasicMatrix* p_tempZMatrix;

};

#endif /* MATRIXINVERSER_H_ */
