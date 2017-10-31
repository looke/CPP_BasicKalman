/*
 * EllipseFitting.cpp
 *
 *  Created on: 2017年4月12日
 *      Author: looke
 */


#include "calibrate\EllipseFitting.h"
//#include "static\static1511\Static1511Matrix.h"
#include "math.h"

#include <iostream>
using namespace std;

EllipseFitting::EllipseFitting(double (*input_mag_original)[3]):jacobiMatrix(),svd(&jacobiMatrix)
{
	//8000个样本点数据
	this->originalDataNum = 8000;

	//原始磁力计读数的缩放比例//MPU9250 磁力计数据0.15*10^-2 Guass / LSB
	this->ratio_magData = 1;
	//地磁强度  10^-2 Guass
	this->earth_magData = 340;

	//精度
	this->precision = 0.00001;

	//步长
	this->step = 200; //this->originalDataNum/15;
	//迭代最大次数
	this->iterateMaxNum = step/10;

	//
	this->diffMax = 1;

	//磁力计原始x,y,z读数
	this->mag_Wx = 0;
	this->mag_Wy = 0;
	this->mag_Wz = 0;

	//--- 未知参数初值
	//磁力计原点偏移量
	this->mag_Wx0 = -350.0*this->ratio_magData;
	this->mag_Wy0 = -200.0*this->ratio_magData;
	this->mag_Wz0 = -300.0*this->ratio_magData;

	//椭圆曲线参数矩阵各元素 3*3对称方阵 共6个元素
	this->ecllips_A11 = earth_magData/fabs(this->mag_Wx0);
	this->ecllips_A11 = ecllips_A11*ecllips_A11;
	this->ecllips_A12 = 0;
	this->ecllips_A13 = 0;
	this->ecllips_A22 = earth_magData/fabs(this->mag_Wy0);
	this->ecllips_A22 = ecllips_A22*ecllips_A22;
	this->ecllips_A23 = 0;
	this->ecllips_A33 = earth_magData/fabs(this->mag_Wz0);
	this->ecllips_A33 = ecllips_A33*ecllips_A33;

	//--- 未知参数迭代结果
	//磁力计原点偏移量
	this->mag_Wx0_it = 0;
	this->mag_Wy0_it = 0;
	this->mag_Wz0_it = 0;

	//椭圆曲线参数矩阵各元素 3*3对称方阵 共6个元素
	this->ecllips_A11_it = 1;
	this->ecllips_A12_it = 0;
	this->ecllips_A13_it = 0;
	this->ecllips_A22_it = 1;
	this->ecllips_A23_it = 0;
	this->ecllips_A33_it = 1;
	//地磁强度  Guass
	this->earth_magData_it = 0;

	//初始化原始磁力计数据源
	this->p_mag_original = input_mag_original;

	/*
	int i=0;
	while(i<3000)
	{
		this->mag_original[i][0] = input_mag_original[i][0];
		this->mag_original[i][1] = input_mag_original[i][1];
		this->mag_original[i][2] = input_mag_original[i][2];
		i++;
	}
	*/

	//Jacobi矩阵初始化
	jacobiMatrix = StaticMatrix(15,11);
	this->p_jacobiMatrix = &jacobiMatrix;

	//svd分解器初始化
	//this->svd = StaticMatrixSingularValueDecomposition(this->p_jacobiMatrix);
	this->p_matrix_SVD_Decomp = &svd;

	//初始化三轴极限值索引
	findOriginalMagData3AxisMaxMinIndex();

};

// dF/dA11 ----> (Wx-Wx0)^2
double EllipseFitting::dFdA11_calc()
{
	return (mag_Wx-mag_Wx0)*(mag_Wx-mag_Wx0);
};

// dF/dA12 ----> 2*(Wx-Wx0)*(Wy-Wy0)
double EllipseFitting::dFdA12_calc()
{
	return 2*(mag_Wx-mag_Wx0)*(mag_Wy-mag_Wy0);
};

// dF/dA13 ----> 2*(Wx-Wx0)*(Wz-Wz0)
double EllipseFitting::dFdA13_calc()
{
	return 2*(mag_Wx-mag_Wx0)*(mag_Wz-mag_Wz0);
};

// dF/dA22 ----> (Wy-Wy0)^2
double EllipseFitting::dFdA22_calc()
{
	return (mag_Wy-mag_Wy0)*(mag_Wy-mag_Wy0);
};

// dF/dA23 ----> 2*(Wy-Wy0)*(Wz-Wz0)
double EllipseFitting::dFdA23_calc()
{
	return 2*(mag_Wy-mag_Wy0)*(mag_Wz-mag_Wz0);
};

