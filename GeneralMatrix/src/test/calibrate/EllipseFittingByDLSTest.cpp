/*
 * EllipseFittingByDLSTest.cpp
 *
 *  Created on: 2017��4��29��
 *      Author: looke
 */

#include "EllipseFittingByDLSTest.h"
#include <iostream>
#include <fstream>
using namespace std;


EllipseFittingByDLSTest::EllipseFittingByDLSTest()
{};

void EllipseFittingByDLSTest::test()
{
	ifstream infile;
	infile.open("original_mag_data2.txt");   //���ļ����������ļ���������
	//assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������

	if(!infile)
	{
	  cout << "Unable to open file";
	  return;
	}
	double magOriginalData[8000][3];

	double a,b,c;

	int i=0;

	while(!infile.eof() && i<=8000)
	{
	    char buffer[256];
		infile.getline(buffer,256);
		sscanf(buffer,"%lf %lf %lf",&a,&b,&c);
		//cout <<"---" << i << "---a:"<<a<<" b:"<<b<<" c:"<<c<<endl;
		magOriginalData[i][0] = a;
		magOriginalData[i][1] = b;
		magOriginalData[i][2] = c;
		i++;
	}

	infile.close();             //�ر��ļ�������

	EllipseFittingByDLS ellipseFitterDLS = EllipseFittingByDLS(magOriginalData);
	ellipseFitterDLS.generateMatrix_C();
	ellipseFitterDLS.generateMatrix_D();
	cout << "-------------------Matrix D----------------" << endl;
	ellipseFitterDLS.getMatrix_C()->printMatrix();
	cout << "-------------------Matrix D----------------" << endl;
	ellipseFitterDLS.getMatrix_D()->printMatrix();
};


