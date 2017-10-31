/*
 * HessenbergDeflation.cpp
 *
 *  Created on: 2017年6月1日
 *      Author: looke
 */

#include "HessenbergDeflation.h"

HessenbergDeflation::HessenbergDeflation()
{
	this->deflateStart_new = 0;
	this->deflateEnd_new = 0;
};

/*
 * 查找并更新降阶点
 * 在全尺寸操作Hessenberg矩阵中，从右下到左上开始，次主对角线上查找0元
 * 找到0元后，分析0元右下角的子矩阵，是否维度大于2（是否可以进行double-shift迭代）
 * 如果不能迭代，更新降阶结束标识位，继续寻找新的0元
 * 如果可以迭代，更新降阶开始标识位，结束
 */
bool HessenbergDeflation::findNewDeflationPoint(BasicMatrix* p_HessenbergMatrix, int deflationStart, int deflationEnd)
{
	bool result = false;
	double temp;
	int deflatedSize; //降阶点右下角矩阵维度
	this->deflateStart_new = deflationStart;
	this->deflateEnd_new = deflationEnd;
	int i=deflationEnd;
	while(i > 0)
	{
		//查询次对角线元素
		temp = p_HessenbergMatrix->getMatrixElement(i,i-1);
		if(temp == 0)
		{
			//次对角线元素为0，分析降阶点
			deflatedSize = this->deflateEnd_new-i+1;

			if(deflatedSize>2)
			{
				//如果降阶点右下方子矩阵维度大于2，则可以进行迭代处理
				this->deflateStart_new = i;
				//this->deflateEnd_new = deflationEnd;
				return true;
			}
			else
			{
				//如果降阶点右下方子矩阵维度小于等于2
				//更新降阶开始及结束点标识
				this->deflateEnd_new = i - 1;
				//this->deflateStart_new = 0;
			}
			result = true;
		}
		i--;
	}

	return result;
};

int HessenbergDeflation::getNewDeflationStart()
{
	return this->deflateStart_new;
};
int HessenbergDeflation::getNewDeflationEnd()
{
	return this->deflateEnd_new;
};
