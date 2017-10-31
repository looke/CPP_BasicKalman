/*
 * DynamicEigenValuePrinter.cpp
 *
 *  Created on: 2017年6月3日
 *      Author: looke
 */

#include "..\eigen\dynamic\DynamicEigenValuePrinter.h"
#include "iostream"
using namespace std;

DynamicEigenValuePrinter::DynamicEigenValuePrinter(BasicMatrix* p_input_OpMatrix):generalizedEigenCalc_nxn(p_input_OpMatrix,p_input_OpMatrix),normalEigenCalc_nxn(p_input_OpMatrix),testMulti(p_input_OpMatrix,p_input_OpMatrix)
{
	this->OpMatrix = DynamicMatrix(2,2);

	this->OpMatrix_A = DynamicMatrix(2,2);
	this->OpMatrix_B = DynamicMatrix(2,2);

	//this->generalizedEigenCalc_nxn = DynamicGeneralizedEigenSolverForReal(&OpMatrix_A, &OpMatrix_B);

	//this->normalEigenCalc_nxn = DynamicNormalEigenSolverForReal(&OpMatrix);

	this->EigenCalc_2x2 = Dynamic2x2ComplexEigenValueCalculator();

	this->ABInvCalc = ABInverseCalculator();
};


void DynamicEigenValuePrinter::printEigenValues(BasicMatrix* p_input_OpMatrix)
{
	DynamicMatrix complexMatrix_2x2 = DynamicMatrix(2,2);
	OpMatrix.resizeMatrix(p_input_OpMatrix->rowNum,p_input_OpMatrix->columnNum);

	normalEigenCalc_nxn.reload(p_input_OpMatrix);
	normalEigenCalc_nxn.calcEigenValue();
	OpMatrix.copyMatrixElementNoCheck(normalEigenCalc_nxn.getOpHessenbergMatrix());

	cout << "Eigen Value Triangle Matrix" << endl;
	OpMatrix.printMatrix();

	cout << "Eigen Value List:" << endl;
	int i=0;
	while(i<this->OpMatrix.columnNum-1)
	{
		double subDiagonalElement;
		subDiagonalElement = OpMatrix.getMatrixElement(i+1,i);
		if(0==subDiagonalElement)
		{
			cout << OpMatrix.getMatrixElement(i,i) << endl;
			i++;
			if(this->OpMatrix.columnNum-1 == i)
			{
				cout << OpMatrix.getMatrixElement(i,i) << endl;
			}
			continue;
		}
		else
		{
			complexMatrix_2x2.setMatrixElement(0,0,OpMatrix.getMatrixElement(i,i));
			complexMatrix_2x2.setMatrixElement(0,1,OpMatrix.getMatrixElement(i,i+1));
			complexMatrix_2x2.setMatrixElement(1,0,OpMatrix.getMatrixElement(i+1,i));
			complexMatrix_2x2.setMatrixElement(1,1,OpMatrix.getMatrixElement(i+1,i+1));
			EigenCalc_2x2.printEigenValue(&complexMatrix_2x2);
			i = i+2;
			if(this->OpMatrix.columnNum-1 == i)
			{
				cout << OpMatrix.getMatrixElement(i,i) << endl;
			}
			continue;
		}
	}
};


