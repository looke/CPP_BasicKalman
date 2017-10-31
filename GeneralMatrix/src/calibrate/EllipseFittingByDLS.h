/*
 * EllipseFittingByDLS.h
 *
 * ʹ��Direct Least Square������������Բ���
 *  Created on: 2017��4��29��
 *      Author: looke
 */

#ifndef CALIBRATE_ELLIPSEFITTINGBYDLS_H_
#define CALIBRATE_ELLIPSEFITTINGBYDLS_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\static\StaticMatrix.h"

class EllipseFittingByDLS
{
public:
	EllipseFittingByDLS(double (*p_input_mag_original)[3]);

	void generateMatrix_D();
	void generateMatrix_C();

	BasicMatrix* getMatrix_D();
	BasicMatrix* getMatrix_C();

private:
	//ԭʼ������������
	int originalDataNum;

	//ԭʼ�����Ʋ������� ָ��
	double (*p_mag_original)[3];

	//��������D
	StaticMatrix opMatrix_D;

	//��������C ��ΪԼ������
	StaticMatrix opMatrix_C;
};



#endif /* CALIBRATE_ELLIPSEFITTINGBYDLS_H_ */
