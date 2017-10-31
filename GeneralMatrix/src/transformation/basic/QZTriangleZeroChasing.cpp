/*
 * HessenbergTriangleDeflation.cpp
 *
 *  Created on: 2017年4月28日
 *      Author: looke
 */

#include <transformation/basic/QZTriangleZeroChasing.h>
#include <iostream>
using namespace std;

QZTriangleZeroChasing::QZTriangleZeroChasing()
{};

QZTriangleZeroChasing::QZTriangleZeroChasing(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B)
{
	this->init(input_Op_Matrix_A, input_Op_Matrix_B);
};

void QZTriangleZeroChasing::init(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B)
{};

void QZTriangleZeroChasing::reload(BasicMatrix* input_Op_Matrix_A, BasicMatrix* input_Op_Matrix_B)
{};


//降零元
void QZTriangleZeroChasing::deflate()
{
	int subMatrixSize;
	int zeroIndex;

	cout << "deflate----clean Q\Z total" << endl;
	//左Givens变换矩阵Q-总体综合矩阵
	p_GivensMatrixFor_Q_total->resetMatrixToI();
	//右Givens变换矩阵Z-总体综合矩阵
	p_GivensMatrixFor_Z_total->resetMatrixToI();


	for(int i=0; i<this->p_OpMatrix_A->rowNum; i++)
	{
		cout << "deflate----start iterate:" << i << endl;

		subMatrixSize = p_OpMatrix_A->rowNum-i;
		//子矩阵维度小于2时退出循环
		if(subMatrixSize < 2)
		{
			deflate_End_New = p_OpMatrix_A->rowNum - 1 - i;
			cout << "deflate----subMatrixSize < 2 quit!:" << deflate_End_New << endl;
			break;
		}

		cout << "deflate----Generate Sub Matrix" << endl;

		//生成左上子矩阵,以及对应的子变换矩阵
		generateSubMatrix(i);

		cout << "deflate---- Sub A " <<endl;
		this->p_OpSubMatrix_A->printMatrix();
		cout << "deflate---- Sub B " <<endl;
		this->p_OpSubMatrix_B->printMatrix();

		//获取主对角线0元位置索引
		zeroIndex = this->p_OpSubMatrix_B->indexOfZeroOnDiagonal();
		cout << "deflate----Zero Index of Sub B:" << zeroIndex << endl;

		//判断主对角线0元的位置
		if(zeroIndex < 0)
		{
			//如果不存在0元,则退出,说明不再需要降零元
			deflate_End_New = p_OpMatrix_A->rowNum - 1 - i;
			cout << "deflate----No Zero, Quit:"<< deflate_End_New <<endl;
			break;
		}

		cout << "deflate----clean Q\Z iterate" << endl;
		//左Givens变换矩阵Q-迭代过程矩阵
		p_GivensMatrixFor_Q_iterate->resetMatrixToI();
		//右Givens变换矩阵Z-迭代过程矩阵
		p_GivensMatrixFor_Z_iterate->resetMatrixToI();

		if(zeroIndex < subMatrixSize-1)
		{
			//如果0元不在B子矩阵右下角,则降零元,将0元降子矩阵右下角
			for (int j=zeroIndex+1; j<subMatrixSize; j++)
			{
				cout << "deflate---- Sub B target:" << j << endl;

				cout << "deflate----clean Q\Z step" << endl;
				//左Givens变换矩阵G-单步过程矩阵
				p_GivensMatrixFor_Q_step->resetMatrixToI();
				//右Givens变换矩阵Z-单步过程矩阵
				p_GivensMatrixFor_Z_step->resetMatrixToI();

				//根据B子矩阵生成Q子矩阵
				generateGivensSubMatrixForB(j);
				//更新A,B子矩阵
				updateSubOpMatrix_A_By_Q();
				updateSubOpMatrix_B_By_Q();
				cout << "deflate---- Sub Q A " <<endl;
				this->p_OpSubMatrix_A->printMatrix();
				cout << "deflate---- Sub Q B " <<endl;
				this->p_OpSubMatrix_B->printMatrix();
				//根据A子矩阵生成Z子矩阵
				generateGivensSubMatrixForA(j);
				//更新A,B子矩阵
				updateSubOpMatrix_A_By_Z();
				updateSubOpMatrix_B_By_Z();

				cout << "deflate---- Sub G A Z" <<endl;
				this->p_OpSubMatrix_A->printMatrix();
				cout << "deflate---- Sub G B Z" <<endl;
				this->p_OpSubMatrix_B->printMatrix();

				//将Z子矩阵升级为Z矩阵
				upgradeGivensSubMatrix_Q();
				upgradeGivensSubMatrix_Z();

				//更新Z迭代矩阵
				updateGivensMatrix_Iterate_Q();
				updateGivensMatrix_Iterate_Z();

				cout << "deflate---- Q iterate" <<endl;
				this->p_GivensMatrixFor_Q_iterate->printMatrix();
				cout << "deflate---- Z iterate" <<endl;
				this->p_GivensMatrixFor_Z_iterate->printMatrix();

			}
		}
		cout << "deflate----Final Z for iterate:" << i <<endl;
		cout << "deflate----clean Z iterate" << endl;
		//右Givens变换矩阵Z-单步过程矩阵
		p_GivensMatrixFor_Z_step->resetMatrixToI();

		//此时0元应当位于B子矩阵右下角,对A子矩阵再进行一次变换,化最末行次对角元为0
		generateGivensSubMatrixForA_last();
		//更新A,B子矩阵
		updateSubOpMatrix_A_By_Z();
		updateSubOpMatrix_B_By_Z();
		cout << "deflate---- Sub A Z_final" <<endl;
		this->p_OpSubMatrix_A->printMatrix();
		cout << "deflate---- Sub B Z_final" <<endl;
		this->p_OpSubMatrix_B->printMatrix();

		//将Z子矩阵升级为Z矩阵
		upgradeGivensSubMatrix_Z();
		//更新Z迭代矩阵
		updateGivensMatrix_Iterate_Z();
		cout << "deflate---- Z iterate" <<endl;
		this->p_GivensMatrixFor_Z_iterate->printMatrix();

		//将变换过程施加在OP操作矩阵，更新G,Z综合变换矩阵
		updateOpMatrix_A_By_Q();
		updateOpMatrix_A_By_Z();
		updateOpMatrix_B_By_Q();
		updateOpMatrix_B_By_Z();

		cout << "deflate---- Op A " <<endl;
		this->p_OpMatrix_A->printMatrix();
		cout << "deflate---- Op B " <<endl;
		this->p_OpMatrix_B->printMatrix();

		updateGivensMatrix_Total_Q();
		updateGivensMatrix_Total_Z();
		cout << "deflate---- Q total " <<endl;
		this->p_GivensMatrixFor_Q_total->printMatrix();
		cout << "deflate---- Z total " <<endl;
		this->p_GivensMatrixFor_Z_total->printMatrix();
	}
};


