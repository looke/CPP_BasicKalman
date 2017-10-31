/*
 * NormalEigenSolverForReal.cpp
 *
 *  Created on: 2017��5��21��
 *      Author: looke
 */

#include "NormalEigenSolverForReal.h"
#include "iostream"
using namespace std;


NormalEigenSolverForReal::NormalEigenSolverForReal()
{};

NormalEigenSolverForReal::NormalEigenSolverForReal(BasicMatrix* p_input_OpMatrix)
{
	this->init(p_input_OpMatrix);
};

void NormalEigenSolverForReal::init(BasicMatrix* p_input_OpMatrix)
{};

void NormalEigenSolverForReal::reload(BasicMatrix* p_input_OpMatrix)
{};

/*
 * ���ݽ�����ֹ�� ���ɽ��׵�Hessenberg����
 */
void NormalEigenSolverForReal::generateDeflatedHessenbergMatrix()
{
	int newSize = this->deflationEnd - this->deflationStart + 1;
	this->p_OpHessenbergMatrix_deflated->resizeMatrix(newSize,newSize);
	this->p_OpHessenbergMatrix_deflated->resetMatrixToI();

	p_QTMatrix_Deflated_Iteration->resizeMatrix(newSize,newSize);
	p_QTMatrix_Deflated_Iteration->resetMatrixToI();

	p_QMatrix_Deflated_Iteration->resizeMatrix(newSize,newSize);
	p_QMatrix_Deflated_Iteration->resetMatrixToI();

	double temp;
	//��ԭʼȫά��hessenberg������ �������ѽ��׵�hessenberg����
	for(int i=this->deflationStart,m=0; i<=this->deflationEnd; i++,m++)
	{
		for(int j=this->deflationStart,n=0; j<=this->deflationEnd; j++,n++)
		{
			temp = this->p_OpHessenbergMatrix->getMatrixElement(i,j);
			this->p_OpHessenbergMatrix_deflated->setMatrixElement(m,n,temp);
		}
	}

	cout << "--------generateDeflatedHessenbergMatrix deflated OpHessenbergMatrix----------" << endl;
	p_OpHessenbergMatrix_deflated->printMatrix();

};

/*
 * ���Ҳ����½��׵�
 * ��ȫ�ߴ����Hessenberg�����У������µ����Ͽ�ʼ�������Խ����ϲ���0Ԫ
 * �ҵ�0Ԫ�󣬷���0Ԫ���½ǵ��Ӿ����Ƿ�ά�ȴ���2���Ƿ���Խ���double-shift������
 * ������ܵ��������½��׽�����ʶλ������Ѱ���µ�0Ԫ
 * ������Ե��������½��׿�ʼ��ʶλ������
 */
/*
bool NormalEigenSolverForReal::findNewDeflationPoint()
{
	bool result = false;
	double temp;
	int deflatedSize; //���׵����½Ǿ���ά��
	int i=this->deflationEnd;
	while(i>0)
	{
		//��ѯ�ζԽ���Ԫ��
		temp = this->p_OpHessenbergMatrix->getMatrixElement(i,i-1);
		if(temp == 0)
		{
			//�ζԽ���Ԫ��Ϊ0���������׵�
			deflatedSize = this->deflationEnd-i+1;

			if(deflatedSize>2)
			{
				//������׵����·��Ӿ���ά�ȴ���2������Խ��е�������
				this->deflationStart = i;
				return true;
			}
			else
			{
				//������׵����·��Ӿ���ά��С�ڵ���2
				//���½��׿�ʼ���������ʶ
				this->deflationEnd = i - 1;
				this->deflationStart = 0;
			}
			result = true;
		}
		i--;
	}
	return result;
};
*/
/*
 * ���ѽ��׵ı任���� ������Ϊȫ�ߴ�任����
 */
