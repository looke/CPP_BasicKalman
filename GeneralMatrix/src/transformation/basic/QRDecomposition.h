/*
 * QRDecomposition.h
 *
 *  Created on: 2017��4��25��
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

	//���²��������Q����
	void updateMatrix();

	//����HouseHolder�任����
	void generateHouseholderMatrix(int index);


	BasicMatrix* getQMatrix();
	BasicMatrix* getQTMatrix();
	BasicMatrix* getRMatrix();
	BasicMatrix* getHouseholderMatrix();


	virtual ~QRDecomposition(){};

private:

protected:

	//�˷���
	MatrixMultiplier* p_Multiplier;

	//householder�任
	HouseholderTransformation* p_HouseholderTrans;

	//�������󣬾��������󽫱���϶ԽǾ���
	BasicMatrix* p_OpMatrix;

	//householder����ÿ�ε���ʹ��
	BasicMatrix* p_householderMatrix;

	//Q����
	BasicMatrix* p_QMatrix;

	//Q�����ת��(�����)
	BasicMatrix* p_QTMatrix;
};


#endif /* TRANSFORMATION_BASIC_QRDECOMPOSITION_H_ */
