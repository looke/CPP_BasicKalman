/*
 * HessenbergTriangleDeflation.cpp
 *
 *  Created on: 2017��4��28��
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


//����Ԫ
void QZTriangleZeroChasing::deflate()
{
	int subMatrixSize;
	int zeroIndex;

	cout << "deflate----clean Q\Z total" << endl;
	//��Givens�任����Q-�����ۺϾ���
	p_GivensMatrixFor_Q_total->resetMatrixToI();
	//��Givens�任����Z-�����ۺϾ���
	p_GivensMatrixFor_Z_total->resetMatrixToI();


	for(int i=0; i<this->p_OpMatrix_A->rowNum; i++)
	{
		cout << "deflate----start iterate:" << i << endl;

		subMatrixSize = p_OpMatrix_A->rowNum-i;
		//�Ӿ���ά��С��2ʱ�˳�ѭ��
		if(subMatrixSize < 2)
		{
			deflate_End_New = p_OpMatrix_A->rowNum - 1 - i;
			cout << "deflate----subMatrixSize < 2 quit!:" << deflate_End_New << endl;
			break;
		}

		cout << "deflate----Generate Sub Matrix" << endl;

		//���������Ӿ���,�Լ���Ӧ���ӱ任����
		generateSubMatrix(i);

		cout << "deflate---- Sub A " <<endl;
		this->p_OpSubMatrix_A->printMatrix();
		cout << "deflate---- Sub B " <<endl;
		this->p_OpSubMatrix_B->printMatrix();

		//��ȡ���Խ���0Ԫλ������
		zeroIndex = this->p_OpSubMatrix_B->indexOfZeroOnDiagonal();
		cout << "deflate----Zero Index of Sub B:" << zeroIndex << endl;

		//�ж����Խ���0Ԫ��λ��
		if(zeroIndex < 0)
		{
			//���������0Ԫ,���˳�,˵��������Ҫ����Ԫ
			deflate_End_New = p_OpMatrix_A->rowNum - 1 - i;
			cout << "deflate----No Zero, Quit:"<< deflate_End_New <<endl;
			break;
		}

		cout << "deflate----clean Q\Z iterate" << endl;
		//��Givens�任����Q-�������̾���
		p_GivensMatrixFor_Q_iterate->resetMatrixToI();
		//��Givens�任����Z-�������̾���
		p_GivensMatrixFor_Z_iterate->resetMatrixToI();

		if(zeroIndex < subMatrixSize-1)
		{
			//���0Ԫ����B�Ӿ������½�,����Ԫ,��0Ԫ���Ӿ������½�
			for (int j=zeroIndex+1; j<subMatrixSize; j++)
			{
				cout << "deflate---- Sub B target:" << j << endl;

				cout << "deflate----clean Q\Z step" << endl;
				//��Givens�任����G-�������̾���
				p_GivensMatrixFor_Q_step->resetMatrixToI();
				//��Givens�任����Z-�������̾���
				p_GivensMatrixFor_Z_step->resetMatrixToI();

				//����B�Ӿ�������Q�Ӿ���
				generateGivensSubMatrixForB(j);
				//����A,B�Ӿ���
				updateSubOpMatrix_A_By_Q();
				updateSubOpMatrix_B_By_Q();
				cout << "deflate---- Sub Q A " <<endl;
				this->p_OpSubMatrix_A->printMatrix();
				cout << "deflate---- Sub Q B " <<endl;
				this->p_OpSubMatrix_B->printMatrix();
				//����A�Ӿ�������Z�Ӿ���
				generateGivensSubMatrixForA(j);
				//����A,B�Ӿ���
				updateSubOpMatrix_A_By_Z();
				updateSubOpMatrix_B_By_Z();

				cout << "deflate---- Sub G A Z" <<endl;
				this->p_OpSubMatrix_A->printMatrix();
				cout << "deflate---- Sub G B Z" <<endl;
				this->p_OpSubMatrix_B->printMatrix();

				//��Z�Ӿ�������ΪZ����
				upgradeGivensSubMatrix_Q();
				upgradeGivensSubMatrix_Z();

				//����Z��������
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
		//��Givens�任����Z-�������̾���
		p_GivensMatrixFor_Z_step->resetMatrixToI();

		//��ʱ0ԪӦ��λ��B�Ӿ������½�,��A�Ӿ����ٽ���һ�α任,����ĩ�дζԽ�ԪΪ0
		generateGivensSubMatrixForA_last();
		//����A,B�Ӿ���
		updateSubOpMatrix_A_By_Z();
		updateSubOpMatrix_B_By_Z();
		cout << "deflate---- Sub A Z_final" <<endl;
		this->p_OpSubMatrix_A->printMatrix();
		cout << "deflate---- Sub B Z_final" <<endl;
		this->p_OpSubMatrix_B->printMatrix();

		//��Z�Ӿ�������ΪZ����
		upgradeGivensSubMatrix_Z();
		//����Z��������
		updateGivensMatrix_Iterate_Z();
		cout << "deflate---- Z iterate" <<endl;
		this->p_GivensMatrixFor_Z_iterate->printMatrix();

		//���任����ʩ����OP�������󣬸���G,Z�ۺϱ任����
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


/* ���ݵ�ǰ���� ΪAB�Ӿ�������Givens�任�Ӿ���Q(QΪ��˾���ZΪ�ҳ˾���)
 * index��ʾB�Ӿ�����Ҫ���Խ�Ԫ�������,
 * ����index���Ի���B�Ӿ������ɽ�B�Ӿ���index��ʾ���жԽ�����Ԫ����ľ���ı任G
 * ����index���Ի���A�Ӿ������ɽ�A�Ӿ���ԭΪHessenberg����ı任Z
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

/* ���ݵ�ǰ���� ΪAB�Ӿ�������Givens�任�Ӿ���Z(QΪ��˾���ZΪ�ҳ˾���)
 * index��ʾB�Ӿ�����Ҫ���Խ�Ԫ�������,
 * ����index���Ի���B�Ӿ������ɽ�B�Ӿ���index��ʾ���жԽ�����Ԫ����ľ���ı任G
 * ����index���Ի���A�Ӿ������ɽ�A�Ӿ���ԭΪHessenberg����ı任Z
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
	//�˴�Ӧ�������жϣ�����ָ��λ�õ�Ԫ���Ƿ��Ѿ�Ϊ0������Ѿ�Ϊ0������Ҫ������Ԫ

	this->p_GivensTrans->reload(p_Vector);
	p_GivensSubMatrixFor_Z_step->copyMatrixElementNoCheck(this->p_GivensTrans->getGivensMatrixAfterMultiple(rowIndex-1));

	//test print
	cout <<"generateGivensSubMatrixForA_last---- sub A givens Z:" << endl;
	p_GivensSubMatrixFor_Z_step->printMatrix();

};

//���ݵ�ǰ�������� ���������Ӿ���
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

//��Givens�任step�Ӿ���Q������Ϊȫά�ȱ任step����Q
void QZTriangleZeroChasing::upgradeGivensSubMatrix_Q()
{
	double temp;
	for(int i=0; i<p_GivensSubMatrixFor_Q_step->rowNum; i++)
	{
		for(int j=0; j<p_GivensSubMatrixFor_Q_step->columnNum; j++)
		{
			//����ȫά��step ��˾���
			temp = p_GivensSubMatrixFor_Q_step->getMatrixElement(i,j);
			this->p_GivensMatrixFor_Q_step->setMatrixElement(i,j,temp);
		}
	}
};

//��Givens�任step�Ӿ���������Ϊȫά�ȱ任step����
void QZTriangleZeroChasing::upgradeGivensSubMatrix_Z()
{
	double temp;
	for(int i=0; i<p_GivensSubMatrixFor_Z_step->rowNum; i++)
	{
		for(int j=0; j<p_GivensSubMatrixFor_Z_step->columnNum; j++)
		{
			//����ȫά��step �ҳ˾���
			temp = p_GivensSubMatrixFor_Z_step->getMatrixElement(i,j);
			this->p_GivensMatrixFor_Z_step->setMatrixElement(i,j,temp);
		}
	}
};

//���µ�������Givens�任����G
void QZTriangleZeroChasing::updateGivensMatrix_Iterate_Q()
{
	//����Givens��� �������̾���
	p_Multiplier->reload(p_GivensMatrixFor_Q_step, p_GivensMatrixFor_Q_iterate);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Q_iterate->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//���µ�������Givens�任����Z
void QZTriangleZeroChasing::updateGivensMatrix_Iterate_Z()
{
	//����Givens�ҳ� �������̾���
	p_Multiplier->reload(p_GivensMatrixFor_Z_iterate, p_GivensMatrixFor_Z_step);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Z_iterate->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//���������ۺ�Givens�任����G
void QZTriangleZeroChasing::updateGivensMatrix_Total_Q()
{
	//����Givens��� �������̾���
	p_Multiplier->reload(p_GivensMatrixFor_Q_iterate,p_GivensMatrixFor_Q_total);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Q_total->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//���������ۺ�Givens�任����Z
void QZTriangleZeroChasing::updateGivensMatrix_Total_Z()
{
	//����Givens�ҳ� �������̾���
	p_Multiplier->reload(p_GivensMatrixFor_Z_total, p_GivensMatrixFor_Z_iterate);
	p_Multiplier->multiplyCalc();
	p_GivensMatrixFor_Z_total->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��G�Ӿ������A�Ӳ�������
void QZTriangleZeroChasing::updateSubOpMatrix_A_By_Q()
{
	p_Multiplier->reload(p_GivensSubMatrixFor_Q_step, p_OpSubMatrix_A);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��Z�Ӿ������A�Ӳ�������
void QZTriangleZeroChasing::updateSubOpMatrix_A_By_Z()
{
	p_Multiplier->reload(p_OpSubMatrix_A, p_GivensSubMatrixFor_Z_step);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��G�Ӿ������B�Ӳ�������
void QZTriangleZeroChasing::updateSubOpMatrix_B_By_Q()
{
	p_Multiplier->reload(p_GivensSubMatrixFor_Q_step, p_OpSubMatrix_B);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��Z�Ӿ������B�Ӳ�������
void QZTriangleZeroChasing::updateSubOpMatrix_B_By_Z()
{
	p_Multiplier->reload(p_OpSubMatrix_B, p_GivensSubMatrixFor_Z_step);
	p_Multiplier->multiplyCalc();
	p_OpSubMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��G�������A��������
void QZTriangleZeroChasing::updateOpMatrix_A_By_Q()
{
	p_Multiplier->reload(p_GivensMatrixFor_Q_iterate, p_OpMatrix_A);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��Z�������A��������
void QZTriangleZeroChasing::updateOpMatrix_A_By_Z()
{
	p_Multiplier->reload(p_OpMatrix_A, p_GivensMatrixFor_Z_iterate);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_A->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��G�������B��������
void QZTriangleZeroChasing::updateOpMatrix_B_By_Q()
{
	p_Multiplier->reload(p_GivensMatrixFor_Q_iterate, p_OpMatrix_B);
	p_Multiplier->multiplyCalc();
	p_OpMatrix_B->copyMatrixElementNoCheck(p_Multiplier->getMultiplyResult());
};

//ʹ��Z�������B��������
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


//���ݵ���������¶����Ӿ���������
void QZTriangleZeroChasing::resizeSubMatrix(int rowAndColumnNumber)
{
	//opSubMatrix_A = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	//opSubMatrix_B = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);

	//givensSubMatrixFor_G_step = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	//givensSubMatrixFor_G_step.resetMatrixToI();
	//givensSubMatrixFor_Z_step = DynamicMatrix(rowAndColumnNumber, rowAndColumnNumber);
	//givensSubMatrixFor_Z_step.resetMatrixToI();
	//����A�Ӿ���
	p_OpSubMatrix_A->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_OpSubMatrix_A->resetMatrixToI();

	//����B�Ӿ���
	p_OpSubMatrix_B->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_OpSubMatrix_B->resetMatrixToI();

	//��Givens�任�Ӿ���Q-�������̾���
	p_GivensSubMatrixFor_Q_step->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_GivensSubMatrixFor_Q_step->resetMatrixToI();
	//��Givens�任�Ӿ���Z-�������̾���
	p_GivensSubMatrixFor_Z_step->resizeMatrix(rowAndColumnNumber,rowAndColumnNumber);
	p_GivensSubMatrixFor_Z_step->resetMatrixToI();
};