void NormalEigenSolverForReal::upgradeDeflatedQQTMatrix()
{
	double temp;
	this->p_QTMatrix_Iteration->resetMatrixToI();
	this->p_QMatrix_Iteration->resetMatrixToI();

	cout << "--------upgradeDeflatedQQTMatrix-------------" << endl;
	cout << "--------Deflation Start:" << this->deflationStart << "-----Deflation End:" << this->deflationEnd <<endl;
	cout << "--------Before Upgrade---QT_Deflated----------" << endl;
	this->p_QTMatrix_Deflated_Iteration->printMatrix();
	cout << "--------Before Upgrade---Q_Deflated----------" << endl;
	this->p_QMatrix_Deflated_Iteration->printMatrix();

	for(int i=this->deflationStart,m=0; i<=this->deflationEnd; i++,m++)
	{
		for(int j=this->deflationStart,n=0; j<=this->deflationEnd; j++,n++)
		{
			//����QT
			temp = this->p_QTMatrix_Deflated_Iteration->getMatrixElement(m,n);
			this->p_QTMatrix_Iteration->setMatrixElement(i,j,temp);

			//����Q
			temp = this->p_QMatrix_Deflated_Iteration->getMatrixElement(m,n);
			this->p_QMatrix_Iteration->setMatrixElement(i,j,temp);
		}
	}

	cout << "--------After Upgrade---QT_FullSize----------" << endl;
	this->p_QTMatrix_Iteration->printMatrix();
	cout << "--------After Upgrade---Q_FullSize----------" << endl;
	this->p_QMatrix_Iteration->printMatrix();
};

/*
 * ���������任���� �ϲ���Ϊ����任����
 */
void NormalEigenSolverForReal::updateQQTMatrixTotal()
{
	//����QT_It * QT_Total
	this->p_Multiplier->reload(p_QTMatrix_Iteration, p_QTMatrix_Total);
	this->p_Multiplier->multiplyCalc();
	p_QTMatrix_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//����Q_Total * Q_It
	this->p_Multiplier->reload(p_QMatrix_Total, p_QMatrix_Iteration);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
	cout << "--------updateQQTMatrixTotal----------" << endl;
	cout << "--------After Upgrade---QT_Total FullSize----------" << endl;
	this->p_QTMatrix_Total->printMatrix();
	cout << "--------After Upgrade---Q_Total FullSize----------" << endl;
	this->p_QMatrix_Total->printMatrix();
};

/*
 * ����hessenberg��������
 */
void NormalEigenSolverForReal::generateHessenbergOpMatrix()
{
	p_HessenbergForm->reload(this->p_OpMatrix);
	p_HessenbergForm->formularUpperHessnbergMatrix();

	this->p_QTMatrix_Iteration->copyMatrixElementNoCheck(p_HessenbergForm->getPreTransMatrix());
	this->p_QMatrix_Iteration->copyMatrixElementNoCheck(p_HessenbergForm->getAfterTransMatrix());

	//��������ת������
	updateQQTMatrixTotal();

	this->p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_HessenbergForm->getOpMatrix());
};

/*
 * ����ԭʼhessenberg��������
 */
void NormalEigenSolverForReal::updateHessenbergOpMatrix()
{
	cout << "--------updateHessenbergOpMatrix Before Upgrade---Fullsize OpHessenbergMatrix----------" << endl;
	p_OpHessenbergMatrix->printMatrix();
	//����QT_It * OpHessenbergMatrix
	this->p_Multiplier->reload(p_QTMatrix_Iteration, p_OpHessenbergMatrix);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//����OpHessenbergMatrix * Q_It
	this->p_Multiplier->reload(p_OpHessenbergMatrix, p_QMatrix_Iteration);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "--------updateHessenbergOpMatrix After Upgrade---Fullsize OpHessenbergMatrix----------" << endl;
	p_OpHessenbergMatrix->printMatrix();

};

/*
 * ��ʼ������ֵ������ؾ���
 */
