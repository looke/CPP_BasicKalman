/*
 * MatrixEigenValueSolver.cpp
 *
 *  Created on: 2017��2��26��
 *      Author: looke
 */
#include "math.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "MatrixEigenValueSolver.h"
#include "MatrixTransposer.h"
#include "MatrixMultiplier.h"
using namespace std;


/*
 * ��ʼ������
 * ����������������������г�ʼ��
 * �������������Ϊ�ԳƷ��������������ʼ��
 */
MatrixEigenValueSolver::MatrixEigenValueSolver(BasicMatrix* input_opMatrix)
{
	/*
	this->isSymmetryMatrix = input_opMatrix->isInputSymmetryMatrix();

	//�ǶԳƷ���Ļ�����Ҫ����ʼ�� ��ӡ������˳�
	if(!this->isSymmetryMatrix)
	{
		cout << "not Symmm! no init proc." << endl;
		return;
	}
	*/
	this->ratio = 1;
	this->init(input_opMatrix);
};

/*
 * ��ȷ���������Ϊ�ԳƷ������ô�init������ʼ��
 */
void MatrixEigenValueSolver::init(BasicMatrix* input_opMatrix)
{

};

void MatrixEigenValueSolver::reload(BasicMatrix* input_opMatrix)
{

};


/*
 * ���ҷ����Խ�Ԫ�����ֵ����λ��
 */
bool MatrixEigenValueSolver::findMaxNoneDiagonaleElement()
{
	double maxTemp = 0;
	double currentTemp = 0;
	for(int i=0; i<this->rowAndColumnNumber; i++)
	{
		for(int j=0; j<this->rowAndColumnNumber; j++)
		{
			if(i==j)
			{
				continue;
			}
			currentTemp = fabs(this->p_operateMatrix->getMatrixElement(i,j));
			if(currentTemp > maxTemp)
			{
				maxTemp = currentTemp;
				this->i_maxNoneDiaElementRow = i;
				this->j_maxNoneDiaElementColumn = j;
			}
		}
	}

	//�ж��Ƿ�ﵽ���ȣ�������ֵ�Ѿ��ﵽ���ȣ��򷵻�false����ʾ�Ѿ�û�����ֵ�������Խ�Ԫ��ȫ��Ϊ0
	if(maxTemp <= this->precision)
	{
		return false;
	}
	cout << "Max None Diagonale Row:" << i_maxNoneDiaElementRow << "   Column:" << j_maxNoneDiaElementColumn << endl;
	return true;
};


/*
 * �������ǶԽ�Ԫ����λ�ã����ɹ���ѡ�����J
 */
void MatrixEigenValueSolver::generateRotateMatrix_J()
{
	double Aij = this->p_operateMatrix->getMatrixElement(i_maxNoneDiaElementRow, j_maxNoneDiaElementColumn);
	double Aii = this->p_operateMatrix->getMatrixElement(i_maxNoneDiaElementRow, i_maxNoneDiaElementRow);
	double Ajj = this->p_operateMatrix->getMatrixElement(j_maxNoneDiaElementColumn, j_maxNoneDiaElementColumn);
	double y = 2*Aij;
	double x = Aii-Ajj;
	double tal = x/y;

	double t = 1/(fabs(tal)+sqrt(1+tal*tal));
	if(tal < 0)
	{
		t = 0 - t;
	}

	//double theta2 = atan2(y, x);

	//double cosTheta = cos(theta2/2);
	double cosTheta = 1/sqrt(1+t*t);
	//double sinTheta = sin(theta2/2);
	double sinTheta = t*cosTheta;
	/*
	for(int i=0; i<this->rowAndColumnNumber; i++)
	{
		for(int j=0; j<this->rowAndColumnNumber; j++)
		{
			if(i == j)
			{
				this->p_Jn->setMatrixElement(i,j,1);
			}
			else
			{
				this->p_Jn->setMatrixElement(i,j,0);
			}

		}
	}
	*/
	this->p_Jn->resetMatrixToI();
	//cout<<"Jn After reset to I" << endl;
	//this->p_Jn->printMatrix();

	this->p_Jn->setMatrixElement(i_maxNoneDiaElementRow,i_maxNoneDiaElementRow, cosTheta);
	this->p_Jn->setMatrixElement(i_maxNoneDiaElementRow,j_maxNoneDiaElementColumn, sinTheta);

	this->p_Jn->setMatrixElement(j_maxNoneDiaElementColumn,j_maxNoneDiaElementColumn, cosTheta);
	this->p_Jn->setMatrixElement(j_maxNoneDiaElementColumn,i_maxNoneDiaElementRow, 0-sinTheta);

	cout<<"Jn After Set Data" << endl;
	this->p_Jn->printMatrix();

	//MatrixTransposer transposer = MatrixTransposer(this->p_Jn);
	p_transposer->reload(this->p_Jn);
	p_transposer->transposeMatrix();


	p_Jn_transopse->copyMatrixElementNoCheck(p_transposer->getTransposeMatrix());
	/*
	for(int i=0; i<this->rowAndColumnNumber; i++)
	{
		for(int j=0; j<this->rowAndColumnNumber; j++)
		{
			this->Jn_transopse.setMatrixElement(i,j, transposed_J[i][j]);
		}
	}
	*/
	//cout<<"Jn After Transpose" << endl;
	//this->p_Jn_transopse->printMatrix();
};

