/*
 * EllipseFittingByDLS.cpp
 *
 *  Created on: 2017年4月29日
 *      Author: looke
 */


#include "EllipseFittingByDLS.h"

EllipseFittingByDLS::EllipseFittingByDLS(double (*p_input_mag_original)[3])
{
	//初始化原始磁力计数据源
	this->p_mag_original = p_input_mag_original;

	//原始磁力计数据量
	this->originalDataNum = 8000;

	this->opMatrix_D = StaticMatrix(15,10);

	this->opMatrix_C = StaticMatrix(15,10);
};

void EllipseFittingByDLS::generateMatrix_C()
{
	this->opMatrix_C.resetMatrixToZero();
	this->opMatrix_C.setMatrixElement(0,2,2);
	this->opMatrix_C.setMatrixElement(1,1,-1);
	this->opMatrix_C.setMatrixElement(2,0,2);
};

void EllipseFittingByDLS::generateMatrix_D()
{
	double mag_Wx;
	double mag_Wy;
	double mag_Wz;

	int step = 500;
	int index;
	for(int i=0; i<this->opMatrix_D.rowNum; i++)
	{
		index = step*(i+1);
		mag_Wx = this->p_mag_original[index][0];
		mag_Wy = this->p_mag_original[index][1];
		mag_Wz = this->p_mag_original[index][2];

		//a*mag_x^2
		this->opMatrix_D.setMatrixElement(i,0,mag_Wx*mag_Wx);

		//b*mag_x*mag_y
		this->opMatrix_D.setMatrixElement(i,1,mag_Wx*mag_Wy);

		//c*mag_y^2
		this->opMatrix_D.setMatrixElement(i,2,mag_Wy*mag_Wy);

		//d*mag_x*mag_z
		this->opMatrix_D.setMatrixElement(i,3,mag_Wx*mag_Wz);

		//e*mag_y*mag_z
		this->opMatrix_D.setMatrixElement(i,4,mag_Wy*mag_Wz);

		//j*mag_z^2
		this->opMatrix_D.setMatrixElement(i,5,mag_Wz*mag_Wz);

		//p*mag_x
		this->opMatrix_D.setMatrixElement(i,6,mag_Wx);

		//q*mag_y
		this->opMatrix_D.setMatrixElement(i,7,mag_Wy);

		//r*mag_y
		this->opMatrix_D.setMatrixElement(i,8,mag_Wz);

		//s*1
		this->opMatrix_D.setMatrixElement(i,9,1);
	}
};

BasicMatrix* EllipseFittingByDLS::getMatrix_D()
{
	return &this->opMatrix_D;
};
BasicMatrix* EllipseFittingByDLS::getMatrix_C()
{
	return &this->opMatrix_C;
};