void DynamicEigenValuePrinter::printEigenValues(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	DynamicMatrix Original_A = DynamicMatrix(p_input_OpMatrix_A->rowNum,p_input_OpMatrix_A->columnNum);
	Original_A.copyMatrixElementNoCheck(p_input_OpMatrix_A);

	DynamicMatrix Original_B = DynamicMatrix(p_input_OpMatrix_B->rowNum,p_input_OpMatrix_B->columnNum);
	Original_B.copyMatrixElementNoCheck(p_input_OpMatrix_B);

	DynamicMatrix Q_Total = DynamicMatrix(p_input_OpMatrix_A->rowNum,p_input_OpMatrix_A->columnNum);
	DynamicMatrix Z_Total = DynamicMatrix(p_input_OpMatrix_A->rowNum,p_input_OpMatrix_A->columnNum);

	DynamicMatrix complexMatrix_2x2_A = DynamicMatrix(2,2);
	DynamicMatrix complexMatrix_2x2_B = DynamicMatrix(2,2);
	DynamicMatrix complexMatrix_2x2_ABInv = DynamicMatrix(2,2);
	OpMatrix_A.resizeMatrix(p_input_OpMatrix_A->rowNum,p_input_OpMatrix_A->columnNum);
	OpMatrix_B.resizeMatrix(p_input_OpMatrix_B->rowNum,p_input_OpMatrix_B->columnNum);

	generalizedEigenCalc_nxn.reload(p_input_OpMatrix_A, p_input_OpMatrix_B);

	generalizedEigenCalc_nxn.calcEigenValue();
	OpMatrix_A.copyMatrixElementNoCheck(generalizedEigenCalc_nxn.getHessenbergMatrix());
	OpMatrix_B.copyMatrixElementNoCheck(generalizedEigenCalc_nxn.getTriangleMatrix());
	Q_Total.copyMatrixElementNoCheck(generalizedEigenCalc_nxn.getQMatrix_Total());
	Z_Total.copyMatrixElementNoCheck(generalizedEigenCalc_nxn.getZMatrix_Total());

	cout << "Eigen Value Hessenberg Matrix" << endl;
	OpMatrix_A.printMatrix();
	cout << "Eigen Value Triangle Matrix" << endl;
	OpMatrix_B.printMatrix();

	testMulti.reload(&Q_Total, &Original_A);
	testMulti.multiplyCalc();
	Original_A.copyMatrixElementNoCheck(testMulti.getMultiplyResult());
	testMulti.reload(&Original_A, &Z_Total);
	testMulti.multiplyCalc();
	Original_A.copyMatrixElementNoCheck(testMulti.getMultiplyResult());
	cout << "--------------Q_Total * Op_Matrix_A * Z_Total-----------------" << endl;
	Original_A.printMatrix();

	testMulti.reload(&Q_Total, &Original_B);
	testMulti.multiplyCalc();
	Original_B.copyMatrixElementNoCheck(testMulti.getMultiplyResult());
	testMulti.reload(&Original_B,&Z_Total);
	testMulti.multiplyCalc();
	Original_B.copyMatrixElementNoCheck(testMulti.getMultiplyResult());
	cout << "--------------Q_Total * Op_Matrix_B * Z_Total-----------------" << endl;
	Original_B.printMatrix();

	cout << "Eigen Value List:" << endl;
	double subDiagonalElement;
	double eigenTemp;
	int i=0;
	while(i<this->OpMatrix_A.columnNum-1)
	{
		subDiagonalElement = OpMatrix_A.getMatrixElement(i+1,i);
		//次主对角元元素为0，直接打印特征值A/B
		if(0==subDiagonalElement)
		{
			eigenTemp  = OpMatrix_A.getMatrixElement(i,i)/OpMatrix_B.getMatrixElement(i,i);
			cout << eigenTemp << endl;
			i++;
			if(this->OpMatrix_A.columnNum-1 == i)
			{
				eigenTemp  = OpMatrix_A.getMatrixElement(i,i)/OpMatrix_B.getMatrixElement(i,i);
				cout << eigenTemp << endl;
			}
			continue;
		}
		//次主对角元元素非0，需要先计算A*B^-1，再计算特征值并打印
		else
		{
			complexMatrix_2x2_A.setMatrixElement(0,0,OpMatrix_A.getMatrixElement(i,i));
			complexMatrix_2x2_A.setMatrixElement(0,1,OpMatrix_A.getMatrixElement(i,i+1));
			complexMatrix_2x2_A.setMatrixElement(1,0,OpMatrix_A.getMatrixElement(i+1,i));
			complexMatrix_2x2_A.setMatrixElement(1,1,OpMatrix_A.getMatrixElement(i+1,i+1));

			complexMatrix_2x2_B.setMatrixElement(0,0,OpMatrix_B.getMatrixElement(i,i));
			complexMatrix_2x2_B.setMatrixElement(0,1,OpMatrix_B.getMatrixElement(i,i+1));
			complexMatrix_2x2_B.setMatrixElement(1,0,OpMatrix_B.getMatrixElement(i+1,i));
			complexMatrix_2x2_B.setMatrixElement(1,1,OpMatrix_B.getMatrixElement(i+1,i+1));

			//计算2x2矩阵 A*B^-1
			this->ABInvCalc.generateABinvFirst2x2(&complexMatrix_2x2_A, &complexMatrix_2x2_B);

			complexMatrix_2x2_ABInv.setMatrixElement(0,0,ABInvCalc.getABinv11());
			complexMatrix_2x2_ABInv.setMatrixElement(0,1,ABInvCalc.getABinv12());
			complexMatrix_2x2_ABInv.setMatrixElement(1,0,ABInvCalc.getABinv21());
			complexMatrix_2x2_ABInv.setMatrixElement(1,1,ABInvCalc.getABinv22());

			EigenCalc_2x2.printEigenValue(&complexMatrix_2x2_ABInv);

			i = i+2;
			if(this->OpMatrix_A.columnNum-1 == i)
			{
				eigenTemp  = OpMatrix_A.getMatrixElement(i,i)/OpMatrix_B.getMatrixElement(i,i);
				cout << eigenTemp << endl;
			}
			continue;
		}
	}
};