/*
 * ʹ����ת����������ת��ľ���An
 */
void MatrixEigenValueSolver::generateTempMatrix_A()
{
	//MatrixMultiplier leftMulti = MatrixMultiplier(this->p_Jn, this->p_operateMatrix);
	this->p_multiplier->reload(this->p_Jn, this->p_operateMatrix);
	this->p_multiplier->multiplyCalc();
	//cout << "left multi done!" << endl;
	//this->p_multiplier->printMultiplyResult();


	//��˽����������������ĸ���Ԫ��
	p_operateMatrix->copyMatrixElementNoCheck(this->p_multiplier->getMultiplyResult());
	/*
	for(int i=0; i<rowAndColumnNumber; i++)
	{
		for(int j=0; j<rowAndColumnNumber; j++)
		{
			operateMatrix.setMatrixElement(i,j, tempLeft[i][j]);
		}
	}
	*/
	//MatrixMultiplier rightMulti = MatrixMultiplier(this->p_operateMatrix, this->p_Jn_transopse);
	this->p_multiplier->reload(this->p_operateMatrix, this->p_Jn_transopse);
	this->p_multiplier->multiplyCalc();
	//cout << "right multi done!" << endl;
	//this->p_multiplier->printMultiplyResult();



	//�ҳ˽����������������ĸ���Ԫ��
	p_operateMatrix->copyMatrixElementNoCheck(this->p_multiplier->getMultiplyResult());
	/*
	for(int i=0; i<rowAndColumnNumber; i++)
	{
		for(int j=0; j<rowAndColumnNumber; j++)
		{
			operateMatrix.setMatrixElement(i,j, tempright[i][j]);
		}
	}
	 */

	p_operateMatrix->setMatrixElement(this->i_maxNoneDiaElementRow, this->j_maxNoneDiaElementColumn,0);
	p_operateMatrix->setMatrixElement(this->j_maxNoneDiaElementColumn, this->i_maxNoneDiaElementRow,0);
	cout << "Op Matrix After rotate is:" << endl;
	p_operateMatrix->printMatrix();
};

/*
 * ������ת����Jn��ת��Jn_transopse����������ֵ��������
 */
void MatrixEigenValueSolver::generateEigenVectorMatrix()
{
	//MatrixMultiplier rightMulti = MatrixMultiplier(this->p_eigenVectorMatrix, this->p_Jn_transopse);
	this->p_multiplier->reload(this->p_eigenVectorMatrix, this->p_Jn_transopse);
	this->p_multiplier->multiplyCalc();

	//cout<< "New EigenVector Matrix:" << endl;
	//this->p_multiplier->printMultiplyResult();


	//�ҳ˽��������������������ĸ���Ԫ��
	p_eigenVectorMatrix->copyMatrixElementNoCheck(this->p_multiplier->getMultiplyResult());
	/*
	for(int i=0; i<rowAndColumnNumber; i++)
	{
		for(int j=0; j<rowAndColumnNumber; j++)
		{
			eigenVectorMatrix.setMatrixElement(i,j, tempright[i][j]);
		}
	}
	*/
};
/*
 * ����������������ֵ����������
 */
