/*
 * QZTriangleZeroChasing.h
 * QZ法,B矩阵 主对角线0元下降
 * 将上三角矩阵B的主对角线0元下降到主对角线右下角
 *
 * 基本思路:
 * 各阶左上子矩阵迭代进行，首先从原矩阵(n阶)开始，如果找到主对角线0元，将一个零元赶到右下
 * 然后对左上n-1阶子矩阵进行同样的操作，直到无法找到主对角线0元
 *
 *
 *  Created on: 2017年4月28日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_QZTRIANGLEZEROCHASING_H_
#define TRANSFORMATION_BASIC_QZTRIANGLEZEROCHASING_H_

//#include "..\matrix\basic\BasicMatrix.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
#include "..\transformation\basic\GivensTransformation.h"

class QZTriangleZeroChasing
{
public:
	QZTriangleZeroChasing();
	QZTriangleZeroChasing(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);

	//降零元
	void deflate();

	BasicMatrix* getOpMatrix_A();
	BasicMatrix* getOpMatrix_B();

	BasicMatrix* getGivensMatrix_Q_Total();
	BasicMatrix* getGivensMatrix_Z_Total();

	BasicMatrix* getGivensMatrix_Q_Iterate();
	BasicMatrix* getGivensMatrix_Z_Iterate();

	BasicMatrix* getGivensMatrix_Q_Step();
	BasicMatrix* getGivensMatrix_Z_Step();

	BasicMatrix* getOpSubMatrix_A();
	BasicMatrix* getOpSubMatrix_B();

	BasicMatrix* getGivensSubMatrix_Q_Step();
	BasicMatrix* getGivensSubMatrix_Z_Step();

	virtual void init(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);
	virtual void reload(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B);
	virtual ~QZTriangleZeroChasing(){};


	//根据当前迭代次数 生成左上子矩阵
	void generateSubMatrix(int iterateNum);

	//根据行索引,对A子矩阵生成 Z变换矩阵
	void generateGivensSubMatrixForA(int index);

	//根据列索引,对B子矩阵生成 G变换矩阵
	void generateGivensSubMatrixForB(int index);

	//对A子矩阵生成 Z变换矩阵 使得A子矩阵最后一行的角次主对角元为0
	void generateGivensSubMatrixForA_last();


	//将Givens变换子矩阵升级成为全维度变换矩阵
	void upgradeGivensSubMatrix_Q();
	void upgradeGivensSubMatrix_Z();

	//更新迭代过程Givens变换矩阵
	void updateGivensMatrix_Iterate_Q();
	void updateGivensMatrix_Iterate_Z();

	//更新总体综合Givens变换矩阵
	void updateGivensMatrix_Total_Q();
	void updateGivensMatrix_Total_Z();

	//使用G子矩阵更新A子操作矩阵
	void updateSubOpMatrix_A_By_Q();
	//使用Z子矩阵更新A子操作矩阵
	void updateSubOpMatrix_A_By_Z();
	//使用G子矩阵更新B子操作矩阵
	void updateSubOpMatrix_B_By_Q();
	//使用Z子矩阵更新B子操作矩阵
	void updateSubOpMatrix_B_By_Z();

	//使用G矩阵更新A操作矩阵
	void updateOpMatrix_A_By_Q();
	//使用Z矩阵更新A操作矩阵
	void updateOpMatrix_A_By_Z();
	//使用G矩阵更新B操作矩阵
	void updateOpMatrix_B_By_Q();
	//使用Z矩阵更新B操作矩阵
	void updateOpMatrix_B_By_Z();

	//根据迭代情况重新定义子矩阵行列数
	void resizeSubMatrix(int rowAndColumnNumber);


protected:
	//降0元后，新的矩阵底部索引
	int deflate_End_New;
	//原始矩阵A Hessenberg
	BasicMatrix* p_OpMatrix_A;
	//原始矩阵B 上三角
	BasicMatrix* p_OpMatrix_B;

	//左Givens变换矩阵G-总体综合矩阵
	BasicMatrix* p_GivensMatrixFor_Q_total;
	//右Givens变换矩阵Z-总体综合矩阵
	BasicMatrix* p_GivensMatrixFor_Z_total;

	//左Givens变换矩阵G-迭代过程矩阵
	BasicMatrix* p_GivensMatrixFor_Q_iterate;
	//右Givens变换矩阵Z-迭代过程矩阵
	BasicMatrix* p_GivensMatrixFor_Z_iterate;

	//左Givens变换矩阵G-单步过程矩阵
	BasicMatrix* p_GivensMatrixFor_Q_step;
	//右Givens变换矩阵Z-单步过程矩阵
	BasicMatrix* p_GivensMatrixFor_Z_step;


	//左上A子矩阵
	BasicMatrix* p_OpSubMatrix_A;
	//左上B子矩阵
	BasicMatrix* p_OpSubMatrix_B;

	//左Givens变换子矩阵G-单步过程矩阵
	BasicMatrix* p_GivensSubMatrixFor_Q_step;
	//右Givens变换子矩阵Z-单步过程矩阵
	BasicMatrix* p_GivensSubMatrixFor_Z_step;

	//乘法器
	MatrixMultiplier* p_Multiplier;

	//Givens变换器
	GivensTransformation* p_GivensTrans;


};

#endif /* TRANSFORMATION_BASIC_QZTRIANGLEZEROCHASING_H_ */