void NormalEigenSolverForReal::initEigenCalcMatrix()
{
	this->p_OpHessenbergMatrix_deflated->resizeMatrix(this->p_OpHessenbergMatrix->rowNum,this->p_OpHessenbergMatrix->columnNum);
	p_OpHessenbergMatrix_deflated->copyMatrixElementNoCheck(p_OpHessenbergMatrix);
	p_DoubleShifeQR->reload(this->p_OpHessenbergMatrix_deflated);

	p_QTMatrix_Deflated_Iteration->resizeMatrix(this->p_OpHessenbergMatrix->rowNum,this->p_OpHessenbergMatrix->columnNum);
	p_QTMatrix_Deflated_Iteration->resetMatrixToI();

	p_QMatrix_Deflated_Iteration->resizeMatrix(this->p_OpHessenbergMatrix->rowNum,this->p_OpHessenbergMatrix->columnNum);
	p_QMatrix_Deflated_Iteration->resetMatrixToI();

	//ԭʼ����ĵ������任����
	p_QTMatrix_Iteration->resetMatrixToI();
	p_QMatrix_Iteration->resetMatrixToI();

};
//���Դ�ӡ��QT_Total * OP * Q
void NormalEigenSolverForReal::showQTOPxQ()
{
	p_testForTemp_nxn->copyMatrixElementNoCheck(this->p_OpMatrix);
	p_testMulti->reload(this->p_QTMatrix_Total, p_testForTemp_nxn);
	p_testMulti->multiplyCalc();
	p_testForTemp_nxn->copyMatrixElementNoCheck(p_testMulti->getMultiplyResult());
	p_testMulti->reload(p_testForTemp_nxn,this->p_QMatrix_Total);
	p_testMulti->multiplyCalc();
	p_testForTemp_nxn->copyMatrixElementNoCheck(p_testMulti->getMultiplyResult());
	cout << "--------------QT_Total * Op_Matrix * Q_Total-----------------" << endl;
	p_testForTemp_nxn->printMatrix();
};
/*
 * ��������ֵ
 */
