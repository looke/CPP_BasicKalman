/*
 * GeneralizedEigenSolverForReal.cpp
 *
 *  Created on: 2017��6��1��
 *      Author: looke
 */

#include "GeneralizedEigenSolverForReal.h"
#include "iostream"
using namespace std;

GeneralizedEigenSolverForReal::GeneralizedEigenSolverForReal()
{};

GeneralizedEigenSolverForReal::GeneralizedEigenSolverForReal(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{
	this->init(p_input_OpMatrix_A, p_input_OpMatrix_B);
};

void GeneralizedEigenSolverForReal::init(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{};

void GeneralizedEigenSolverForReal::reload(BasicMatrix* p_input_OpMatrix_A, BasicMatrix* p_input_OpMatrix_B)
{};

/*
 * ����ԭʼHessenberg-Triangle��������
 */
void GeneralizedEigenSolverForReal::generateHTOpMatrix()
{
	this->p_HessenbergTriangleFormular->reload(this->p_OpMatrix_A,this->p_OpMatrix_B);
	this->p_HessenbergTriangleFormular->formularABMatrix();
	this->p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getHessenbergMatrixA());
	this->p_OpMatrix_Triangle->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getTriangleMatrixB());

	//QZ�任����-������
	this->p_QMatrix_Iteration->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getMatrixQ_Total());
	this->p_ZMatrix_Iteration->copyMatrixElementNoCheck(p_HessenbergTriangleFormular->getMatrixZ_Total());

	//��������ת������
	updateQZMatrixTotal();

	cout << "--------generateHTOpMatrix full OpHessenbergMatrix----------" << endl;
	p_OpMatrix_Hessenberg->printMatrix();
	cout << "--------generateHTOpMatrix full OpTriangleMatrix----------" << endl;
	p_OpMatrix_Triangle->printMatrix();
};


/*
 * ���ݽ��׵� ���ɽ��׵�Hessenberg-Tirangle���� �����¹滮��Ӧ��ת������
 */
void GeneralizedEigenSolverForReal::generateDeflatedHTMatrixPair()
{
	int newSize = this->deflationEnd - this->deflationStart + 1;
	this->p_OpMatrix_Hessenberg_deflated->resizeMatrix(newSize,newSize);
	this->p_OpMatrix_Hessenberg_deflated->resetMatrixToI();
	this->p_OpMatrix_Triangle_deflated->resizeMatrix(newSize,newSize);
	this->p_OpMatrix_Triangle_deflated->resetMatrixToI();

	p_QMatrix_Deflated_Iteration->resizeMatrix(newSize,newSize);
	p_QMatrix_Deflated_Iteration->resetMatrixToI();

	p_ZMatrix_Deflated_Iteration->resizeMatrix(newSize,newSize);
	p_ZMatrix_Deflated_Iteration->resetMatrixToI();


	double temp;
	//��ԭʼȫά��hessenberg-Triangle������ �������ѽ��׵�hessenberg-Triangle����
	for(int i=this->deflationStart,m=0; i<=this->deflationEnd; i++,m++)
	{
		for(int j=this->deflationStart,n=0; j<=this->deflationEnd; j++,n++)
		{
			temp = this->p_OpMatrix_Hessenberg->getMatrixElement(i,j);
			this->p_OpMatrix_Hessenberg_deflated->setMatrixElement(m,n,temp);

			temp = this->p_OpMatrix_Triangle->getMatrixElement(i,j);
			this->p_OpMatrix_Triangle_deflated->setMatrixElement(m,n,temp);
		}
	}

	cout << "--------generateDeflatedHTMatrixPair deflated OpHessenbergMatrix----------" << endl;
	p_OpMatrix_Hessenberg_deflated->printMatrix();
	cout << "--------generateDeflatedHTMatrixPair deflated OpTriangleMatrix----------" << endl;
	p_OpMatrix_Triangle_deflated->printMatrix();

};

/*
 * ���ѽ��׵ı任���� ������Ϊȫ�ߴ�任����
 */
