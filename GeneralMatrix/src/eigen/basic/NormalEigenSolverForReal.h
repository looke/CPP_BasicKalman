/*
 * NormalEigenSolverForReal.h
 *
 *  Created on: 2017年5月20日
 *      Author: looke
 */

#ifndef EIGEN_BASIC_NORMALEIGENSOLVERFORREAL_H_
#define EIGEN_BASIC_NORMALEIGENSOLVERFORREAL_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\eigen\basic\QR\DoubleShiftQRIteration.h"
#include "..\eigen\basic\QR\SingleShiftQRIteration.h"
#include "..\transformation\util\HessenbergDeflation.h"

class NormalEigenSolverForReal
{
public:
	NormalEigenSolverForReal();
	NormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix);

	virtual void init(BasicMatrix* p_input_OpMatrix);
	virtual void reload(BasicMatrix* p_input_OpMatrix);
	virtual ~NormalEigenSolverForReal(){};

	//查找并更新降阶点
	//bool findNewDeflationPoint();

	//根据降阶点 生成降阶的Hessenberg矩阵
	void generateDeflatedHessenbergMatrix();

	//将已降阶的变换矩阵 升级成为全尺寸变换矩阵
	void upgradeDeflatedQQTMatrix();

	//将单迭代变换矩阵 合并成为总体变换矩阵
	void updateQQTMatrixTotal();

	//生成原始hessenberg操作矩阵
	void generateHessenbergOpMatrix();

	//更新原始hessenberg操作矩阵
	void updateHessenbergOpMatrix();

	//计算特征值
	void calcEigenValue();

	//初始化特征值计算相关矩阵
	void initEigenCalcMatrix();

	//解算结束判断逻辑
	bool hasFinishedIteration();

	//2x2对角块是否为复数特征值判断
	bool isDiagonalBlockComplexEigen(BasicMatrix* p_Input_OpMatrix);

	//初步化为对角块以后，最后一步迭代，将对角线上的2x2对角块进行上三角化
	void lastStepIteration(int startIndex);

	BasicMatrix* getEigenValueMatrix();
	BasicMatrix* getOpHessenbergMatrix();

	BasicMatrix* getQTMatrix_Iteration();
	BasicMatrix* getQMatrix_Iteration();

	BasicMatrix* getQTMatrix_Total();
	BasicMatrix* getQMatrix_Total();

	BasicMatrix* getOpHessenbergMatrix_deflated();

	BasicMatrix* getQTMatrix_Deflated_Iteration();
	BasicMatrix* getQMatrix_Deflated_Iteration();

	//测试打印，QT_Total * OP * Q
	void showQTOPxQ();
protected:

	//降阶起点索引指示，初始化为0
	int deflationStart;
	//降阶终点索引指示，初始化为n-1
	int deflationEnd;

	//原始操作矩阵
	BasicMatrix* p_OpMatrix;

	//原始操作矩阵对应的特征值矩阵
	BasicMatrix* p_EigenValueMatrix;

	//原始操作Hessenberg矩阵
	BasicMatrix* p_OpHessenbergMatrix;

	//原始矩阵的单迭代变换矩阵 QT为左乘矩阵 Q为右乘矩阵
	BasicMatrix* p_QTMatrix_Iteration;
	BasicMatrix* p_QMatrix_Iteration;

	//原始矩阵的总体变换矩阵 QT为左乘矩阵 Q为右乘矩阵
	BasicMatrix* p_QTMatrix_Total;
	BasicMatrix* p_QMatrix_Total;

	//已降阶的 操作Hessenberg矩阵
	BasicMatrix* p_OpHessenbergMatrix_deflated;

	//已降阶矩阵的单迭代变换矩阵Q\QT
	BasicMatrix* p_QTMatrix_Deflated_Iteration;
	BasicMatrix* p_QMatrix_Deflated_Iteration;

	//最后一步针对对角线2x2矩阵块的操作
	BasicMatrix* p_LastStepMatrix_2x2;

	//双重步QR迭代器
	DoubleShiftQRIteration* p_DoubleShifeQR;

	//单步QR迭代器
	SingleShiftQRIteration* p_SingleShifeQR;

	//hessen格式化
	HessenbergFormular* p_HessenbergForm;

	//乘法器
	MatrixMultiplier* p_Multiplier;

	//hessenberg降阶点查找器
	HessenbergDeflation* p_HessenbergDeflation;

	//测试总体转置矩阵的临时测试对象
	BasicMatrix* p_testForTemp_nxn;
	MatrixMultiplier* p_testMulti;
};



#endif /* EIGEN_BASIC_NORMALEIGENSOLVERFORREAL_H_ */
