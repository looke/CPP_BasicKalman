/*
 * QRDecomposition.h
 *
 *  Created on: 2017年4月25日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_QRDECOMPOSITION_H_
#define TRANSFORMATION_BASIC_QRDECOMPOSITION_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "HouseholderTransformation.h"

class QRDecomposition
{

public:

	QRDecomposition();
	QRDecomposition(BasicMatrix* input_Matrix);

	virtual void init(BasicMatrix* input_Matrix);
	virtual void reload(BasicMatrix* input_Matrix);

	void calcQRMatrix();

	//更新操作矩阵和Q矩阵
	void updateMatrix();

	//生成HouseHolder变换矩阵
	void generateHouseholderMatrix(int index);


	BasicMatrix* getQMatrix();
	BasicMatrix* getQTMatrix();
	BasicMatrix* getRMatrix();
	BasicMatrix* getHouseholderMatrix();


	virtual ~QRDecomposition(){};

private:

protected:

	//乘法器
	MatrixMultiplier* p_Multiplier;

	//householder变换
	HouseholderTransformation* p_HouseholderTrans;

	//操作矩阵，经过迭代后将变成上对角矩阵
	BasicMatrix* p_OpMatrix;

	//householder矩阵，每次迭代使用
	BasicMatrix* p_householderMatrix;

	//Q矩阵
	BasicMatrix* p_QMatrix;

	//Q矩阵的转置(逆矩阵)
	BasicMatrix* p_QTMatrix;
};


#endif /* TRANSFORMATION_BASIC_QRDECOMPOSITION_H_ */