void GeneralizedEigenSolverForReal::upgradeDeflatedQZMatrix()
{
	double temp;
	this->p_QMatrix_Iteration->resetMatrixToI();
	this->p_ZMatrix_Iteration->resetMatrixToI();

	cout << "--------upgradeDeflatedQZMatrix-------------" << endl;
	cout << "--------Deflation Start:" << this->deflationStart << "-----Deflation End:" << this->deflationEnd <<endl;
	cout << "--------Before Upgrade---Q_Deflated----------" << endl;
	this->p_QMatrix_Deflated_Iteration->printMatrix();
	cout << "--------Before Upgrade---Z_Deflated----------" << endl;
	this->p_ZMatrix_Deflated_Iteration->printMatrix();

	for(int i=this->deflationStart,m=0; i<=this->deflationEnd; i++,m++)
	{
		for(int j=this->deflationStart,n=0; j<=this->deflationEnd; j++,n++)
		{
			//����QT
			temp = this->p_QMatrix_Deflated_Iteration->getMatrixElement(m,n);
			this->p_QMatrix_Iteration->setMatrixElement(i,j,temp);

			//����Q
			temp = this->p_ZMatrix_Deflated_Iteration->getMatrixElement(m,n);
			this->p_ZMatrix_Iteration->setMatrixElement(i,j,temp);
		}
	}

	cout << "--------After Upgrade---Q_FullSize----------" << endl;
	this->p_QMatrix_Iteration->printMatrix();
	cout << "--------After Upgrade---Z_FullSize----------" << endl;
	this->p_ZMatrix_Iteration->printMatrix();
};

/*
 * ���������任���� �ϲ���Ϊ����任����
 */
void GeneralizedEigenSolverForReal::updateQZMatrixTotal()
{
	//����Q_It * Q_Total
	this->p_Multiplier->reload(p_QMatrix_Iteration, p_QMatrix_Total);
	this->p_Multiplier->multiplyCalc();
	p_QMatrix_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//����Z_Total * Z_It
	this->p_Multiplier->reload(p_ZMatrix_Total, p_ZMatrix_Iteration);
	this->p_Multiplier->multiplyCalc();
	p_ZMatrix_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
	cout << "--------updateQZMatrixTotal----------" << endl;
	cout << "--------After Upgrade---Q_Total FullSize----------" << endl;
	this->p_QMatrix_Total->printMatrix();
	cout << "--------After Upgrade---Z_Total FullSize----------" << endl;
	this->p_ZMatrix_Total->printMatrix();
};

//ʹ��Q�������H-T�����
void GeneralizedEigenSolverForReal::updateHTMatrixByQ()
{
	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByQ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByQ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//���¾���Hessenberg A
	this->p_Multiplier->reload(p_QMatrix_Iteration, p_OpMatrix_Hessenberg);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Triangle B
	this->p_Multiplier->reload(p_QMatrix_Iteration, p_OpMatrix_Triangle);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByQ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByQ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};

//ʹ��Z�����ҳ�H-T�����
void GeneralizedEigenSolverForReal::updateHTMatrixByZ()
{
	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByZ----OP Hessenberg Matrix Before" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByZ----OP Triangle Matrix Before" << endl;
	this->p_OpMatrix_Triangle->printMatrix();

	//���¾���Hessenberg A
	this->p_Multiplier->reload(p_OpMatrix_Hessenberg, p_ZMatrix_Iteration);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Hessenberg->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//���¾���Triangle B
	this->p_Multiplier->reload(p_OpMatrix_Triangle, p_ZMatrix_Iteration);
	this->p_Multiplier->multiplyCalc();
	p_OpMatrix_Triangle->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByZ----OP Hessenberg Matrix After" << endl;
	this->p_OpMatrix_Hessenberg->printMatrix();
	cout << "GeneralizedEigenSolverForReal--updateHTMatrixByZ----OP Triangle Matrix After" << endl;
	this->p_OpMatrix_Triangle->printMatrix();
};