// dF/dA33 ----> (Wz-Wz0)^2
double EllipseFitting::dFdA33_calc()
{
	return (mag_Wz-mag_Wz0)*(mag_Wz-mag_Wz0);
};

//dF/dWx0
double EllipseFitting::dFdWx0_calc()
{
	double temp = (mag_Wx-mag_Wx0)*ecllips_A11 + (mag_Wy-mag_Wy0)*ecllips_A12 + (mag_Wz-mag_Wz0)*ecllips_A13;
	temp = 0 - 2*temp;
	return temp;
};

//dF/dWy0
double EllipseFitting::dFdWy0_calc()
{
	double temp = (mag_Wy-mag_Wy0)*ecllips_A22 + (mag_Wx-mag_Wx0)*ecllips_A12 + (mag_Wz-mag_Wz0)*ecllips_A23;
	temp = 0 - 2*temp;
	return temp;
};

//dF/dWz0
double EllipseFitting::dFdWz0_calc()
{
	double temp = (mag_Wz-mag_Wz0)*ecllips_A33 + (mag_Wx-mag_Wx0)*ecllips_A13 + (mag_Wy-mag_Wy0)*ecllips_A23;
	temp = 0 - 2*temp;
	return temp;
};

//dF/dC
double EllipseFitting::dFdC_calc()
{
	//return -1.0;
	return 0-2.0*earth_magData;
};

double EllipseFitting::F_calc()
{
	double part0;
	double part1;
	double part2;
	double part3;
	double part4;
	double part5;
	double part6;

	part0 = (mag_Wx-mag_Wx0)*(mag_Wx-mag_Wx0)*ecllips_A11;
	part1 = (mag_Wy-mag_Wy0)*(mag_Wy-mag_Wy0)*ecllips_A22;
	part2 = (mag_Wz-mag_Wz0)*(mag_Wz-mag_Wz0)*ecllips_A33;

	part3 = 2*(mag_Wx-mag_Wx0)*(mag_Wy-mag_Wy0)*ecllips_A12;
	part4 = 2*(mag_Wx-mag_Wx0)*(mag_Wz-mag_Wz0)*ecllips_A13;
	part5 = 2*(mag_Wy-mag_Wy0)*(mag_Wz-mag_Wz0)*ecllips_A23;

	part6 = earth_magData*earth_magData;
	//part6 = earth_magData;
	return 0-(part0+part1+part2+part3+part4+part5-part6);
};

/*
 *  计算当前迭代结果与前一次迭代结果的差值的最大值DiffMax
 */
void EllipseFitting::calcMaxIterateDiff()
{
	diffMax = 0;
	double temp = fabs(this->ecllips_A11_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->ecllips_A12_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->ecllips_A13_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->ecllips_A22_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->ecllips_A23_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->ecllips_A33_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->mag_Wx0_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->mag_Wy0_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->mag_Wz0_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}

	temp = fabs(this->earth_magData_it);
	if(diffMax < temp)
	{
		diffMax = temp;
	}
};

/*
 *  根据迭代结果和当前迭代次数生成牛顿迭代的Jacobi矩阵,SVD分解器使用该矩阵进行总体最小二乘求解
 */
