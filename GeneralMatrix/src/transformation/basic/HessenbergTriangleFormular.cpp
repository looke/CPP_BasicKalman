/*
 * HessenbergTriangleFormular.cpp
 *
 *  Created on: 2017年4月28日
 *      Author: looke
 */

#include "HessenbergTriangleFormular.h"
#include <iostream>
using namespace std;

HessenbergTriangleFormular::HessenbergTriangleFormular()
{};

HessenbergTriangleFormular::HessenbergTriangleFormular(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B)
{
	this->init(input_Matrix_A, input_Matrix_B);
};

void HessenbergTriangleFormular::init(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B)
{
};

void HessenbergTriangleFormular::reload(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B)
{
};

BasicMatrix* HessenbergTriangleFormular::getMatrixA()
{
	return this->p_OpMatrix_A;
};

BasicMatrix* HessenbergTriangleFormular::getMatrixB()
{
	return this->p_OpMatrix_B;
};
BasicMatrix* HessenbergTriangleFormular::getHessenbergMatrixA()
{
	return this->p_OpHessenbergMatrix_A;
};
BasicMatrix* HessenbergTriangleFormular::getTriangleMatrixB()
{
	return this->p_OpTriangleMatrix_B;
};
BasicMatrix* HessenbergTriangleFormular::getMatrixQ_Total()
{
	return this->p_QMatrix_Total;
};

BasicMatrix* HessenbergTriangleFormular::getMatrixZ_Total()
{
	return this->p_ZMatrix_Total;
};

BasicMatrix* HessenbergTriangleFormular::getMatrixQ_Step()
{
	return this->p_QMatrix_Step;
};

BasicMatrix* HessenbergTriangleFormular::getMatrixZ_Step()
{
	return this->p_ZMatrix_Step;
};

void HessenbergTriangleFormular::formularABMatrix()
{
	p_QMatrix_Total->resetMatrixToI();
	p_ZMatrix_Total->resetMatrixToI();
	p_QMatrix_Step->resetMatrixToI();
	p_ZMatrix_Step->resetMatrixToI();
	if(this->p_OpMatrix_A->isUpperHessenbergMatrix() && this->p_OpMatrix_B->isUpperTriangleMatrix())
	{
		this->p_OpHessenbergMatrix_A->copyMatrixElementNoCheck(p_OpMatrix_A);
		this->p_OpTriangleMatrix_B->copyMatrixElementNoCheck(p_OpMatrix_B);
		return;
	}

	this->initABMatrix();
	cout << "After HessenBergTriangle init--- A:" << endl;
	p_OpHessenbergMatrix_A->printMatrix();
	cout << "After HessenBergTriangle init--- B:" << endl;
	p_OpTriangleMatrix_B->printMatrix();
	cout << "After HessenBergTriangle init--- Q Total:" << endl;
	p_QMatrix_Total->printMatrix();
	cout << "After HessenBergTriangle init--- Z Total:" << endl;
	p_ZMatrix_Total->printMatrix();

	for(int i=0; i<this->p_OpHessenbergMatrix_A->columnNum; i++)
	{
		this->formularColumnVector(i);
		//p_OpHessenbergMatrix_A->regularZeroElement();
		//p_OpTriangleMatrix_B->regularZeroElement();
	}
};


/*
 * 对A矩阵的指定列进行hessenberg格式化
 */
