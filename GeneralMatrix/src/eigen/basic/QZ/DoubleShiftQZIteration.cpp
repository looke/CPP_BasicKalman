/*
 * DoubleShiftQZIteration.cpp
 *
 *  Created on: 2017年5月30日
 *      Author: looke
 */

#include "DoubleShiftQZIteration.h"
#include <iostream>
using namespace std;

DoubleShiftQZIteration::DoubleShiftQZIteration()
{};

DoubleShiftQZIteration::DoubleShiftQZIteration(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	this->init(p_input_OpMatrix_A, p_input_OpMatrix_B);
};

void DoubleShiftQZIteration::init(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{};

void DoubleShiftQZIteration::reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{};

//生成H-T操作矩阵对
void DoubleShiftQZIteration::generateHessenTriangleOpMatrix()
{
	this->p_HessenbergTriangleFormular->reload(p_OpMatrix_A, p_OpMatrix_B);
	this->p_HessenbergTriangleFormular->formularABMatrix();
	this->p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getHessenbergMatrixA());
	this->p_OpMatrix_Triangle->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getTriangleMatrixB());

	cout << "DoubleShiftQZIteration--generateHessenTriangleOpMatrix----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--generateHessenTriangleOpMatrix----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * 根据A*B^-1 矩阵最后2x2子矩阵 计算生成Wilkinson移位的trace & determinant
 */
void DoubleShiftQZIteration::generateWilkinsonShift()
{
	//计算 A*B^-1 最后2x2子矩阵
	p_ABInvCalc->generateABinvLast2x2(p_OpMatrix_Hessenberg,p_OpMatrix_Triangle);

	double ABinv_n_1_n_1 = p_ABInvCalc->getABinv_N_1_N_1();
	double ABinv_n_n = p_ABInvCalc->getABinv_N_N();
	double ABinv_n_1_n = p_ABInvCalc->getABinv_N_1_N();
	double ABinv_n_n_1 = p_ABInvCalc->getABinv_N_N_1();

	this->trace = ABinv_n_1_n_1 + ABinv_n_n;
	this->determinant = ABinv_n_1_n_1*ABinv_n_n - ABinv_n_1_n*ABinv_n_n_1;
};

/*
 * 计算 A*B^-1 前两列元素
 */
void DoubleShiftQZIteration::generateABinvFirst3x2()
{
	p_ABInvCalc->generateABinvFirst3x2(p_OpMatrix_Hessenberg, p_OpMatrix_Triangle);
	this->ABinv_11 = p_ABInvCalc->getABinv11();
	this->ABinv_12 = p_ABInvCalc->getABinv12();
	this->ABinv_21 = p_ABInvCalc->getABinv21();
	this->ABinv_22 = p_ABInvCalc->getABinv22();
	this->ABinv_32 = p_ABInvCalc->getABinv32();
};

/*
 * 计算 A*B^-1 双重移位后 第一列元素
 */
void DoubleShiftQZIteration::generateABinvShiftedFirstColumn()
{
	generateABinvFirst3x2();
	generateWilkinsonShift();
	this->C11 = ABinv_11*ABinv_11 - ABinv_11*this->trace + this->determinant + ABinv_12*ABinv_21;
	this->C21 = ABinv_21*ABinv_11 + ABinv_21*ABinv_22 -ABinv_21*this->trace;
	this->C31 = ABinv_21*ABinv_32;
};

/*
 * 根据当前迭代进度，生成三角矩阵膨胀部位的元素
 */
void DoubleShiftQZIteration::generateTriangleBulgeElement(int iterateNum)
{
	int startPosition = iterateNum+1;
	this->B_21 = p_OpMatrix_Triangle->getMatrixElement(startPosition+1,startPosition);
	this->B_22 = p_OpMatrix_Triangle->getMatrixElement(startPosition+1,startPosition+1);
	this->B_31 = p_OpMatrix_Triangle->getMatrixElement(startPosition+2,startPosition);
	this->B_32 = p_OpMatrix_Triangle->getMatrixElement(startPosition+2,startPosition+1);
	this->B_33 = p_OpMatrix_Triangle->getMatrixElement(startPosition+2,startPosition+2);
};