void MatrixEigenValueSolver::calcEigenValue()
{
	cout << std::setprecision(10);
	if(!isSymmetryMatrix)
	{
		cout << "Illegal Matrix, None Symmetry!" << endl;
		return;
	}
	int i=1;
	cout << "-----------Start to calc eigenValue and Vector------------" << endl;
	while(this->findMaxNoneDiagonaleElement())
	{
		cout << "---------Loop: " << i << " -----------" << endl;
		this->generateRotateMatrix_J();
		this->generateEigenVectorMatrix();
		this->generateTempMatrix_A();
		//this->regularOpMatrix();
		//cout << "After Regular OP Matrix" << endl;
		//this->p_operateMatrix->printMatrix();
		i++;
	}

	//��������ֵ��С˳�򣬶�����ֵ������������������������
	double tempMaxElement;
	int from = 0;
	int to = 0;
	for(int i=0; i<p_operateMatrix->rowNum; i++)
	{
		tempMaxElement = this->p_operateMatrix->getMatrixElement(i,i);
		to = i;
		from = i;
		for(int j=i+1; j<p_operateMatrix->rowNum; j++)
		{
			if(this->p_operateMatrix->getMatrixElement(j,j) > tempMaxElement)
			{
				tempMaxElement = this->p_operateMatrix->getMatrixElement(j,j);
				from = j;
			}
		}
		if(from != to)
		{
			this->p_operateMatrix->swapDiagElement(from, to);
			this->p_eigenVectorMatrix->swapColumn(from, to);
		}
	}
	cout << "-----------Eigen Value------------" << endl;
	this->p_operateMatrix->printMatrix();
	cout << "-----------Eigen Vector------------" << endl;
	this->p_eigenVectorMatrix->printMatrix();

	signAlignmentForEigenVector();
	cout << "-----------Eigen Vector After Sign Alignment------------" << endl;
	this->p_eigenVectorMatrix->printMatrix();

};

void MatrixEigenValueSolver::calcEigenValue(int input_ratio)
{
	double r = 1.0/input_ratio;
	p_operateMatrix->rMatrix(r);
	cout << "-----------Eigen Value ratioed OP Matrix------------" << endl;
	p_operateMatrix->printMatrix();
	calcEigenValue();
	cout << "-----------Eigen Value After ratioBack------------" << endl;
	p_operateMatrix->rMatrix(input_ratio);
	p_operateMatrix->printMatrix();
};
/*
 * ��ӡ������������
 */
void MatrixEigenValueSolver::printEigenVectorMatrix()
{
	this->p_eigenVectorMatrix->printMatrix();
};

/*
 * ��ӡ����ֵ����
 */
void MatrixEigenValueSolver::printEigenValueMatrix()
{
	this->p_operateMatrix->printMatrix();
};


/*
 * ��ȡ�������������ָ��
 */
BasicMatrix* MatrixEigenValueSolver::getEigenVectorMatrix()
{
	return this->p_eigenVectorMatrix;
};


/*
 * ��ȡ����ֵ�����ָ��
 */

BasicMatrix* MatrixEigenValueSolver::getEigenValueMatrix()
{
	return this->p_operateMatrix;
};

void MatrixEigenValueSolver::regularOpMatrix()
{
	double temp;
	for(int i=0; i<this->rowAndColumnNumber;i++)
	{
		for(int j=0; j<this->rowAndColumnNumber;j++)
		{
			temp = fabs(this->p_operateMatrix->getMatrixElement(i,j));
			if(temp < this->precision)
			{
				this->p_operateMatrix->setMatrixElement(i,j,0.0);
			}
		}
	}
};

//������������������Ԫ��X0������������
void MatrixEigenValueSolver::signAlignmentForEigenVector()
{
	bool isPositive = false;
	double temp = this->p_eigenVectorMatrix->getMatrixElement(0,0);

	if(temp >= 0)
	{
		isPositive = true;
	}

	for(int i=1; i<this->p_eigenVectorMatrix->columnNum; i++)
	{
		temp = this->p_eigenVectorMatrix->getMatrixElement(0,i);
		if(temp >=0 && !isPositive)
		{
			this->p_eigenVectorMatrix->reverseSignOfColumn(i);
		}
		else if(temp < 0 && isPositive)
		{
			this->p_eigenVectorMatrix->reverseSignOfColumn(i);
		}
	}
};
