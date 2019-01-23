
// 多继承的二义性.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

class B
{
public:
	//B(int b)
	//{
	//	cout << "执行B的构造函数" <<  "b:" << b << endl;
	//}
	//~B()
	//{
	//	cout << "执行B的析构函数" << endl;
	//}
public:
	int b;
};


class B1:  virtual public B
{
public:
	//B1(int b1): B(b1)
	//{
	//	cout << "执行B1的构造函数" << "b1:" << b1 << endl;
	//}
	//~B1()
	//{
	//	cout << "执行B1的析构函数" << endl;
	//}
public:
	int b1;
};


class B2 : virtual public B
{
public:
	//B2(int b2) : B(b2)
	//{
	//	cout << "执行B2的构造函数" << "b2:" << b2 << endl;
	//}
	//~B2()
	//{
	//	cout << "执行B2的析构函数" << endl;
	//}

public:
	int b2;
};


class C :  public B1, public B2
{
public:
	//C(int c1,int c2,int c3) : B1(c1),B2(c2)
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
	C c;
	c.b1 = 100;
	c.b2 = 200;
	c.c1 = 300;

	c.b = 400;

	/*
	the error is :
				 1>多继承的二义性.cpp
				 1>f:\githubrepository\qt\多继承的二义性\多继承的二义性\多继承的二义性\多继承的二义性.cpp(81): error C2385: 对“b”的访问不明确
				 1>f:\githubrepository\qt\多继承的二义性\多继承的二义性\多继承的二义性\多继承的二义性.cpp(81): note: 可能是“b”(位于基“B”中)
				 1>f:\githubrepository\qt\多继承的二义性\多继承的二义性\多继承的二义性\多继承的二义性.cpp(81): note: 也可能是“b”(位于基“B”中)
	*/
}


int main()
{
	display();
	system("pause");
    return 0;
}


/*the output is:*/
/*
执行B的构造函数b:1
执行B1的构造函数b1:1
执行B的构造函数b:2
执行B2的构造函数b2:2
执行C的构造函数c1:1

执行C的析构函数
执行B2的析构函数
执行B的析构函数
执行B1的析构函数
执行B的析构函数
*/

