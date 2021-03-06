
// 多继承的二义性.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

class B
{
public:
	B(int b)
	{
		cout << "执行B的构造函数" <<  "b:" << b << endl;
	}
	~B()
	{
		cout << "执行B的析构函数" << endl;
	}
public:
	int b;
};


class B1:  virtual public B
{
public:
	B1(int b1): B(b1)
	{
		cout << "执行B1的构造函数" << "b1:" << b1 << endl;
	}
	~B1()
	{
		cout << "执行B1的析构函数" << endl;
	}
public:
	int b1;
};


class B2 :   public B
{
public:
	B2(int b2) : B(b2)
	{
		cout << "执行B2的构造函数" << "b2:" << b2 << endl;
	}
	~B2()
	{
		cout << "执行B2的析构函数" << endl;
	}

public:
	int b2;
};


class C :  public B1, public B2
{
public:
	//C(int c1,int c2,int c3) : B1(c1),B2(c2),B(c3)
	//{
	//	this->c1 = c1;
	//	this->c2 = c2;
	//	this->c3 = c3;
	//	cout << "执行C的构造函数" << "c1:" << this->c1 << endl;
	//}
	//~C()
	//{
	//	cout << "执行C的析构函数" << endl;
	//}
public:
	int c1, c2, c3;
};


void display()
{
	cout << "B类的大小：" << sizeof(B) << endl;
	cout << "B1类的大小：" << sizeof(B1) << endl;
	cout << "B2类的大小：" << sizeof(B2) << endl;
}


int main()
{
	display();
	system("pause");
    return 0;
}


/*
B类的大小：4
B1类的大小：12
B2类的大小：8
*/








