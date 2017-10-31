/*
 * EllipseFitting.h
 * 使用 牛顿迭代 + 总体最小二乘法 计算椭圆拟合
 *  Created on: 2017年4月11日
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
	//等式F
	double F_calc();

	//等式F的各未知数的偏导数
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
	//计算拟合结果
	bool TLS_Fitting();

	//计算当前迭代值与前一次迭代值的最大差值
	void calcMaxIterateDiff();

	//更新Jacobi矩阵
	void updateJacobiMatrix(int iterateNum);

	//更新迭代相关参数的取值
	void updateIterateParaValue();

	double getDiffMax();
	void printJacobiMatrix();
	void findOriginalMagData3AxisMaxMinIndex();
private:
	//原始磁力计数据量
	int originalDataNum;
	//迭代停止精度
	double precision;

	//原始磁力计采样数据 指针
	double (*p_mag_original)[3];
	//原始磁力计采样三轴数据最大最小值所在索引
	int mag_original_index_x_Max;
	int mag_original_index_x_Min;
	int mag_original_index_y_Max;
	int mag_original_index_y_Min;
	int mag_original_index_z_Max;
	int mag_original_index_z_Min;

	int mag_maxData_index[6];
	//数据处理步长
	int step;
	//迭代最大次数
	int iterateMaxNum;

	//每次迭代计算结果与前次迭代结果的最大差值
	double diffMax;

	//--- 已知参数
	//磁力计原始x,y,z读数
	double mag_Wx;
	double mag_Wy;
	double mag_Wz;

	//--- 未知参数
	//磁力计原点偏移量
	double mag_Wx0;
	double mag_Wy0;
	double mag_Wz0;

	//椭圆曲线参数矩阵各元素 3*3对称方阵 共6个元素
	double ecllips_A11;
	double ecllips_A12;
	double ecllips_A13;
	double ecllips_A22;
	double ecllips_A23;
	double ecllips_A33;
	//地磁强度 Guass
	double earth_magData;

	//--- 未知参数迭代结果
	//磁力计原点偏移量
	double mag_Wx0_it;
	double mag_Wy0_it;
	double mag_Wz0_it;

	//椭圆曲线参数矩阵各元素 3*3对称方阵 共6个元素
	double ecllips_A11_it;
	double ecllips_A12_it;
	double ecllips_A13_it;
	double ecllips_A22_it;
	double ecllips_A23_it;
	double ecllips_A33_it;
	//地磁强度 Guass
	double earth_magData_it;


	//MPU9250 磁力计数据0.15*10^-2 Guass / LSB
	double ratio_magData;

	//Jacobi超定矩阵
	StaticMatrix jacobiMatrix;
	BasicMatrix* p_jacobiMatrix;

	//矩阵奇异值分解器
	StaticMatrixSingularValueDecomposition svd;
	StaticMatrixSingularValueDecomposition* p_matrix_SVD_Decomp;


};

#endif /* CALIBRATE_ELLIPSEFITTING_H_ */