/* 根据当前索引 为AB子矩阵生成Givens变换子矩阵Q(Q为左乘矩阵，Z为右乘矩阵)
 * index表示B子矩阵需要主对角元清零的列,
 * 根据index可以基于B子矩阵生成将B子矩阵index标示的列对角线主元清零的矩阵的变换G
 * 根据index可以基于A子矩阵生成将A子矩阵还原为Hessenberg矩阵的变换Z
 */
void QZTriangleZeroChasing::generateGivensSubMatrixForB(int index)
{
	BasicVector* p_Vector = this->p_OpSubMatrix_B->getColumnVector(index);

	//test print
	cout <<"generateGivensSubMatrixForB---- sub B column vector to zero:" << endl;
	p_Vector->printVector();

	this->p_GivensTrans->reload(p_Vector);

	p_GivensSubMatrixFor_Q_step->copyMatrixElementNoCheck(this->p_GivensTrans->getGivensMatrixPreMultiple(index));

	//test print
	cout <<"generateGivensSubMatrixForB---- sub B givens G:" << endl;
	p_GivensSubMatrixFor_Q_step->printMatrix();

};

/* 根据当前索引 为AB子矩阵生成Givens变换子矩阵Z(Q为左乘矩阵，Z为右乘矩阵)
 * index表示B子矩阵需要主对角元清零的列,
 * 根据index可以基于B子矩阵生成将B子矩阵index标示的列对角线主元清零的矩阵的变换G
 * 根据index可以基于A子矩阵生成将A子矩阵还原为Hessenberg矩阵的变换Z
 */
void QZTriangleZeroChasing::generateGivensSubMatrixForA(int index)
{
	int columnIndex = index-2;
	if(columnIndex < 0)
	{
		cout <<"generateGivensSubMatrixForA---- columnIndex < 0 no need to eliminate" << endl;
		return;
	};
	BasicVector* p_Vector = this->p_OpSubMatrix_A->getRowVector(index);

	//test print
	cout <<"generateGivensSubMatrixForA---- sub A row vector to zero:" << endl;
	p_Vector->printVector();

	this->p_GivensTrans->reload(p_Vector);
	p_GivensSubMatrixFor_Z_step->copyMatrixElementNoCheck(this->p_GivensTrans->getGivensMatrixAfterMultiple(columnIndex));

	//test print
	cout <<"generateGivensSubMatrixForA---- sub A givens Z:" << endl;
	p_GivensSubMatrixFor_Z_step->printMatrix();
};

