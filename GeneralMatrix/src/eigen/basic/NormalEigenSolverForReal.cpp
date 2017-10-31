/*
 * NormalEigenSolverForReal.cpp
 *
 *  Created on: 2017年5月21日
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
 * 根据降阶起止点 生成降阶的Hessenberg矩阵
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
	//从原始全维度hessenberg矩阵中 拷贝出已降阶的hessenberg矩阵
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
 * 查找并更新降阶点
 * 在全尺寸操作Hessenberg矩阵中，从右下到左上开始，次主对角线上查找0元
 * 找到0元后，分析0元右下角的子矩阵，是否维度大于2（是否可以进行double-shift迭代）
 * 如果不能迭代，更新降阶结束标识位，继续寻找新的0元
 * 如果可以迭代，更新降阶开始标识位，结束
 */
/*
bool NormalEigenSolverForReal::findNewDeflationPoint()
{
	bool result = false;
	double temp;
	int deflatedSize; //降阶点右下角矩阵维度
	int i=this->deflationEnd;
	while(i>0)
	{
		//查询次对角线元素
		temp = this->p_OpHessenbergMatrix->getMatrixElement(i,i-1);
		if(temp == 0)
		{
			//次对角线元素为0，分析降阶点
			deflatedSize = this->deflationEnd-i+1;

			if(deflatedSize>2)
			{
				//如果降阶点右下方子矩阵维度大于2，则可以进行迭代处理
				this->deflationStart = i;
				return true;
			}
			else
			{
				//如果降阶点右下方子矩阵维度小于等于2
				//更新降阶开始及结束点标识
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
 * 将已降阶的变换矩阵 升级成为全尺寸变换矩阵
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
			//更新QT
			temp = this->p_QTMatrix_Deflated_Iteration->getMatrixElement(m,n);
			this->p_QTMatrix_Iteration->setMatrixElement(i,j,temp);

			//更新Q
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
 * 将单迭代变换矩阵 合并成为总体变换矩阵
 */
void NormalEigenSolverForReal::updateQQTMatrixTotal()
{
	//计算QT_It * QT_Total
	this->p_Multiplier->reload(p_QTMatrix_Iteration, p_QTMatrix_Total);
	this->p_Multiplier->multiplyCalc();
	p_QTMatrix_Total->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//计算Q_Total * Q_It
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
 * 生成hessenberg操作矩阵
 */
void NormalEigenSolverForReal::generateHessenbergOpMatrix()
{
	p_HessenbergForm->reload(this->p_OpMatrix);
	p_HessenbergForm->formularUpperHessnbergMatrix();

	this->p_QTMatrix_Iteration->copyMatrixElementNoCheck(p_HessenbergForm->getPreTransMatrix());
	this->p_QMatrix_Iteration->copyMatrixElementNoCheck(p_HessenbergForm->getAfterTransMatrix());

	//更新总体转换矩阵
	updateQQTMatrixTotal();

	this->p_OpHessenbergMatrix->copyMatrixElementNoCheck(p_HessenbergForm->getOpMatrix());
};

/*
 * 更新原始hessenberg操作矩阵
 */
void NormalEigenSolverForReal::updateHessenbergOpMatrix()
{
	cout << "--------updateHessenbergOpMatrix Before Upgrade---Fullsize OpHessenbergMatrix----------" << endl;
	p_OpHessenbergMatrix->printMatrix();
	//计算QT_It * OpHessenbergMatrix
	this->p_Multiplier->reload(p_QTMatrix_Iteration, p_OpHessenbergMatrix);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	//计算OpHessenbergMatrix * Q_It
	this->p_Multiplier->reload(p_OpHessenbergMatrix, p_QMatrix_Iteration);
	this->p_Multiplier->multiplyCalc();
	p_OpHessenbergMatrix->copyMatrixElementNoCheck(this->p_Multiplier->getMultiplyResult());

	cout << "--------updateHessenbergOpMatrix After Upgrade---Fullsize OpHessenbergMatrix----------" << endl;
	p_OpHessenbergMatrix->printMatrix();

};

/*
 * 初始化特征值计算相关矩阵
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

	//原始矩阵的单迭代变换矩阵
	p_QTMatrix_Iteration->resetMatrixToI();
	p_QMatrix_Iteration->resetMatrixToI();

};
//测试打印，QT_Total * OP * Q
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
 * 计算特征值
 */
void NormalEigenSolverForReal::calcEigenValue()
{
	this->deflationStart = 0;
	this->deflationEnd = this->p_OpMatrix->rowNum - 1;

	//原始矩阵的总体变换矩阵
	p_QTMatrix_Total->resetMatrixToI();
	p_QMatrix_Total->resetMatrixToI();

	//生成原始全维度Hessenberg矩阵
	generateHessenbergOpMatrix();

	//打印总体转换矩阵乘积测试
	showQTOPxQ();

	//初始化相关计算矩阵
	initEigenCalcMatrix();

	//将全维度hessenberg操作矩阵近似对角化
	while(true)
	{
		//Hessenberg矩阵进行整形，将极小值变为0元
		p_OpHessenbergMatrix->regularZeroElement();
		cout << "--------calcEigenValue After Regular---Fullsize OpHessenbergMatrix----------" << endl;
		p_OpHessenbergMatrix->printMatrix();
		//查找降阶点
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
			//生成降阶Hessenberg矩阵
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
		//将降阶转换矩阵升级为全维度转换矩阵
		upgradeDeflatedQQTMatrix();
		//更新原始Hessenberg矩阵
		updateHessenbergOpMatrix();
		//更新总体转换矩阵
		updateQQTMatrixTotal();

		//打印总体转换矩阵乘积测试
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

		//判断对角线的2x2矩阵块是否需要继续对角化
		if(!isDiagonalBlockComplexEigen(p_LastStepMatrix_2x2))
		{
			lastStepIteration(i);
		}
		i++;
	}

	//打印总体转换矩阵乘积测试
	showQTOPxQ();
};


/*
 * 解算结束判断逻辑，降阶标志位指示出的矩阵维度小于等于2
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
 * 2x2对角块是否为复数特征值判断
 * 根据次主对角元非零值所在行索引，计算对角块特征值是否为复数
 *
 * true:复数
 * false:非复数
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
		//对负数开根号，特征值为复数
		return true;
	}

	return false;
};

/*
 * 初步化为对角块以后，最后一步迭代，将对角线指定索引上的2x2对角块进行上三角化
 */
void NormalEigenSolverForReal::lastStepIteration(int startIndex)
{
	double temp;
	//重新设定deflate起止点
	this->deflationStart = startIndex;
	this->deflationEnd = startIndex+1;
	//生成降阶的hessenberg矩阵
	generateDeflatedHessenbergMatrix();

	//如果已经是上三角矩阵，则不处理，直接返回
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

		//将降阶转换矩阵升级为全维度转换矩阵
		upgradeDeflatedQQTMatrix();
		//更新原始Hessenberg矩阵
		updateHessenbergOpMatrix();
		//更新总体转换矩阵
		updateQQTMatrixTotal();

		//打印总体转换矩阵乘积测试
		showQTOPxQ();

		//Hessenberg矩阵进行整形，将极小值变为0元
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
