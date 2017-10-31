/*
 * MatrixEigenValueSolver.h
 * ʹ���ſɱȵ��������ԳƷ��������ֵ����������
 *
 *  Created on: 2017��2��26��
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

	//������������������ֵ
	void calcEigenValue(int input_ratio);

	BasicMatrix* getEigenVectorMatrix();


	BasicMatrix* getEigenValueMatrix();


	void printEigenVectorMatrix();
	void printEigenValueMatrix();
	virtual ~MatrixEigenValueSolver() {};
protected:
	//�ж��Ƿ�ԳƷ���
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

	//������������������ֵ
	void calcEigenValue();

	//����������Ԫ����λ��
	bool findMaxNoneDiagonaleElement();
	//����������Ԫ������ת����J�Լ�J��ת��Jn
	void generateRotateMatrix_J();

	//������ת����J�Լ�J��ת��Jn����������ֵ��������
	void generateEigenVectorMatrix();

	//ʹ����ת������ת��ľ���A
	void generateTempMatrix_A();

	//�Լ�С��0Ԫ��ǿ�ƹ�0
	void regularOpMatrix();

	//������������������Ԫ��X0������������
	void signAlignmentForEigenVector();

	//������Ԫ����λ��
	int i_maxNoneDiaElementRow;
	int j_maxNoneDiaElementColumn;

	//�Գƾ����ʶ
	bool isSymmetryMatrix;
	//����
	double precision;
};


#endif /* MATRIXEIGENVALUESOLVER_H_ */
