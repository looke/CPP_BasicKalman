/*
 * EllipseFitting.h
 * ʹ�� ţ�ٵ��� + ������С���˷� ������Բ���
 *  Created on: 2017��4��11��
 *      Author: looke
 */

#ifndef CALIBRATE_ELLIPSEFITTING_H_
#define CALIBRATE_ELLIPSEFITTING_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\static\StaticMatrix.h"
#include "..\matrix\static\util\StaticMatrixSingularValueDecomposition.h"

class EllipseFitting
{
public:
	//EllipseFitting();
	EllipseFitting(double (*input_mag_original)[3]);
	//��ʽF
	double F_calc();

	//��ʽF�ĸ�δ֪����ƫ����
	double dFdA11_calc();
	double dFdA12_calc();
	double dFdA13_calc();
	double dFdA22_calc();
	double dFdA23_calc();
	double dFdA33_calc();

	double dFdWx0_calc();
	double dFdWy0_calc();
	double dFdWz0_calc();
	double dFdC_calc();
	//������Ͻ��
	bool TLS_Fitting();

	//���㵱ǰ����ֵ��ǰһ�ε���ֵ������ֵ
	void calcMaxIterateDiff();

	//����Jacobi����
	void updateJacobiMatrix(int iterateNum);

	//���µ�����ز�����ȡֵ
	void updateIterateParaValue();

	double getDiffMax();
	void printJacobiMatrix();
	void findOriginalMagData3AxisMaxMinIndex();
private:
	//ԭʼ������������
	int originalDataNum;
	//����ֹͣ����
	double precision;

	//ԭʼ�����Ʋ������� ָ��
	double (*p_mag_original)[3];
	//ԭʼ�����Ʋ����������������Сֵ��������
	int mag_original_index_x_Max;
	int mag_original_index_x_Min;
	int mag_original_index_y_Max;
	int mag_original_index_y_Min;
	int mag_original_index_z_Max;
	int mag_original_index_z_Min;

	int mag_maxData_index[6];
	//���ݴ�����
	int step;
	//����������
	int iterateMaxNum;

	//ÿ�ε�����������ǰ�ε������������ֵ
	double diffMax;

	//--- ��֪����
	//������ԭʼx,y,z����
	double mag_Wx;
	double mag_Wy;
	double mag_Wz;

	//--- δ֪����
	//������ԭ��ƫ����
	double mag_Wx0;
	double mag_Wy0;
	double mag_Wz0;

	//��Բ���߲��������Ԫ�� 3*3�ԳƷ��� ��6��Ԫ��
	double ecllips_A11;
	double ecllips_A12;
	double ecllips_A13;
	double ecllips_A22;
	double ecllips_A23;
	double ecllips_A33;
	//�ش�ǿ�� Guass
	double earth_magData;

	//--- δ֪�����������
	//������ԭ��ƫ����
	double mag_Wx0_it;
	double mag_Wy0_it;
	double mag_Wz0_it;

	//��Բ���߲��������Ԫ�� 3*3�ԳƷ��� ��6��Ԫ��
	double ecllips_A11_it;
	double ecllips_A12_it;
	double ecllips_A13_it;
	double ecllips_A22_it;
	double ecllips_A23_it;
	double ecllips_A33_it;
	//�ش�ǿ�� Guass
	double earth_magData_it;


	//MPU9250 ����������0.15*10^-2 Guass / LSB
	double ratio_magData;

	//Jacobi��������
	StaticMatrix jacobiMatrix;
	BasicMatrix* p_jacobiMatrix;

	//��������ֵ�ֽ���
	StaticMatrixSingularValueDecomposition svd;
	StaticMatrixSingularValueDecomposition* p_matrix_SVD_Decomp;


};

#endif /* CALIBRATE_ELLIPSEFITTING_H_ */