void HessenbergTriangleFormular::formularColumnVector(int columnIndex)
{
	double element,lowEdge;
	BasicVector* p_ColumnVector;
	//BasicMatrix* p_GivensMatrix;
	for(int i=this->p_OpHessenbergMatrix_A->rowNum-1; i>columnIndex+1; i--)
	{
		p_QMatrix_Step->resetMatrixToI();
		p_ZMatrix_Step->resetMatrixToI();
		//先计算更新A矩阵
		lowEdge = p_OpHessenbergMatrix_A->getLowEdge();
		element = p_OpHessenbergMatrix_A->getMatrixElementRegulared(i,columnIndex,lowEdge);
		if(0 != element)
		{
			p_ColumnVector = p_OpHessenbergMatrix_A->getColumnVector(columnIndex);

			this->p_GivensTrans->reload(p_ColumnVector);
			this->p_QMatrix_Step->copyMatrixElementNoCheck(this->p_GivensTrans->getGivensMatrixPreMultiple(i));
			cout << "After HessenBergTriangle--- Left Givens Matrix:" << i << endl;
			p_QMatrix_Step->printMatrix();

			updateMatrixByQ();
		}


/*
		cout << "After HessenBergTriangle--- A:" << i << endl;
		p_OpMatrix_A->printMatrix();
		cout << "After HessenBergTriangle--- B:" << i<< endl;
		p_OpMatrix_B->printMatrix();
		cout << "After HessenBergTriangle--- Q:" << i << endl;
		p_QMatrix_Total->printMatrix();
		cout << "After HessenBergTriangle--- Z:" << i << endl;
		p_ZMatrix_Total->printMatrix();
*/
		//接着计算更新B矩阵
		lowEdge = p_OpTriangleMatrix_B->getLowEdge();
		element = p_OpTriangleMatrix_B->getMatrixElementRegulared(i,i-1,lowEdge);
		if(0 != element)
		{
			p_ColumnVector = p_OpTriangleMatrix_B->getRowVector(i);
			cout << "p_OpTriangleMatrix_B:getRowVector:" << i << endl;
			p_ColumnVector->printVector();
			this->p_GivensTrans->reload(p_ColumnVector);
			//this->p_GivensTrans->setIsUsingPreElement(false);
			this->p_ZMatrix_Step->copyMatrixElementNoCheck(this->p_GivensTrans->getGivensMatrixAfterMultiple(i-1));
			cout << "After HessenBergTriangle--- Right Givens Matrix:" << i << endl;
			this->p_ZMatrix_Step->printMatrix();

			updateMatrixByZ();
		}


		updateQZMatrix_Total();

		cout << "After HessenBergTriangle--- A:" << i << endl;
		p_OpHessenbergMatrix_A->printMatrix();
		cout << "After HessenBergTriangle--- B:" << i<< endl;
		p_OpTriangleMatrix_B->printMatrix();
		cout << "After HessenBergTriangle--- Q:" << i << endl;
		p_QMatrix_Total->printMatrix();
		cout << "After HessenBergTriangle--- Z:" << i << endl;
		p_ZMatrix_Total->printMatrix();
	}
};


/*
 * 使用QT矩阵 更新操作矩阵
 *  QT * A
 *  QT * B
 */
void HessenbergTriangleFormular::updateMatrixByQ()
{
	//更新操作矩阵A
	this->p_Multiplier->reload(this->p_QMatrix_Step, p_OpHessenbergMatrix_A);
	p_Multiplier->multiplyCalc();
	this->p_OpHessenbergMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
	//this->p_OpMatrix_A->regularZeroElement();

	//更新操作矩阵B
	p_Multiplier->reload(this->p_QMatrix_Step, p_OpTriangleMatrix_B);
	p_Multiplier->multiplyCalc();
	this->p_OpTriangleMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
	//this->p_OpTriangleMatrix_B->regularZeroElement();

};

/*
 * 使用Z矩阵 更新操作矩阵
 *  A * Z
 *  B * Z
 */
void HessenbergTriangleFormular::updateMatrixByZ()
{
	//更新操作矩阵A
	p_Multiplier->reload(p_OpHessenbergMatrix_A, this->p_ZMatrix_Step);
	p_Multiplier->multiplyCalc();
	this->p_OpHessenbergMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
	//this->p_OpHessenbergMatrix_A->regularZeroElement();

	//更新操作矩阵B
	p_Multiplier->reload(p_OpTriangleMatrix_B, this->p_ZMatrix_Step);
	p_Multiplier->multiplyCalc();
	this->p_OpTriangleMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
	//this->p_OpTriangleMatrix_B->regularZeroElement();

};

void HessenbergTriangleFormular::updateQZMatrix_Total()
{
	//更新Q矩阵
	p_Multiplier->reload(this->p_QMatrix_Step, p_QMatrix_Total);
	p_Multiplier->multiplyCalc();
	this->p_QMatrix_Total->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());

	//更新Z矩阵
	p_Multiplier->reload(p_ZMatrix_Total, this->p_ZMatrix_Step);
	p_Multiplier->multiplyCalc();
	this->p_ZMatrix_Total->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

/*
 * 原始操作矩阵B 进行QR分解 化为上三角矩阵，并将QT左乘A
 */
void HessenbergTriangleFormular::initABMatrix()
{
	this->p_OpHessenbergMatrix_A->copyMatrixElementNoCheck(this->p_OpMatrix_A);
	this->p_OpTriangleMatrix_B->copyMatrixElementNoCheck(this->p_OpMatrix_B);

	this->p_QRDecomp->reload(this->p_OpMatrix_B);
	this->p_QRDecomp->calcQRMatrix();

	this->p_QMatrix_Step->copyMatrixElementNoCheck(this->p_QRDecomp->getQTMatrix());
	this->p_ZMatrix_Step->resetMatrixToI();

	updateMatrixByQ();
	updateMatrixByZ();
	updateQZMatrix_Total();
};
