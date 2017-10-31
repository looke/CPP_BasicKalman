/*
 * MatrixInverser.cpp
 *
 *  Created on: 2017��2��27��
 *      Author: looke
 */

#include <dynamic/util/DynamicMatrixInverser.h>
#include <dynamic/DynamicMatrix.h>

DynamicMatrixInverser::DynamicMatrixInverser(BasicMatrix* input_opMatrix):MatrixInverser(input_opMatrix)
{
	this->init(input_opMatrix);
};

/*
 * 	��ʼ���������������
 */
void DynamicMatrixInverser::init(BasicMatrix* input_opMatrix)
{

	this->rowNumber = input_opMatrix->rowNum;
	this->columnNumber = input_opMatrix->columnNum;


	//ֻ�з����������
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
			//��ʼ����������
			this->operateMatrix.setMatrixElement(i,j, input_opMatrix->getMatrixElement(i,j));

			//��������ʼ��Ϊ��λ����
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
 * ����װ��������󣬳�ʼ���������
 * ���������������
 */
void DynamicMatrixInverser::reload(BasicMatrix* input_opMatrix)
{



	//���²���������ԭ���������������һ�£�ֻ��Ҫ���²������������������Ԫ�ؼ���
	if(this->rowNumber == input_opMatrix->rowNum && this->columnNumber == input_opMatrix->columnNum)
	{
		this->operateMatrix.copyMatrixElementNoCheck(input_opMatrix);
		this->inverseMatrix.resetMatrixToI();
		/*
		for(int i=0; i<rowNumber; i++)
		{
			for(int j=0; j<columnNumber; j++)
			{
				//��ʼ����������
				this->operateMatrix.setMatrixElement(i,j, input_opMatrix->getMatrixElement(i,j));

				//��������ʼ��Ϊ��λ����
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