void EllipseFitting::updateJacobiMatrix(int iterateNum)
{
	//使用15组数据,生成15*11的Jacobi矩阵
	cout << "#######Picking Original Mag Data" << endl;
	int index;

	for(int i=0; i<6; i++)
	{
		index = mag_maxData_index[i];
		cout << "Time:" << i << "  X:" << p_mag_original[index][0] << " Y:" << p_mag_original[index][1] << " Z:" << p_mag_original[index][2] <<endl;
		this->mag_Wx = this->p_mag_original[index][0] * this->ratio_magData;
		this->mag_Wy = this->p_mag_original[index][1] * this->ratio_magData;
		this->mag_Wz = this->p_mag_original[index][2] * this->ratio_magData;

		//dF
		this->p_jacobiMatrix->setMatrixElement(i,0,this->dFdA11_calc());
		this->p_jacobiMatrix->setMatrixElement(i,1,this->dFdA12_calc());
		this->p_jacobiMatrix->setMatrixElement(i,2,this->dFdA13_calc());
		this->p_jacobiMatrix->setMatrixElement(i,3,this->dFdA22_calc());
		this->p_jacobiMatrix->setMatrixElement(i,4,this->dFdA23_calc());
		this->p_jacobiMatrix->setMatrixElement(i,5,this->dFdA33_calc());
		this->p_jacobiMatrix->setMatrixElement(i,6,this->dFdWx0_calc());
		this->p_jacobiMatrix->setMatrixElement(i,7,this->dFdWy0_calc());
		this->p_jacobiMatrix->setMatrixElement(i,8,this->dFdWz0_calc());
		this->p_jacobiMatrix->setMatrixElement(i,9,this->dFdC_calc());
		//F
		this->p_jacobiMatrix->setMatrixElement(i,10,this->F_calc());
	}


	for(int i=6; i<p_jacobiMatrix->rowNum; i++)
	{
		index = iterateNum + this->step*i;
		cout << "Time:" << i << "  X:" << p_mag_original[index][0] << " Y:" << p_mag_original[index][1] << " Z:" << p_mag_original[index][2] <<endl;
		this->mag_Wx = this->p_mag_original[index][0] * this->ratio_magData;
		this->mag_Wy = this->p_mag_original[index][1] * this->ratio_magData;
		this->mag_Wz = this->p_mag_original[index][2] * this->ratio_magData;

		//dF
		this->p_jacobiMatrix->setMatrixElement(i,0,this->dFdA11_calc());
		this->p_jacobiMatrix->setMatrixElement(i,1,this->dFdA12_calc());
		this->p_jacobiMatrix->setMatrixElement(i,2,this->dFdA13_calc());
		this->p_jacobiMatrix->setMatrixElement(i,3,this->dFdA22_calc());
		this->p_jacobiMatrix->setMatrixElement(i,4,this->dFdA23_calc());
		this->p_jacobiMatrix->setMatrixElement(i,5,this->dFdA33_calc());
		this->p_jacobiMatrix->setMatrixElement(i,6,this->dFdWx0_calc());
		this->p_jacobiMatrix->setMatrixElement(i,7,this->dFdWy0_calc());
		this->p_jacobiMatrix->setMatrixElement(i,8,this->dFdWz0_calc());
		this->p_jacobiMatrix->setMatrixElement(i,9,this->dFdC_calc());
		//F
		this->p_jacobiMatrix->setMatrixElement(i,10,this->F_calc());
	}

};

//计算拟合结果
bool EllipseFitting::TLS_Fitting()
{
	int i=0; //当前迭代次数
	int noSolveNum = 0;
	bool isSuccess = false;
	cout << "#######TLS Iteration Start" << endl;
	//当精度未达到要求,持续循环迭代过程,直到最大迭代次数到达
	while(this->diffMax > this->precision && i<this->iterateMaxNum)
	{
		cout << "#######TLS Iteration: " << i << endl;
		//首先更新Jacobi矩阵
		updateJacobiMatrix(i);
		cout << "#######New Jacobi Matrix:" << endl;
		printJacobiMatrix();
		//SVD分解
		p_matrix_SVD_Decomp->reload(this->p_jacobiMatrix);
		p_matrix_SVD_Decomp->sigularValueDecomposition(1);

		//判断TLS解是否唯一存在
		//15*10 奇异值矩阵
		BasicMatrix* p_SingularValueMatrix = p_matrix_SVD_Decomp->getSingularValueMatrix();
		cout << "#######S Matrix:" << endl;
		p_SingularValueMatrix->printMatrix();
		//10*10 右奇异矩阵V
		BasicMatrix* p_VMatrix = p_matrix_SVD_Decomp->getVMatrix();
		cout << "#######V Matrix:" << endl;
		p_VMatrix->printMatrix();

		if(p_SingularValueMatrix->getMatrixElement(p_jacobiMatrix->columnNum-2,p_jacobiMatrix->columnNum-2) > p_SingularValueMatrix->getMatrixElement(p_jacobiMatrix->columnNum-1,p_jacobiMatrix->columnNum-1)
		  && 0!= p_VMatrix->getMatrixElement(p_jacobiMatrix->columnNum-1,p_jacobiMatrix->columnNum-1))
		{
			//存在TLS解
			//求解,并赋值
			double temp = p_VMatrix->getMatrixElement(p_jacobiMatrix->columnNum-1,p_jacobiMatrix->columnNum-1);

			//椭圆曲线参数矩阵各元素 3*3对称方阵 共6个元素
			this->ecllips_A11_it = 0-p_VMatrix->getMatrixElement(0,p_jacobiMatrix->columnNum-1)/temp;
			this->ecllips_A12_it = 0-p_VMatrix->getMatrixElement(1,p_jacobiMatrix->columnNum-1)/temp;
			this->ecllips_A13_it = 0-p_VMatrix->getMatrixElement(2,p_jacobiMatrix->columnNum-1)/temp;
			this->ecllips_A22_it = 0-p_VMatrix->getMatrixElement(3,p_jacobiMatrix->columnNum-1)/temp;
			this->ecllips_A23_it = 0-p_VMatrix->getMatrixElement(4,p_jacobiMatrix->columnNum-1)/temp;
			this->ecllips_A33_it = 0-p_VMatrix->getMatrixElement(5,p_jacobiMatrix->columnNum-1)/temp;

			//磁力计原点偏移量
			this->mag_Wx0_it = 0-p_VMatrix->getMatrixElement(6,p_jacobiMatrix->columnNum-1)/temp;
			this->mag_Wy0_it = 0-p_VMatrix->getMatrixElement(7,p_jacobiMatrix->columnNum-1)/temp;
			this->mag_Wz0_it = 0-p_VMatrix->getMatrixElement(8,p_jacobiMatrix->columnNum-1)/temp;

			//地磁强度
			this->earth_magData_it = 0-p_VMatrix->getMatrixElement(9,p_jacobiMatrix->columnNum-1)/temp;

			//更新DiffMax
			this->calcMaxIterateDiff();
			cout << "#######DiffMax: " << this->diffMax << endl;

			//更新迭代初始值
			this->updateIterateParaValue();
		}
		else
		{
			noSolveNum++;
			//如果TSL不存在解的次数超过3次,则退出迭代
			if(noSolveNum >= 3)
			{
				break;
			}
		}
		i++;
	}

	if(this->diffMax <= this->precision)
	{
		isSuccess = true;
	}

	return isSuccess;
};


