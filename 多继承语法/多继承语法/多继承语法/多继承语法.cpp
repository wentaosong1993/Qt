// 多继承语法.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;


class Base1
{
public:

	Base1(int b1)
	{
		this->b1 = b1;
		cout << "执行Base1的构造函数" << "b1:" << b1 << endl;
	}

	~Base1()
	{
		cout << "执行Base1的析构函数" << endl;
	}

private:
	int b1;
};

class Base2
{
public:

	Base2(int b2)
	{
		this->b2 = b2;
		cout << "执行Base1的构造函数" << "b2:" << b2 << endl;
	}
	~Base2()
	{
		cout << "执行Base2的析构函数" << endl;
	}

private:
	int b2;
};


class Child: public Base1,public Base2
{
public:

	Child(int b1,int b2,int c): Base1(b1),Base2(b2)
	{
		this->a = b1;
		this->b = b2;
		this->c = c;
		cout << "执行Child的构造函数" << "c:" << c << endl;
	}

	~Child()
	{
		cout << "执行Child的析构函数" << endl;
	}

private:
	int a, b, c;
};


void display()
{
	Child a(1, 2, 3);
}
int main()
{
	display();
	system("pause");
    return 0;
}


/*the output is:*/
/*
执行Base1的构造函数b1:1
执行Base1的构造函数b2:2
执行Child的构造函数c:3
执行Child的析构函数
执行Base2的析构函数
执行Base1的析构函数
*/

