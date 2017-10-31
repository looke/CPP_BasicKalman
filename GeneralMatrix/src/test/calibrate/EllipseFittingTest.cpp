/*
 * EllipseFittingTest.cpp
 *
 *  Created on: 2017��4��12��
 *      Author: looke
 */


#include "EllipseFittingTest.h"
#include <iostream>
#include <fstream>
using namespace std;


EllipseFittingTest::EllipseFittingTest()
{

};

void EllipseFittingTest::test()
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

	EllipseFitting ellipseFitter = EllipseFitting(magOriginalData);
	ellipseFitter.TLS_Fitting();
	//cout << "Max Diff:" << ellipseFitter.getDiffMax() << endl;
	//ellipseFitter.calcMaxIterateDiff();
	//cout << "Max Diff:" << ellipseFitter.getDiffMax() << endl;
	//ellipseFitter.printJacobiMatrix();
	//cout << "------------------" << endl;

	//ellipseFitter.printJacobiMatrix();
	//ellipseFitter.updateJacobiMatrix(1);
	//ellipseFitter.printJacobiMatrix();


};
