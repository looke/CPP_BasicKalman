/*
 * HessenbergFormular.h
 *
 *  Created on: 2017��5��8��
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

	//���ݵ�ǰ����  ��ʼ���ӱ任����
	//void initSubHouseholderTrans(int iterateNum);

	//Hessenberg��ʽ��
	void formularUpperHessnbergMatrix();

	//���ݵ�ǰ���� ���������ӱ任����
	void generateSubHouseholderTrans(int iterateNum);

	//���ӱ任��������Ϊȫά�ȱ任��
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

	//��˱任��
	BasicMatrix* p_preTransMatrix;

	//�ҳ˱任��
	BasicMatrix* p_afterTransMatrix;

	//Householder�任��
	BasicMatrix* p_transMatrix;

	//Householder�ӱ任��
	BasicMatrix* p_subTransMatrix;

	//Householder�任
	HouseholderTransformation* p_HouseholderTrans;

	//�˷���
	MatrixMultiplier* p_Multiplier;
};



#endif /* TRANSFORMATION_BASIC_HESSENBERGFORMULAR_H_ */