double EllipseFitting::getDiffMax()
{
	return this->diffMax;
};

void EllipseFitting::printJacobiMatrix()
{
	this->p_jacobiMatrix->printMatrix();
};

//更新迭代相关参数的取值
void EllipseFitting::updateIterateParaValue()
{
	//磁力计原点偏移量
	this->mag_Wx0 += this->mag_Wx0_it;
	this->mag_Wy0 += this->mag_Wy0_it;
	this->mag_Wz0 += this->mag_Wz0_it;

	//椭圆曲线参数矩阵各元素 3*3对称方阵 共6个元素
	this->ecllips_A11 += this->ecllips_A11_it;
	this->ecllips_A12 += this->ecllips_A12_it;
	this->ecllips_A13 += this->ecllips_A13_it;
	this->ecllips_A22 += this->ecllips_A22_it;
	this->ecllips_A23 += this->ecllips_A23_it;
	this->ecllips_A33 += this->ecllips_A33_it;

	//地磁强度
	this->earth_magData += earth_magData_it;
};

/*
 * 根据原始磁力计数据,查找3轴最大最小取值所在位置
 */
void EllipseFitting::findOriginalMagData3AxisMaxMinIndex()
{
	int x_max_temp = -99999;
	int x_min_temp = 99999;
	int y_max_temp = -99999;
	int y_min_temp = 99999;
	int z_max_temp = -99999;
	int z_min_temp = 99999;

	int i=0;
	while(i < this->originalDataNum)
	{
		if(this->p_mag_original[i][0] > x_max_temp)
		{
			x_max_temp = p_mag_original[i][0];
			this->mag_original_index_x_Max = i;
		}
		if(this->p_mag_original[i][0] < x_min_temp)
		{
			x_min_temp = p_mag_original[i][0];
			this->mag_original_index_x_Min = i;
		}

		if(this->p_mag_original[i][1] > y_max_temp)
		{
			y_max_temp = p_mag_original[i][1];
			this->mag_original_index_y_Max = i;
		}
		if(this->p_mag_original[i][1] < y_min_temp)
		{
			y_min_temp = p_mag_original[i][1];
			this->mag_original_index_y_Min = i;
		}

		if(this->p_mag_original[i][2] > z_max_temp)
		{
			z_max_temp = p_mag_original[i][2];
			this->mag_original_index_z_Max = i;
		}
		if(this->p_mag_original[i][2] < z_min_temp)
		{
			z_min_temp = p_mag_original[i][2];
			this->mag_original_index_z_Min = i;
		}
		i++;
	}

	mag_maxData_index[0] = this->mag_original_index_x_Max;
	mag_maxData_index[1] = this->mag_original_index_x_Min;
	mag_maxData_index[2] = this->mag_original_index_y_Max;
	mag_maxData_index[3] = this->mag_original_index_y_Min;
	mag_maxData_index[4] = this->mag_original_index_z_Max;
	mag_maxData_index[5] = this->mag_original_index_z_Min;

};
