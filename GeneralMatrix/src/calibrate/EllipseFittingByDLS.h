/*
 * EllipseFittingByDLS.h
 *
 * 使用Direct Least Square方法，计算椭圆拟合
 *  Created on: 2017年4月29日
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
	//原始磁力计数据量
	int originalDataNum;

	//原始磁力计采样数据 指针
	double (*p_mag_original)[3];

	//操作矩阵D
	StaticMatrix opMatrix_D;

	//操作矩阵C 作为约束矩阵
	StaticMatrix opMatrix_C;
};



#endif /* CALIBRATE_ELLIPSEFITTINGBYDLS_H_ */
