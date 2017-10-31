/*
 * StaticMatrixGroup.cpp
 *
 *  Created on: 2017年4月5日
 *      Author: looke
 */

#include <static/StaticMatrixUnit.h>
#include <cstdlib>
using namespace std;

StaticMatrixUnit::StaticMatrixUnit()
{
	rowNum = -1;
	columnNum = -1;
/*
	opMatrix_1511 = Static1511Matrix();
	opMatrix_1510 = Static1510Matrix();
	opMatrix_1015 = Static1015Matrix();
	opMatrix_1515 = Static1515Matrix();
	opMatrix_1010 = Static1010Matrix();
	opMatrix_1111 = Static1111Matrix();
	opMatrix_1115 = Static1115Matrix();
	opMatrix_44 = Static44Matrix();
	opMatrix_33 = Static33Matrix();
	opMatrix_32 = Static32Matrix();
	opMatrix_23 = Static23Matrix();
	opMatrix_22 = Static22Matrix();
*/
	p_currentMatrix = NULL;
};

void StaticMatrixUnit::init(int row, int column)
{
	rowNum = row;
	columnNum = column;
	setMatrixPointer(rowNum, columnNum);
};

/*
void StaticMatrixGroup::reload(int row, int column)
{
	if(rowNum == row && columnNum == column)
	{
		return;
	}
	else
	{
		init(row, column);
	}
};
*/

BasicMatrix* StaticMatrixUnit::getCurrentMatrixPointer()
{
	return this->p_currentMatrix;
};

/*
 * 根据行列数设置矩阵指针
 */
void StaticMatrixUnit::setMatrixPointer(int row, int column)
{
	/*
	switch(row)//行数
	{
		case 15://行数
		{
			if(column==15)//列数
			{
				this->p_currentMatrix = &opMatrix_1515;
			}
			if(column==11)
			{
				this->p_currentMatrix = &opMatrix_1511;
			}
			if(column==10)
			{
				this->p_currentMatrix = &opMatrix_1510;
			}
			break;
		}
		case 11://行数
		{
			if(column==11)
			{
				this->p_currentMatrix = &opMatrix_1111;
			}
			if(column==15)
			{
				this->p_currentMatrix = &opMatrix_1115;
			}
			break;
		}
		case 10://行数
		{
			if(column==15)
			{
				this->p_currentMatrix = &opMatrix_1015;
			}
			if(column==10)
			{
				this->p_currentMatrix = &opMatrix_1010;
			}
			break;
		}
		case 4://行数
		{
			if(column==4)
			{
				this->p_currentMatrix = &opMatrix_44;
			}
			break;
		}
		case 3://行数
		{
			if(column==3)
			{
				this->p_currentMatrix = &opMatrix_33;
			}
			if(column==2)
			{
				this->p_currentMatrix = &opMatrix_32;
			}
			break;
		}
		case 2://行数
		{
			if(column==3)
			{
				this->p_currentMatrix = &opMatrix_23;
			}
			if(column==2)
			{
				this->p_currentMatrix = &opMatrix_22;
			}
			break;
		}
		default:
			break;
	}
	*/
};
