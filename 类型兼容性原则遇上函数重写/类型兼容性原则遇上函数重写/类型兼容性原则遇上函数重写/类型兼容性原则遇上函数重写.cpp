// 类型兼容性原则遇上函数重写.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

class Parent
{
public:
	Parent(int a)
	{
		this->m_a = a;
		cout << "Parent构造函数" << "m_a: " << this->m_a << endl;
	}

	void virtual printT()
	{
		cout << "Parent成员函数" << endl;
	}

private:
	int m_a;
};

class Child: public Parent
{
public:
	Child(int b): Parent(b)
	{
		this->m_b = b;
		cout << "Child构造函数" << "m_b: " << this->m_b << endl;
	}


	void printT()
	{
		cout << "Child成员函数" << endl;
	}

private:
	int m_b;
};



void printF1(Parent *base1)
{
	base1->printT(); //一种调用语句，有多种表现形态……
}


void printF2(Parent &base2)
{
	base2.printT();
}

int main()
{
	Parent* base = NULL;
	
	Parent a(20);
	Child b(30);
	base = &a;
	base->printT();

	base = &b;
	base->printT();


	{
		Parent &base = a;
		base.printT();

		Parent &base1 = b; //base1是b的别名
		base1.printT();
	}

	printF1(&a);
	printF1(&b);

	printF2(a);
	printF2(b);

	system("pause");

    return 0;
}

/*不加virtual关键字
Parent构造函数m_a: 20
Parent构造函数m_a: 30
Child构造函数m_b: 30
Parent成员函数
Parent成员函数
Parent成员函数
Parent成员函数
Parent成员函数
Parent成员函数
Parent成员函数
Parent成员函数
*/




/* 加virtual关键字
Parent构造函数m_a: 20
Parent构造函数m_a: 30
Child构造函数m_b: 30
Parent成员函数
Child成员函数
Parent成员函数
Child成员函数
Parent成员函数
Child成员函数
Parent成员函数
Child成员函数
*/