void QZTriangleZeroChasing::generateGivensSubMatrixForA_last()
{
	int rowIndex = this->p_OpSubMatrix_A->rowNum - 1;
	BasicVector* p_Vector = this->p_OpSubMatrix_A->getRowVector(rowIndex);

	//test print
	cout <<"generateGivensSubMatrixForA_last---- sub A row vector to zero:" << endl;
	p_Vector->printVector();
	//此处应当增加判断，向量指定位置的元素是否已经为0，如果已经为0，则不需要进行消元

	this->p_GivensTrans->reload(p_Vector);
	p_GivensSubMatrixFor_Z_step->copyMatrixElementNoCheck(this->p_GivensTrans->getGivensMatrixAfterMultiple(rowIndex-1));

	//test print
	cout <<"generateGivensSubMatrixForA_last---- sub A givens Z:" << endl;
	p_GivensSubMatrixFor_Z_step->printMatrix();

};

//根据当前迭代次数 生成左上子矩阵
void QZTriangleZeroChasing::generateSubMatrix(int iterateNum)
{
	int rowNum = this->p_OpMatrix_A->rowNum - iterateNum;
	if(rowNum <= 0)
	{
		return;
	}
	this->resizeSubMatrix(rowNum);

	double temp;
	for(int i=0; i<rowNum; i++)
	{
		for(int j=0;j<rowNum;j++)
		{
			temp = this->p_OpMatrix_A->getMatrixElement(i,j);
			this->p_OpSubMatrix_A->setMatrixElement(i,j,temp);

			temp = this->p_OpMatrix_B->getMatrixElement(i,j);
			this->p_OpSubMatrix_B->setMatrixElement(i,j,temp);
		}
	}

};

//将Givens变换step子矩阵Q升级成为全维度变换step矩阵Q
void QZTriangleZeroChasing::upgradeGivensSubMatrix_Q()
{
	double temp;
	for(int i=0; i<p_GivensSubMatrixFor_Q_step->rowNum; i++)
	{
		for(int j=0; j<p_GivensSubMatrixFor_Q_step->columnNum; j++)
		{
			//更新全维度step 左乘矩阵
			temp = p_GivensSubMatrixFor_Q_step->getMatrixElement(i,j);
			this->p_GivensMatrixFor_Q_step->setMatrixElement(i,j,temp);
		}
	}
};

//将Givens变换step子矩阵升级成为全维度变换step矩阵
void QZTriangleZeroChasing::upgradeGivensSubMatrix_Z()
{
	double temp;
	for(int i=0; i<p_GivensSubMatrixFor_Z_step->rowNum; i++)
	{
		for(int j=0; j<p_GivensSubMatrixFor_Z_step->columnNum; j++)
		{
			//更新全维度step 右乘矩阵
			temp = p_GivensSubMatrixFor_Z_step->getMatrixElement(i,j);
			this->p_GivensMatrixFor_Z_step->setMatrixElement(i,j,temp);
		}
	}
};

