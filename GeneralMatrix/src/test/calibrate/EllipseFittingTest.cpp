/*
 * EllipseFittingTest.cpp
 *
 *  Created on: 2017年4月12日
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
	infile.open("original_mag_data2.txt");   //将文件流对象与文件连接起来
	//assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

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

	infile.close();             //关闭文件输入流

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