void NormalEigenSolverForReal::calcEigenValue()
{
	this->deflationStart = 0;
	this->deflationEnd = this->p_OpMatrix->rowNum - 1;

	//ԭʼ���������任����
	p_QTMatrix_Total->resetMatrixToI();
	p_QMatrix_Total->resetMatrixToI();

	//����ԭʼȫά��Hessenberg����
	generateHessenbergOpMatrix();

	//��ӡ����ת������˻�����
	showQTOPxQ();

	//��ʼ����ؼ������
	initEigenCalcMatrix();

	//��ȫά��hessenberg����������ƶԽǻ�
	while(true)
	{
		//Hessenberg����������Σ�����Сֵ��Ϊ0Ԫ
		p_OpHessenbergMatrix->regularZeroElement();
		cout << "--------calcEigenValue After Regular---Fullsize OpHessenbergMatrix----------" << endl;
		p_OpHessenbergMatrix->printMatrix();
		//���ҽ��׵�
		//bool hasNewDeflate = findNewDeflationPoint();
		bool hasNewDeflate = p_HessenbergDeflation->findNewDeflationPoint(p_OpHessenbergMatrix, this->deflationStart,this->deflationEnd);
		this->deflationStart = p_HessenbergDeflation->getNewDeflationStart();
		this->deflationEnd = p_HessenbergDeflation->getNewDeflationEnd();
		if(this->hasFinishedIteration())
		{
			break;
		}

		if(hasNewDeflate)
		{
			//���ɽ���Hessenberg����
			generateDeflatedHessenbergMatrix();
			p_DoubleShifeQR->reload(this->p_OpHessenbergMatrix_deflated);
		}

		p_DoubleShifeQR->wilkinson_IM_QRIteration_Single();
		p_QTMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_DoubleShifeQR->getQTMatrix_Total());
		p_QMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_DoubleShifeQR->getQMatrix_Total());

		cout << "--------calcEigenValue deflated matrix After wilkinson--- QT_Df * OpHessenbergMatrix_Df * Q_Df----------" << endl;
		this->p_Multiplier->reload(p_QTMatrix_Deflated_Iteration,p_OpHessenbergMatrix_deflated);
		this->p_Multiplier->multiplyCalc();
		p_OpHessenbergMatrix_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		this->p_Multiplier->reload(p_OpHessenbergMatrix_deflated,p_QMatrix_Deflated_Iteration);
		this->p_Multiplier->multiplyCalc();
		p_OpHessenbergMatrix_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		p_OpHessenbergMatrix_deflated->printMatrix();
		//������ת����������Ϊȫά��ת������
		upgradeDeflatedQQTMatrix();
		//����ԭʼHessenberg����
		updateHessenbergOpMatrix();
		//��������ת������
		updateQQTMatrixTotal();

		//��ӡ����ת������˻�����
		showQTOPxQ();
	}
	int i = 0;
	double subDiagonalElement;
	while (i < this->p_OpHessenbergMatrix->columnNum - 1)
	{
		subDiagonalElement = p_OpHessenbergMatrix->getMatrixElement(i+1,i);
		if(0 == subDiagonalElement)
		{
			i++;
			continue;
		}
		this->p_LastStepMatrix_2x2->setMatrixElement(0,0,p_OpHessenbergMatrix->getMatrixElement(i,i));
		this->p_LastStepMatrix_2x2->setMatrixElement(0,1,p_OpHessenbergMatrix->getMatrixElement(i,i+1));
		this->p_LastStepMatrix_2x2->setMatrixElement(1,0,p_OpHessenbergMatrix->getMatrixElement(i+1,i));
		this->p_LastStepMatrix_2x2->setMatrixElement(1,1,p_OpHessenbergMatrix->getMatrixElement(i+1,i+1));

		//�ж϶Խ��ߵ�2x2������Ƿ���Ҫ�����Խǻ�
		if(!isDiagonalBlockComplexEigen(p_LastStepMatrix_2x2))
		{
			lastStepIteration(i);
		}
		i++;
	}

	//��ӡ����ת������˻�����
	showQTOPxQ();
};


/*
 * ��������ж��߼������ױ�־λָʾ���ľ���ά��С�ڵ���2
 */
bool NormalEigenSolverForReal::hasFinishedIteration()
{
	int distanceSize = this->deflationEnd - this->deflationStart + 1;
	if(distanceSize<=2)
	{
		return true;
	}
	return false;
};

/*
 * 2x2�Խǿ��Ƿ�Ϊ��������ֵ�ж�
 * ���ݴ����Խ�Ԫ����ֵ����������������Խǿ�����ֵ�Ƿ�Ϊ����
 *
 * true:����
 * false:�Ǹ���
 */
bool NormalEigenSolverForReal::	isDiagonalBlockComplexEigen(BasicMatrix* p_Input_OpMatrix)
{
	double temp;
	double a,b,c,d;

	a = p_Input_OpMatrix->getMatrixElement(0,0);
	b = p_Input_OpMatrix->getMatrixElement(0,1);
	c = p_Input_OpMatrix->getMatrixElement(1,0);
	d = p_Input_OpMatrix->getMatrixElement(1,1);

	if(0 == c)
	{
		return false;
	}

	temp = 0.5*a + 0.5*d;
	temp = temp*temp;
	temp = temp-a*d + b*c;

	if(temp<0)
	{
		//�Ը��������ţ�����ֵΪ����
		return true;
	}

	return false;
};

/*
 * ������Ϊ�Խǿ��Ժ����һ�����������Խ���ָ�������ϵ�2x2�Խǿ���������ǻ�
 */