//��ʼ������ֵ������ؾ���
void GeneralizedEigenSolverForReal::initEigenCalcMatrix()
{
	this->p_OpMatrix_Hessenberg_deflated->resizeMatrix(this->p_OpMatrix_Hessenberg->rowNum,this->p_OpMatrix_Hessenberg->columnNum);
	p_OpMatrix_Hessenberg_deflated->copyMatrixElementNoCheck(p_OpMatrix_Hessenberg);
	this->p_OpMatrix_Triangle_deflated->resizeMatrix(this->p_OpMatrix_Triangle->rowNum,this->p_OpMatrix_Triangle->columnNum);
	p_OpMatrix_Triangle_deflated->copyMatrixElementNoCheck(p_OpMatrix_Triangle);

	p_DoubleShifeQZ->reload(this->p_OpMatrix_Hessenberg_deflated, this->p_OpMatrix_Triangle_deflated);

	p_QMatrix_Deflated_Iteration->resizeMatrix(this->p_OpMatrix_Hessenberg->rowNum,this->p_OpMatrix_Hessenberg->columnNum);
	p_QMatrix_Deflated_Iteration->resetMatrixToI();

	p_ZMatrix_Deflated_Iteration->resizeMatrix(this->p_OpMatrix_Hessenberg->rowNum,this->p_OpMatrix_Hessenberg->columnNum);
	p_ZMatrix_Deflated_Iteration->resetMatrixToI();

	//ԭʼ����ĵ������任����
	p_QMatrix_Iteration->resetMatrixToI();
	p_ZMatrix_Iteration->resetMatrixToI();


};

//��������ж��߼�
bool GeneralizedEigenSolverForReal::hasFinishedIteration()
{
	int distanceSize = this->deflationEnd - this->deflationStart + 1;
	if(distanceSize<=2)
	{
		return true;
	}
	return false;
};

