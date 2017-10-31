/*
 * HessenbergFormular.h
 *
 *  Created on: 2017年5月8日
 *      Author: looke
 */

#ifndef TRANSFORMATION_BASIC_HESSENBERGFORMULAR_H_
#define TRANSFORMATION_BASIC_HESSENBERGFORMULAR_H_

#include "..\matrix\basic\BasicMatrix.h"
#include "..\vector\basic\BasicVector.h"
#include "..\transformation\basic\HouseholderTransformation.h"
#include "..\matrix\basic\util\MatrixMultiplier.h"
class HessenbergFormular
{
public:
	HessenbergFormular();
	HessenbergFormular(BasicMatrix* p_InputOpMatrix);

	virtual void init(BasicMatrix* p_InputOpMatrix);
	virtual void reload(BasicMatrix* p_InputOpMatrix);
	virtual void resizeSubMatrix(int rowAndColumnNumber);

	//根据当前迭代  初始化子变换矩阵
	//void initSubHouseholderTrans(int iterateNum);

	//Hessenberg格式化
	void formularUpperHessnbergMatrix();

	//根据当前迭代 计算生成子变换矩阵
	void generateSubHouseholderTrans(int iterateNum);

	//将子变换矩阵升级为全维度变换阵
	void upgradeSubHouseholderTrans(int iterateNum);

	void updatePreTransMatrix();
	void updateAfterTransMatrix();

	void updateOpMatrix();

	BasicMatrix* getOpMatrix();
	BasicMatrix* getPreTransMatrix();
	BasicMatrix* getAfterTransMatrix();
	BasicMatrix* getTransMatrix();
	BasicMatrix* getSubTransMatrix();

	virtual ~HessenbergFormular(){};
protected:
	BasicMatrix* p_OpMatrix;

	//左乘变换阵
	BasicMatrix* p_preTransMatrix;

	//右乘变换阵
	BasicMatrix* p_afterTransMatrix;

	//Householder变换阵
	BasicMatrix* p_transMatrix;

	//Householder子变换阵
	BasicMatrix* p_subTransMatrix;

	//Householder变换
	HouseholderTransformation* p_HouseholderTrans;

	//乘法器
	MatrixMultiplier* p_Multiplier;
};



#endif /* TRANSFORMATION_BASIC_HESSENBERGFORMULAR_H_ */
