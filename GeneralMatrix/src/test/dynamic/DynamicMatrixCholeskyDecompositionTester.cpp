/*
 * DynamicMatrixCholeskyDecompositionTester.cpp
 *
 *  Created on: 2017��3��18��
 *      Author: looke
 */
//#include "..\matrix\MatrixCholeskyDecomposition.h"
#include <iostream>
#include "basic\BasicMatrix.h"
#include "dynamic\util\DynamicMatrixMultiplier.h"
#include "dynamic\util\DynamicMatrixTransposer.h"
#include "DynamicMatrixCholeskyDecompositionTester.h"
using namespace std;


DynamicMatrixCholeskyDecompositionTester::DynamicMatrixCholeskyDecompositionTester()
{
	cout << "Start Cholesky Decomposition Test" << endl;
}

void DynamicMatrixCholeskyDecompositionTester::test()
{
	//��������ʵ�ԳƲ��Ծ���
	DynamicMatrix CholeskyDecompTestMatrix(3,3);
	CholeskyDecompTestMatrix.setMatrixElement(0,0,6);
	CholeskyDecompTestMatrix.setMatrixElement(0,1,3);
	CholeskyDecompTestMatrix.setMatrixElement(0,2,0);

	CholeskyDecompTestMatrix.setMatrixElement(1,0,3);
	CholeskyDecompTestMatrix.setMatrixElement(1,1,6);
	CholeskyDecompTestMatrix.setMatrixElement(1,2,-6);

	CholeskyDecompTestMatrix.setMatrixElement(2,0,0);
	CholeskyDecompTestMatrix.setMatrixElement(2,1,-6);
	CholeskyDecompTestMatrix.setMatrixElement(2,2,11);

	DynamicMatrixCholeskyDecomposition choleskyDecom = DynamicMatrixCholeskyDecomposition(&CholeskyDecompTestMatrix);

	cout << "Init Op Matrix" << endl;
	choleskyDecom.printOpMatrix();

	cout << "Init Decomp Matrix" << endl;
	choleskyDecom.printDecompositionMatrix();

	choleskyDecom.generateDecompositionMatrix();

	//�ֽ�������

	BasicMatrix* decompResultPointer = choleskyDecom.getDecompositionMatrix();
	DynamicMatrix decompositioinResult = DynamicMatrix(3,3);

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			decompositioinResult.setMatrixElement(i,j,decompResultPointer->getMatrixElement(i,j));
		}
	}
	cout << "Cholesky Decomp Matrix is:" << endl;
	decompositioinResult.printMatrix();

	//�ֽ��������ת��
	DynamicMatrixTransposer transMatrix = DynamicMatrixTransposer(&decompositioinResult);
	transMatrix.transposeMatrix();


	BasicMatrix* decompResultTPointer = transMatrix.getTransposeMatrix();
	DynamicMatrix decompositioinResultT = DynamicMatrix(3,3);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			decompositioinResultT.setMatrixElement(i,j,decompResultTPointer->getMatrixElement(i,j));
		}
	}
	cout << "Cholesky Decomp T Matrix is:" << endl;
	decompositioinResultT.printMatrix();

	//�ֽ���ת�ó��Էֽ�����Ӧ������ԭ��������
	DynamicMatrixMultiplier multip = DynamicMatrixMultiplier(&decompositioinResultT, &decompositioinResult);
	multip.multiplyCalc();
	cout << "Cholesky Decomp T * Cholesky Decomp is:" << endl;
	multip.printMultiplyResult();

};