//����2x2�Խǿ��Ƿ�Ϊ��������ֵ�ж�
bool GeneralizedEigenSolverForReal::isDiagonalBlockComplexEigen(BasicMatrix* p_Input_OpMatrix_A, BasicMatrix* p_Input_OpMatrix_B)
{
	this->p_ABInvCalc->generateABinvFirst2x2(p_Input_OpMatrix_A,p_Input_OpMatrix_B);
	double temp;
	double a,b,c,d;

	a = p_ABInvCalc->getABinv11();
	b = p_ABInvCalc->getABinv12();
	c = p_ABInvCalc->getABinv21();
	d = p_ABInvCalc->getABinv22();

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

//���Դ�ӡ��Q_Total * OP * Z_Total
void GeneralizedEigenSolverForReal::showQxOPxZ()
{
	p_testForTemp_A_nxn->copyMatrixElementNoCheck(this->p_OpMatrix_A);
	p_testMulti->reload(this->p_QMatrix_Total, p_testForTemp_A_nxn);
	p_testMulti->multiplyCalc();
	p_testForTemp_A_nxn->copyMatrixElementNoCheck(p_testMulti->getMultiplyResult());
	p_testMulti->reload(p_testForTemp_A_nxn,this->p_ZMatrix_Total);
	p_testMulti->multiplyCalc();
	p_testForTemp_A_nxn->copyMatrixElementNoCheck(p_testMulti->getMultiplyResult());
	cout << "--------------Q_Total * Op_Matrix_A * Z_Total-----------------" << endl;
	p_testForTemp_A_nxn->printMatrix();

	p_testForTemp_B_nxn->copyMatrixElementNoCheck(this->p_OpMatrix_B);
	p_testMulti->reload(this->p_QMatrix_Total, p_testForTemp_B_nxn);
	p_testMulti->multiplyCalc();
	p_testForTemp_B_nxn->copyMatrixElementNoCheck(p_testMulti->getMultiplyResult());
	p_testMulti->reload(p_testForTemp_B_nxn,this->p_ZMatrix_Total);
	p_testMulti->multiplyCalc();
	p_testForTemp_B_nxn->copyMatrixElementNoCheck(p_testMulti->getMultiplyResult());
	cout << "--------------Q_Total * Op_Matrix_B * Z_Total-----------------" << endl;
	p_testForTemp_B_nxn->printMatrix();
};

//��������ֵ
void GeneralizedEigenSolverForReal::calcEigenValue()
{
	this->deflationStart = 0;
	this->deflationEnd = this->p_OpMatrix_A->rowNum - 1;
	//ԭʼ���������任����
	p_QMatrix_Total->resetMatrixToI();
	p_ZMatrix_Total->resetMatrixToI();

	//����ԭʼȫά��Hessenberg-Triangle����
	generateHTOpMatrix();

	//��ӡ����ת������˻�����
	showQxOPxZ();

	//������Triangle�Խ�����Ԫ�½�����
	p_QZTriangleZeroChasing->reload(this->p_OpMatrix_Hessenberg,this->p_OpMatrix_Triangle);
	p_QZTriangleZeroChasing->deflate();
	p_QMatrix_Iteration->copyMatrixElementNoCheck(p_QZTriangleZeroChasing->getGivensMatrix_Q_Total());
	p_ZMatrix_Iteration->copyMatrixElementNoCheck(p_QZTriangleZeroChasing->getGivensMatrix_Z_Total());
	//����ԭʼHessenberg-Trianlge ����ʹ��Q�������H-T�����
	updateHTMatrixByQ();
	//����ԭʼHessenberg-Trianlge ����ʹ��Z�����ҳ�H-T�����
	updateHTMatrixByZ();
	//��������ת������
	updateQZMatrixTotal();
	//��ӡ����ת������˻�����
	showQxOPxZ();

	//��ʼ����ؾ���
	initEigenCalcMatrix();

	//��hessenberg����������ƶԽǻ�
	while(true)
	{
		//Hessenberg����������Σ�����Сֵ��Ϊ0Ԫ
		this->p_OpMatrix_Hessenberg->regularZeroElement();
		this->p_OpMatrix_Triangle->regularZeroElement();
		cout << "--------calcEigenValue After Regular---Fullsize OpHessenbergMatrix----------" << endl;
		p_OpMatrix_Hessenberg->printMatrix();
		cout << "--------calcEigenValue After Regular---Fullsize OpTriangleMatrix----------" << endl;
		p_OpMatrix_Triangle->printMatrix();

		bool hasNewDeflate = p_HessenbergDeflation->findNewDeflationPoint(p_OpMatrix_Hessenberg, this->deflationStart,this->deflationEnd);
		this->deflationStart = p_HessenbergDeflation->getNewDeflationStart();
		this->deflationEnd = p_HessenbergDeflation->getNewDeflationEnd();

		if(this->hasFinishedIteration())
		{
			break;
		}

		if(hasNewDeflate)
		{
			//���ɽ���Hessenberg-Triangle����
			generateDeflatedHTMatrixPair();
			p_DoubleShifeQZ->reload(this->p_OpMatrix_Hessenberg_deflated,this->p_OpMatrix_Triangle_deflated);
		}

		p_DoubleShifeQZ->wilkinson_IM_QZIteration_Single();
		p_QMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_DoubleShifeQZ->getQMatrix_Total());
		p_ZMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_DoubleShifeQZ->getZMatrix_Total());

		cout << "--------calcEigenValue deflated matrix After wilkinson--- Q_DF * OpHessenbergMatrix_Df * Z_Df----------" << endl;
		this->p_Multiplier->reload(p_QMatrix_Deflated_Iteration,p_OpMatrix_Hessenberg_deflated);
		this->p_Multiplier->multiplyCalc();
		p_OpMatrix_Hessenberg_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		this->p_Multiplier->reload(p_OpMatrix_Hessenberg_deflated,p_ZMatrix_Deflated_Iteration);
		this->p_Multiplier->multiplyCalc();
		p_OpMatrix_Hessenberg_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		p_OpMatrix_Hessenberg_deflated->printMatrix();

		cout << "--------calcEigenValue deflated matrix After wilkinson--- Q_DF * OpTriangleMatrix_Df * Z_Df----------" << endl;
		this->p_Multiplier->reload(p_QMatrix_Deflated_Iteration,p_OpMatrix_Triangle_deflated);
		this->p_Multiplier->multiplyCalc();
		p_OpMatrix_Triangle_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		this->p_Multiplier->reload(p_OpMatrix_Triangle_deflated,p_ZMatrix_Deflated_Iteration);
		this->p_Multiplier->multiplyCalc();
		p_OpMatrix_Triangle_deflated->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());
		p_OpMatrix_Triangle_deflated->printMatrix();

		//������ת����������Ϊȫά��ת������
		upgradeDeflatedQZMatrix();
		//����ԭʼHessenberg-Trianlge ����ʹ��Q�������H-T�����
		updateHTMatrixByQ();
		//����ԭʼHessenberg-Trianlge ����ʹ��Z�����ҳ�H-T�����
		updateHTMatrixByZ();
		//��������ת������
		updateQZMatrixTotal();
		//��ӡ����ת������˻�����
		showQxOPxZ();
	}
	int i = 0;
	double subDiagonalElement;
	while (i < this->p_OpMatrix_Hessenberg->columnNum - 1)
	{
		subDiagonalElement = p_OpMatrix_Hessenberg->getMatrixElement(i+1,i);
		if(0 == subDiagonalElement)
		{
			i++;
			continue;
		}
		this->p_LastStepMatrix_2x2_Hessenberg->setMatrixElement(0,0,p_OpMatrix_Hessenberg->getMatrixElement(i,i));
		this->p_LastStepMatrix_2x2_Hessenberg->setMatrixElement(0,1,p_OpMatrix_Hessenberg->getMatrixElement(i,i+1));
		this->p_LastStepMatrix_2x2_Hessenberg->setMatrixElement(1,0,p_OpMatrix_Hessenberg->getMatrixElement(i+1,i));
		this->p_LastStepMatrix_2x2_Hessenberg->setMatrixElement(1,1,p_OpMatrix_Hessenberg->getMatrixElement(i+1,i+1));

		this->p_LastStepMatrix_2x2_Triangle->setMatrixElement(0,0,p_OpMatrix_Triangle->getMatrixElement(i,i));
		this->p_LastStepMatrix_2x2_Triangle->setMatrixElement(0,1,p_OpMatrix_Triangle->getMatrixElement(i,i+1));
		this->p_LastStepMatrix_2x2_Triangle->setMatrixElement(1,0,p_OpMatrix_Triangle->getMatrixElement(i+1,i));
		this->p_LastStepMatrix_2x2_Triangle->setMatrixElement(1,1,p_OpMatrix_Triangle->getMatrixElement(i+1,i+1));

		//�ж϶Խ��ߵ�2x2������Ƿ���Ҫ�����Խǻ�
		if(!isDiagonalBlockComplexEigen(p_LastStepMatrix_2x2_Hessenberg,p_LastStepMatrix_2x2_Triangle))
		{
			lastStepIteration(i);
		}
		i++;
	}
};