//更新迭代过程Givens变换矩阵G
void QZTriangleZeroChasing::updateGivensMatrix_Iterate_Q()
{
	//更新Givens左乘 迭代过程矩阵
	p_Multiplier->reload(p_GivensMatrixFor_Q_step, p_GivensMatrixFor_Q_iterate);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Q_iterate->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//更新迭代过程Givens变换矩阵Z
void QZTriangleZeroChasing::updateGivensMatrix_Iterate_Z()
{
	//更新Givens右乘 迭代过程矩阵
	p_Multiplier->reload(p_GivensMatrixFor_Z_iterate, p_GivensMatrixFor_Z_step);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Z_iterate->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//更新总体综合Givens变换矩阵G
void QZTriangleZeroChasing::updateGivensMatrix_Total_Q()
{
	//更新Givens左乘 迭代过程矩阵
	p_Multiplier->reload(p_GivensMatrixFor_Q_iterate,p_GivensMatrixFor_Q_total);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Q_total->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//更新总体综合Givens变换矩阵Z
void QZTriangleZeroChasing::updateGivensMatrix_Total_Z()
{
	//更新Givens右乘 迭代过程矩阵
	p_Multiplier->reload(p_GivensMatrixFor_Z_total, p_GivensMatrixFor_Z_iterate);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Z_total->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用G子矩阵更新A子操作矩阵
void QZTriangleZeroChasing::updateSubOpMatrix_A_By_Q()
{
	p_Multiplier->reload(p_GivensSubMatrixFor_Q_step, p_OpSubMatrix_A);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用Z子矩阵更新A子操作矩阵
void QZTriangleZeroChasing::updateSubOpMatrix_A_By_Z()
{
	p_Multiplier->reload(p_OpSubMatrix_A, p_GivensSubMatrixFor_Z_step);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用G子矩阵更新B子操作矩阵
void QZTriangleZeroChasing::updateSubOpMatrix_B_By_Q()
{
	p_Multiplier->reload(p_GivensSubMatrixFor_Q_step, p_OpSubMatrix_B);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用Z子矩阵更新B子操作矩阵
void QZTriangleZeroChasing::updateSubOpMatrix_B_By_Z()
{
	p_Multiplier->reload(p_OpSubMatrix_B, p_GivensSubMatrixFor_Z_step);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用G矩阵更新A操作矩阵
void QZTriangleZeroChasing::updateOpMatrix_A_By_Q()
{
	p_Multiplier->reload(p_GivensMatrixFor_Q_iterate, p_OpMatrix_A);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用Z矩阵更新A操作矩阵
void QZTriangleZeroChasing::updateOpMatrix_A_By_Z()
{
	p_Multiplier->reload(p_OpMatrix_A, p_GivensMatrixFor_Z_iterate);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用G矩阵更新B操作矩阵
void QZTriangleZeroChasing::updateOpMatrix_B_By_Q()
{
	p_Multiplier->reload(p_GivensMatrixFor_Q_iterate, p_OpMatrix_B);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//使用Z矩阵更新B操作矩阵
void QZTriangleZeroChasing::updateOpMatrix_B_By_Z()
{
	p_Multiplier->reload(p_OpMatrix_B, p_GivensMatrixFor_Z_iterate);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};


BasicMatrix* QZTriangleZeroChasing::getOpMatrix_A()
{
	return this->p_OpMatrix_A;
};
BasicMatrix* QZTriangleZeroChasing::getOpMatrix_B()
{
	return this->p_OpMatrix_B;
};

BasicMatrix* QZTriangleZeroChasing::getGivensMatrix_Q_Total()
{
	return this->p_GivensMatrixFor_Q_total;
};
BasicMatrix* QZTriangleZeroChasing::getGivensMatrix_Z_Total()
{
	return this->p_GivensMatrixFor_Z_total;
};

BasicMatrix* QZTriangleZeroChasing::getGivensMatrix_Q_Iterate()
{
	return this->p_GivensMatrixFor_Q_iterate;
};
BasicMatrix* QZTriangleZeroChasing::getGivensMatrix_Z_Iterate()
{
	return this->p_GivensMatrixFor_Z_iterate;
};

BasicMatrix* QZTriangleZeroChasing::getGivensMatrix_Q_Step()
{
	return this->p_GivensMatrixFor_Q_step;
};
BasicMatrix* QZTriangleZeroChasing::getGivensMatrix_Z_Step()
{
	return this->p_GivensMatrixFor_Z_step;
};

BasicMatrix* QZTriangleZeroChasing::getOpSubMatrix_A()
{
	return this->p_OpSubMatrix_A;
};
BasicMatrix* QZTriangleZeroChasing::getOpSubMatrix_B()
{
	return this->p_OpSubMatrix_B;
};

BasicMatrix* QZTriangleZeroChasing::getGivensSubMatrix_Q_Step()
{
	return this->p_GivensSubMatrixFor_Q_step;
};

BasicMatrix* QZTriangleZeroChasing::getGivensSubMatrix_Z_Step()
{
	return this->p_GivensSubMatrixFor_Z_step;
};


//根据迭代情况重新定义子矩阵行列数
void QZTriangleZeroChasing::resizeSubMatrix(int rowAndColumnNumber)
{
	//opSubMatrix_A = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	//opSubMatrix_B = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);

	//givensSubMatrixFor_G_step = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	//givensSubMatrixFor_G_step.resetMatrixToI();
	//givensSubMatrixFor_Z_step = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	//givensSubMatrixFor_Z_step.resetMatrixToI();
	//左上A子矩阵
	p_OpSubMatrix_A->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_OpSubMatrix_A->resetMatrixToI();

	//左上B子矩阵
	p_OpSubMatrix_B->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_OpSubMatrix_B->resetMatrixToI();

	//左Givens变换子矩阵Q-单步过程矩阵
	p_GivensSubMatrixFor_Q_step->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_GivensSubMatrixFor_Q_step->resetMatrixToI();
	//右Givens变换子矩阵Z-单步过程矩阵
	p_GivensSubMatrixFor_Z_step->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_GivensSubMatrixFor_Z_step->resetMatrixToI();
};


