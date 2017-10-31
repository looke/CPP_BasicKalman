/*
 * MatrixInverser.cpp
 *
 *  Created on: 2017年2月27日
 *      Author: looke
 */

#include <dynamic/util/DynamicMatrixInverser.h>
#include <dynamic/DynamicMatrix.h>

DynamicMatrixInverser::DynamicMatrixInverser(BasicMatrix* input_opMatrix):MatrixInverser(input_opMatrix)
{
	this->init(input_opMatrix);
};

/*
 * 	初始化各项参数、矩阵
 */
void DynamicMatrixInverser::init(BasicMatrix* input_opMatrix)
{

	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;


	//只有方阵可以求逆
	if(rowNumber == columnNumber)
	{
		isSquareMatrix = true;
	}

	this->operateMatrix = DynamicMatrix(rowNumber, columnNumber);
	this->p_operateMatrix = &this->operateMatrix;
	this->inverseMatrix = DynamicMatrix(rowNumber, columnNumber);
	this->p_inverseMatrix = &this->inverseMatrix;
	//this->opMatrixPointer = operateMatrix.getMatrixPointer();
	//this->invMatrixPointer = inverseMatrix.getMatrixPointer();

	this->operateMatrix.copyMatrixElementNoCheck(input_opMatrix);
	this->inverseMatrix.resetMatrixToI();

	/*
	for(int i=0; i<rowNumber; i++)
	{
		for(int j=0; j<columnNumber; j++)
		{
			//初始化操作矩阵
			this->operateMatrix.setMatrixElement(i,j, input_opMatrix->getMatrixElement(i,j));

			//将逆矩阵初始化为单位矩阵
			if(i==j)
			{
				this->inverseMatrix.setMatrixElement(i,j,1);
			}
			else
			{
				this->inverseMatrix.setMatrixElement(i,j,0);
			}
		}
	}
	*/

};
/*
 * 重新装填操作矩阵，初始化各项参数
 * 避免重新申请对象
 */
void DynamicMatrixInverser::reload(BasicMatrix* input_opMatrix)
{



	//当新操作矩阵与原操作矩阵的行列数一致，只需要更新操作矩阵和逆矩阵的所有元素即可
	if(this->rowNumber == input_opMatrix->rowNum && this->columnNumber == input_opMatrix->columnNum)
	{
		this->operateMatrix.copyMatrixElementNoCheck(input_opMatrix);
		this->inverseMatrix.resetMatrixToI();
		/*
		for(int i=0; i<rowNumber; i++)
		{
			for(int j=0; j<columnNumber; j++)
			{
				//初始化操作矩阵
				this->operateMatrix.setMatrixElement(i,j, input_opMatrix->getMatrixElement(i,j));

				//将逆矩阵初始化为单位矩阵
				if(i==j)
				{
					this->inverseMatrix.setMatrixElement(i,j,1);
				}
				else
				{
					this->inverseMatrix.setMatrixElement(i,j,0);
				}
			}
		}
		*/
	}
	else
	{
		this->init(input_opMatrix);
	}

};