//������Ϊ�Խǿ��Ժ����һ����������0,1�����ϵ�2x2�Խǿ���������ǻ�
void GeneralizedEigenSolverForReal::lastStepIteration(int startIndex)
{
	double temp;
	//�����趨deflate��ֹ��
	this->deflationStart = startIndex;
	this->deflationEnd = startIndex + 1;
	//���ɽ��׵�hessenberg-Triangle����
	generateDeflatedHTMatrixPair();

	p_SingleShifeQZ->reload(this->p_OpMatrix_Hessenberg_deflated,this->p_OpMatrix_Triangle_deflated);

	while(true)
	{
		p_SingleShifeQZ->rayleigh_Quotient_IM_QZIteration_Step();
		p_QMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_SingleShifeQZ->getQMatrix_Total());
		p_ZMatrix_Deflated_Iteration->copyMatrixElementNoCheck(p_SingleShifeQZ->getZMatrix_Total());

		//������ת����������Ϊȫά��ת������
		upgradeDeflatedQZMatrix();

		//����ԭʼHessenberg-Trianlge ����ʹ��Q�������H-T�����
		updateHTMatrixByQ();
		//����ԭʼHessenberg-Trianlge ����ʹ��Z�����ҳ�H-T�����
		updateHTMatrixByZ();

		//��������ת������
		updateQZMatrixTotal();

		//��ӡ����ת������˻�����
		showQxOPxZ();

		//Hessenberg����������Σ�����Сֵ��Ϊ0Ԫ
		p_OpMatrix_Hessenberg->regularZeroElement();
		cout << "--------calcEigenValue lastStepIteration After Regular---Fullsize OpHessenbergMatrix----------" << endl;
		p_OpMatrix_Hessenberg->printMatrix();

		p_OpMatrix_Triangle->regularZeroElement();
		cout << "--------calcEigenValue lastStepIteration After Regular---Fullsize OpTriangleMatrix----------" << endl;
		p_OpMatrix_Triangle->printMatrix();

		temp = this->p_OpMatrix_Hessenberg->getMatrixElement(startIndex+1,startIndex);
		if(0 == temp)
		{
			break;
		}
	}
};

//��ȡH-T�����
BasicMatrix* GeneralizedEigenSolverForReal::getHessenbergMatrix()
{
	return this->p_OpMatrix_Hessenberg;
};
BasicMatrix* GeneralizedEigenSolverForReal::getTriangleMatrix()
{
	return this->p_OpMatrix_Triangle;
};

//��ȡQ\Z �ۺ�ת������
BasicMatrix* GeneralizedEigenSolverForReal::getQMatrix_Total()
{
	return this->p_QMatrix_Total;
};
BasicMatrix* GeneralizedEigenSolverForReal::getZMatrix_Total()
{
	return this->p_ZMatrix_Total;
};