void NormalEigenSolverForReal::lastStepIteration(int startIndex)
{
	double temp;
	//�����趨deflate��ֹ��
	this->deflationStart = startIndex;
	this->deflationEnd = startIndex+1;
	//���ɽ��׵�hessenberg����
	generateDeflatedHessenbergMatrix();

	//����Ѿ��������Ǿ����򲻴���ֱ�ӷ���
	if(p_OpHessenbergMatrix_deflated->isUpperTriangleMatrix())
	{
		return;
	}

	p_SingleShifeQR->reload(this->p_OpHessenbergMatrix_deflated);

	while(true)
	{
		p_SingleShifeQR->rayleigh_Quotient_IM_QRIteration_Step();
		p_QTMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_SingleShifeQR->getQTMatrix_Total());
		cout << "--------calcEigenValue deflated matrix lastStepIteration--- p_QTMatrix_Deflated_Iteration----------" << endl;
		p_QTMatrix_Deflated_Iteration->printMatrix();

		p_QMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_SingleShifeQR->getQMatrix_Total());
		cout << "--------calcEigenValue deflated matrix lastStepIteration--- p_QMatrix_Deflated_Iteration----------" << endl;
		p_QMatrix_Deflated_Iteration->printMatrix();

		cout << "--------calcEigenValue deflated matrix lastStepIteration--- OpHessenbergMatrix_Df----------" << endl;
		p_OpHessenbergMatrix_deflated->printMatrix();
		cout << "--------calcEigenValue deflated matrix lastStepIteration--- QT_Df * OpHessenbergMatrix_Df * Q_Df----------" << endl;
		this->p_Multiplier->reload(p_QTMatrix_Deflated_Iteration,p_OpHessenbergMatrix_deflated);
		this->p_Multiplier->multiplyCalc();
		p_OpHessenbergMatrix_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		this->p_Multiplier->reload(p_OpHessenbergMatrix_deflated,p_QMatrix_Deflated_Iteration);
		this->p_Multiplier->multiplyCalc();
		p_OpHessenbergMatrix_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		p_OpHessenbergMatrix_deflated->printMatrix();

		//������ת����������Ϊȫά��ת������
		upgradeDeflatedQQTMatrix();
		//����ԭʼHessenberg����
		updateHessenbergOpMatrix();
		//��������ת������
		updateQQTMatrixTotal();

		//��ӡ����ת������˻�����
		showQTOPxQ();

		//Hessenberg����������Σ�����Сֵ��Ϊ0Ԫ
		p_OpHessenbergMatrix->regularZeroElement();
		cout << "--------calcEigenValue lastStepIteration After Regular---Fullsize OpHessenbergMatrix----------" << endl;
		p_OpHessenbergMatrix->printMatrix();

		temp = this->p_OpHessenbergMatrix->getMatrixElement(startIndex+1,startIndex);
		if(0 == temp)
		{
			break;
		}
	}

};


BasicMatrix* NormalEigenSolverForReal::getOpHessenbergMatrix()
{
	return this->p_OpHessenbergMatrix;
};

BasicMatrix* NormalEigenSolverForReal::getEigenValueMatrix()
{
	return this->p_EigenValueMatrix;
};

BasicMatrix* NormalEigenSolverForReal::getQTMatrix_Iteration()
{
	return this->p_QTMatrix_Iteration;
};

BasicMatrix* NormalEigenSolverForReal::getQMatrix_Iteration()
{
	return this->p_QMatrix_Iteration;
};

BasicMatrix* NormalEigenSolverForReal::getQTMatrix_Total()
{
	return this->p_QTMatrix_Total;
};

BasicMatrix* NormalEigenSolverForReal::getQMatrix_Total()
{
	return this->p_QMatrix_Total;
};

BasicMatrix* NormalEigenSolverForReal::getOpHessenbergMatrix_deflated()
{
	return this->p_OpHessenbergMatrix_deflated;
};

BasicMatrix* NormalEigenSolverForReal::getQTMatrix_Deflated_Iteration()
{
	return this->p_QTMatrix_Deflated_Iteration;
};

BasicMatrix* NormalEigenSolverForReal::getQMatrix_Deflated_Iteration()
{
	return this->p_QMatrix_Deflated_Iteration;
};