/*
 * 将Q子矩阵根据当前迭代进度,升级为全尺寸Q矩阵
 */
void DoubleShiftQZIteration::upgradeQSubMatrix(int iterateNum)
{
	this->p_QMatrix_Implicit_Step->resetMatrixToI();
	int startPosition = iterateNum+1;

	cout << "DoubleShiftQZIteration--upgradeQSubMatrix----Before Update" << endl;
	p_QSubMatrix_Implicit_Step_3->printMatrix();

	for(int i=0,m=startPosition; i<p_QSubMatrix_Implicit_Step_3->rowNum; i++,m++)
	{
		for(int j=0,n=startPosition; j<p_QSubMatrix_Implicit_Step_3->columnNum; j++,n++)
		{
			p_QMatrix_Implicit_Step->setMatrixElement(m,n,p_QSubMatrix_Implicit_Step_3->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeQSubMatrix----After Update" << endl;
	p_QMatrix_Implicit_Step->printMatrix();
};

/*
 * 将Z子矩阵根据当前迭代进度,升级为全尺寸Z矩阵
 */
void DoubleShiftQZIteration::upgradeZSubMatrix(int iterateNum)
{
	this->p_ZMatrix_Implicit_Step->resetMatrixToI();
	int startPosition = iterateNum+1;

	cout << "DoubleShiftQZIteration--upgradeZSubMatrix----Before Update" << endl;
	p_ZSubMatrix_Implicit_Step_3->printMatrix();

	for(int i=0,m=startPosition; i<p_ZSubMatrix_Implicit_Step_3->rowNum; i++,m++)
	{
		for(int j=0,n=startPosition; j<p_ZSubMatrix_Implicit_Step_3->columnNum; j++,n++)
		{
			p_ZMatrix_Implicit_Step->setMatrixElement(m,n,p_ZSubMatrix_Implicit_Step_3->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeZSubMatrix----After Update" << endl;
	p_ZMatrix_Implicit_Step->printMatrix();
};
/*
 * 将2x2 Q子矩阵升级为 3x3 Q子矩阵 2x2位于右下
 */
void DoubleShiftQZIteration::upgradeQMiniToSubMatrix_RightEnd()
{
	p_QSubMatrix_Implicit_Step_3->resetMatrixToI();

	cout << "DoubleShiftQZIteration--upgradeQMiniToSubMatrix_RightEnd----Before Update" << endl;
	p_QSubMatrix_Implicit_Step_2->printMatrix();

	for(int i=0; i<p_QSubMatrix_Implicit_Step_2->rowNum;i++)
	{
		for(int j=0; j<p_QSubMatrix_Implicit_Step_2->columnNum;j++)
		{
			p_QSubMatrix_Implicit_Step_3->setMatrixElement(i+1, j+1, p_QSubMatrix_Implicit_Step_2->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeQMiniToSubMatrix_RightEnd----After Update" << endl;
	p_QSubMatrix_Implicit_Step_3->printMatrix();
};

/*
 * 将2x2 Z子矩阵升级为 3x3 Z子矩阵 2x2位于右下
 */
void DoubleShiftQZIteration::upgradeZMiniToSubMatrix_RightEnd()
{
	p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_RightEnd----Before Update" << endl;
	p_ZSubMatrix_Implicit_Step_2->printMatrix();

	for(int i=0; i<p_ZSubMatrix_Implicit_Step_2->rowNum;i++)
	{
		for(int j=0; j<p_ZSubMatrix_Implicit_Step_2->columnNum;j++)
		{
			p_ZSubMatrix_Implicit_Step_3->setMatrixElement(i+1, j+1, p_ZSubMatrix_Implicit_Step_2->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_RightEnd----After Update" << endl;
	p_ZSubMatrix_Implicit_Step_3->printMatrix();
};

/*
 * 将2x2 Z子矩阵升级为 3x3 Z子矩阵 2x2位于左上
 */
void DoubleShiftQZIteration::upgradeZMiniToSubMatrix_LeftTop()
{
	p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_LeftTop----Before Update" << endl;
	p_ZSubMatrix_Implicit_Step_2->printMatrix();

	for(int i=0; i<p_ZSubMatrix_Implicit_Step_2->rowNum;i++)
	{
		for(int j=0; j<p_ZSubMatrix_Implicit_Step_2->columnNum;j++)
		{
			p_ZSubMatrix_Implicit_Step_3->setMatrixElement(i, j, p_ZSubMatrix_Implicit_Step_2->getMatrixElement(i,j));
		}
	}

	cout << "DoubleShiftQZIteration--upgradeZMiniToSubMatrix_LeftTop----After Update" << endl;
	p_ZSubMatrix_Implicit_Step_3->printMatrix();

};

/*
 * 使用Q矩阵右乘H-T矩阵对
 */
void DoubleShiftQZIteration::updateHTMatrixByQ()
{
	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//更新矩阵Hessenberg A
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_OpMatrix_Hessenberg);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//更新矩阵Triangle B
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_OpMatrix_Triangle);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByQ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};


/*
 * 使用Z矩阵右乘H-T矩阵对
 */
void DoubleShiftQZIteration::updateHTMatrixByZ()
{
	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//更新矩阵Hessenberg A
	this->p_Multiplier->reload(p_OpMatrix_Hessenberg, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//更新矩阵Triangle B
	this->p_Multiplier->reload(p_OpMatrix_Triangle, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--updateHTMatrixByZ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * 更新综合转换矩阵Q Total(将Step合并入Total)
 */
void DoubleShiftQZIteration::updateQMatrix_Total()
{
	//更新矩阵Q total
	this->p_Multiplier->reload(p_QMatrix_Implicit_Step, p_QMatrix_Implicit_Total);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

/*
 * 更新综合转换矩阵Z Total(将Step合并入Total)
 */
void DoubleShiftQZIteration::updateZMatrix_Total()
{
	//更新矩阵Z total
	this->p_Multiplier->reload(p_ZMatrix_Implicit_Total, p_ZMatrix_Implicit_Step);
	this->p_Multiplier->multiplyCalc();
	p_ZMatrix_Implicit_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
};

//Wilkinson位移QZ迭代 隐式 初始化
void DoubleShiftQZIteration::initForWilkinsonImplicitQZ()
{
	//Qi 子矩阵 显式迭代 分步 Qi用于左乘OP矩阵 3x3
	p_QSubMatrix_Implicit_Step_3->resetMatrixToI();

	//Zi 子矩阵 显式迭代 分步 QTi用于右乘OP矩阵 3x3
	p_ZSubMatrix_Implicit_Step_3->resetMatrixToI();
	//Zi 子矩阵 显式迭代 分步 QT用于右乘OP矩阵 2x2
	p_ZSubMatrix_Implicit_Step_2->resetMatrixToI();

	//计算生成A*B^-1 双重移位后的第一列
	generateABinvShiftedFirstColumn();

	//双步移位后的矩阵首列三个元素构成三元向量
	p_TransVectorForQStep_3->setElement(0,this->C11);
	p_TransVectorForQStep_3->setElement(1,this->C21);
	p_TransVectorForQStep_3->setElement(2,this->C31);

	//计算Q转换矩阵3维子矩阵
	this->p_HouseholderTrans->reload(this->p_TransVectorForQStep_3);
	p_QSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));
	//Q子矩阵升级
	upgradeQSubMatrix(-1);
	//Q左乘更新HT矩阵对
	updateHTMatrixByQ();
	//更新总体转换矩阵Q Total
	updateQMatrix_Total();


	//必须首先计算Z转换矩阵3维子矩阵
	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---3维
	generateTriangleBulgeElement(-1);
	p_TransVectorForZStep_3->setElement(0,this->B_31);
	p_TransVectorForZStep_3->setElement(1,this->B_32);
	p_TransVectorForZStep_3->setElement(2,this->B_33);
	this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_3);
	p_ZSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
	//Z子矩阵升级
	upgradeZSubMatrix(-1);
	//Z右乘更新HT矩阵对
	updateHTMatrixByZ();
	//更新总体转换矩阵Z Total
	updateZMatrix_Total();

	//其次计算Z转换矩阵2维子矩阵
	//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---2维
	generateTriangleBulgeElement(-1);
	p_TransVectorForZStep_2->setElement(0,this->B_21);
	p_TransVectorForZStep_2->setElement(1,this->B_22);
	this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_2);
	p_ZSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
	//2维变换矩阵升级为3维
	upgradeZMiniToSubMatrix_LeftTop();
	//Z子矩阵升级
	upgradeZSubMatrix(-1);
	//Z右乘更新HT矩阵对
	updateHTMatrixByZ();
	//更新总体转换矩阵Z Total
	updateZMatrix_Total();

	//两轮Z矩阵更新过后，Triangle-B矩阵应当恢复上三角格式

	cout << "initForWilkinsonImplicitQZ---Q * Hessenberg * Z" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "initForWilkinsonImplicitQZ---Q * Triangle * Z" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

/*
 * Wilkinson位移QZ迭代 隐式 单轮迭代
 */
void DoubleShiftQZIteration::wilkinson_IM_QZIteration_Step()
{
	//重置Q\Z 总体转换矩阵
	this->p_QMatrix_Implicit_Total->resetMatrixToI();
	this->p_ZMatrix_Implicit_Total->resetMatrixToI();
	//初始迭代第一步
	initForWilkinsonImplicitQZ();

	//膨胀部分下移
	int bulgeNumber = this->p_OpMatrix_Hessenberg->columnNum - 3;

	for(int j=0; j<bulgeNumber; j++)
	{
		//生成隐式Q
		double a1,a2,a3;
		a1 = this->p_OpMatrix_Hessenberg->getMatrixElement(j+1,j);
		a2 = this->p_OpMatrix_Hessenberg->getMatrixElement(j+2,j);
		a3 = this->p_OpMatrix_Hessenberg->getMatrixElement(j+3,j);

		//双步移位后的矩阵首列三个元素构成三元向量
		p_TransVectorForQStep_3->setElement(0,a1);
		p_TransVectorForQStep_3->setElement(1,a2);
		p_TransVectorForQStep_3->setElement(2,a3);

		//计算Q转换矩阵3维子矩阵
		this->p_HouseholderTrans->reload(this->p_TransVectorForQStep_3);
		p_QSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));
		//Q子矩阵升级
		upgradeQSubMatrix(j);
		//Q左乘更新HT矩阵对
		updateHTMatrixByQ();
		//更新总体转换矩阵Q Total
		updateQMatrix_Total();

		//必须首先计算Z转换矩阵3维子矩阵
		//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---3维
		generateTriangleBulgeElement(j);
		p_TransVectorForZStep_3->setElement(0,this->B_31);
		p_TransVectorForZStep_3->setElement(1,this->B_32);
		p_TransVectorForZStep_3->setElement(2,this->B_33);
		this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_3);
		p_ZSubMatrix_Implicit_Step_3->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
		//Z子矩阵升级
		upgradeZSubMatrix(j);
		//Z右乘更新HT矩阵对
		updateHTMatrixByZ();
		//更新总体转换矩阵Z Total
		updateZMatrix_Total();

		//其次计算Z转换矩阵2维子矩阵
		//用于计算隐式双步QZ跌代单步转换矩阵Zi的向量---2维
		generateTriangleBulgeElement(j);
		p_TransVectorForZStep_2->setElement(0,this->B_21);
		p_TransVectorForZStep_2->setElement(1,this->B_22);
		this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_2);
		p_ZSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
		//2维变换矩阵升级为3维
		upgradeZMiniToSubMatrix_LeftTop();
		//Z子矩阵升级
		upgradeZSubMatrix(j);
		//Z右乘更新HT矩阵对
		updateHTMatrixByZ();
		//更新总体转换矩阵Z Total
		updateZMatrix_Total();

		//两轮Z矩阵更新过后，Triangle-B矩阵应当恢复上三角格式
		cout << "wilkinson_IM_QZIteration_Step---Q * Hessenberg * Z" << endl;
		this->p_OpMatrix_Hessenberg->printMatrix();
		cout << "wilkinson_IM_QZIteration_Step---Q * Triangle * Z" << endl;
		this->p_OpMatrix_Triangle->printMatrix();
	}

	endForWilkinsonImplicitQZ();
};

/*
 * Wilkinson双位移QZ迭代 隐式 -收尾最后一步迭代
 */
void DoubleShiftQZIteration::endForWilkinsonImplicitQZ()
{
	int lastQIndex = p_OpMatrix_Hessenberg->rowNum-1;
	//生成隐式Q
	double an1,an2;
	an1 = this->p_OpMatrix_Hessenberg->getMatrixElement(lastQIndex-1,lastQIndex-2);
	an2 = this->p_OpMatrix_Hessenberg->getMatrixElement(lastQIndex,lastQIndex-2);

	p_TransVectorForQStep_2->setElement(0,an1);
	p_TransVectorForQStep_2->setElement(1,an2);
	this->p_HouseholderTrans->reload(this->p_TransVectorForQStep_2);
	p_QSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToE1(true));
	//2维变换矩阵升级为3维
	upgradeQMiniToSubMatrix_RightEnd();
	//Q子矩阵升级为全维度
	upgradeQSubMatrix(lastQIndex-3);
	//Q左乘更新HT矩阵对
	updateHTMatrixByQ();
	//更新总体转换矩阵Q Total
	updateQMatrix_Total();

	//生成隐式 Z
	double bn1,bn2;
	bn1 = this->p_OpMatrix_Triangle->getMatrixElement(lastQIndex,lastQIndex-1);
	bn2 = this->p_OpMatrix_Triangle->getMatrixElement(lastQIndex,lastQIndex);
	p_TransVectorForZStep_2->setElement(0,bn1);
	p_TransVectorForZStep_2->setElement(1,bn2);
	this->p_HouseholderTrans->reload(this->p_TransVectorForZStep_2);
	p_ZSubMatrix_Implicit_Step_2->copyMatrixElementNoCheck(this->p_HouseholderTrans->getHouseholderMatrixToEn(true));
	//2维变换矩阵升级为3维
	upgradeZMiniToSubMatrix_RightEnd();
	//Z子矩阵升级为全维度
	upgradeZSubMatrix(lastQIndex-3);
	//Z右乘更新HT矩阵对
	updateHTMatrixByZ();
	//更新总体转换矩阵Z Total
	updateZMatrix_Total();

	//两轮QZ矩阵更新过后，H-Triangle 矩阵应当恢复H-T格式
	cout << "endForWilkinsonImplicitQZ---Q * Hessenberg * Z" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "endForWilkinsonImplicitQZ---Q * Triangle * Z" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

};

/*
 * Wilkinson位移QZ迭代 隐式 单轮迭代对外接口 (不需要对操作矩阵进行H-T格式化 init/reload时已经完成H-T格式化)
 */
void DoubleShiftQZIteration::wilkinson_IM_QZIteration_Single()
{
	//操作矩阵转换为Hessenberg矩阵
	//this->generateHessenTriangleOpMatrix();
	cout << "DoubleShiftQZIteration--initForImplicitQR----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--initForImplicitQR----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
	wilkinson_IM_QZIteration_Step();
};

/*
 * Wilkinson位移QZ迭代 隐式 10次连续迭代 (不需要对操作矩阵进行H-T格式化 init/reload时已经完成H-T格式化)
 */
void DoubleShiftQZIteration::wilkinson_IM_QZIteration()
{
	//操作矩阵转换为Hessenberg-Triangle矩阵
	//this->generateHessenTriangleOpMatrix();
	cout << "DoubleShiftQZIteration--H-T Format----OP Hessenberg Matrix" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "DoubleShiftQZIteration--H-T Format----OP Triangle Matrix" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	int iteratNumber = 100;
	int i = 0;
	while(i < iteratNumber)
	{
		wilkinson_IM_QZIteration_Step();
		i++;
	}
};

BasicMatrix* DoubleShiftQZIteration::getQMatrix_Total()
{
	return this->p_QMatrix_Implicit_Total;
};

BasicMatrix* DoubleShiftQZIteration::getZMatrix_Total()
{
	return this->p_ZMatrix_Implicit_Total;
};
