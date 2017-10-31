/*
 * HessenbergTriangleFormular.h
 *
 *  Created on: 2017年4月28日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_HESSENBERGTRIANGLEFORMULAR_H_
#define TRANSFORMATION_BASIC_HESSENBERGTRIANGLEFORMULAR_H_

#include "..\matrix\basic\BasicMatrix.h"
//#include "..\vector\basic\BasicVector.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "..\transformation\basic\QRDecomposition.h"
#include "GivensTransformation.h"


class HessenbergTriangleFormular
{
public:
	HessenbergTriangleFormular();
	HessenbergTriangleFormular(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);

	void initABMatrix();
	void formularABMatrix();
	void formularColumnVector(int columnIndex);

	void updateMatrixByQ();
	void updateMatrixByZ();

	void updateQZMatrix_Total();


	BasicMatrix* getMatrixA();
	BasicMatrix* getMatrixB();
	BasicMatrix* getHessenbergMatrixA();
	BasicMatrix* getTriangleMatrixB();
	BasicMatrix* getMatrixQ_Step();
	BasicMatrix* getMatrixZ_Step();
	BasicMatrix* getMatrixQ_Total();
	BasicMatrix* getMatrixZ_Total();


	virtual void init(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);
	virtual void reload(BasicMatrix* input_Matrix_A, BasicMatrix* input_Matrix_B);

	virtual ~HessenbergTriangleFormular(){};
protected:

	//原始操作方阵A
	BasicMatrix* p_OpMatrix_A;
	//原始操作方阵B
	BasicMatrix* p_OpMatrix_B;

	//Hessenberg方阵A
	BasicMatrix* p_OpHessenbergMatrix_A;

	//上三角方阵B
	BasicMatrix* p_OpTriangleMatrix_B;

	//总体Q变换矩阵,用于汇总左乘操作矩阵
	BasicMatrix* p_QMatrix_Total;

	//总体Z变换矩阵,用于汇总右乘操作矩阵
	BasicMatrix* p_ZMatrix_Total;

	//单步Q变换矩阵,用于左乘操作矩阵
	BasicMatrix* p_QMatrix_Step;

	//单步Z变换矩阵,用于右乘操作矩阵
	BasicMatrix* p_ZMatrix_Step;

	//Q* A Z--->Hessenberg矩阵
	//Q* B Z--->上三角矩阵

	//QR分解
	QRDecomposition* p_QRDecomp;

	//Givens变换
	GivensTransformation* p_GivensTrans;

	//乘法器
	MatrixMultiplier* p_Multiplier;

private:

};

#endif /* TRANSFORMATION_BASIC_HESSENBERGTRIANGLEFORMULAR_H_ */
