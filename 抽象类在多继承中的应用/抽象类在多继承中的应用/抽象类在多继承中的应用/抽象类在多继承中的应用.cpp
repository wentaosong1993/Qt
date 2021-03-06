// 抽象类在多继承中的应用.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;


class Interface1
{
public :
	virtual int add(int a, int b) = 0;
	virtual void printT() = 0;

};

class Interface2
{
public:
	virtual int multi(int a, int b) = 0;
	virtual void printT() = 0;

};

class Parent
{
public :
	int getA()
	{
		a = 0;
		return a;
	}
private :
	int a = 0;
};


class Child : public Interface1, public Interface2, public Parent
{
public :
	virtual int add(int a, int b)
	{
		cout << "Child::add: " << a + b << "\n";
		return a + b;
	}


	virtual int multi(int a, int b)
	{
		cout << "Child::multi: " << a*b << "\n";
		return a*b;
	}
	virtual void printT()
	{
		cout << "Chilid::printT()" << "\n";
	}
};

int main()
{
	Child c;

	Interface1 *inter1 = &c;
	inter1->add(1,2);

	Interface2 *inter2 = &c;
	inter2->multi(2,3);
	cout << "hello world " << endl;
	system("pause");
    return 0;
}


/*
the output is:
Child::add: 3
Child::multi: 6
hello world
请按任意键继续. . .
*/