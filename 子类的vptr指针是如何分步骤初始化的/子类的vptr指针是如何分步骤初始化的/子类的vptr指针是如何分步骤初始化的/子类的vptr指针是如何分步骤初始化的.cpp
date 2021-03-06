// 子类的vptr指针是如何分步骤初始化的.cpp: 定义控制台应用程序的入口点。
//


/*构造函数中调用虚函数无法实现多态*/

#include "stdafx.h"
#include "iostream"

using namespace std;

class Parent1
{
public :
	Parent1()
	{
		//cout << "Parent1111" << endl;
		//printT();
		//cout << "Parent111" << endl;
		cout << "Parent1的构造函数" << endl;
		cout << "\n";
	}
	void virtual printT()
	{
		cout << "Parent1的成员函数" << endl;
	}

};

//class Parent2
//{
//public:
//	Parent2()
//	{
//		cout << "Parent2的构造函数" << endl;
//	}
//	void virtual printT()
//	{
//		cout << "Parent2的成员函数" << endl;
//	}
//};

class Child : public Parent1/*, public Parent2*/
{
public:
	Child()
	{
		cout << "Child2222" << endl;
		printT();
		cout << "Child2222" << endl;
		cout << "Child的构造函数" << endl;
		cout << "\n";
		cout << "\n";
		cout << "\n";
	}
	void virtual printT()
	{
		cout << "Child的成员函数" << endl;
	}

};

void display(Parent1 *base)
{
	base->printT();
}

int main()
{
	Child c;
	display(&c);

	system("pause");
    return 0;
}


/*
the output is:

Parent1的构造函数

Child2222
Child的成员函数
Child2222
Child的构造函数



Child的成员函数
请按任意键继续. . .
*/


/*the output is:

Parent1的构造函数
Child的构造函数
Parent1111
Child的成员函数
Parent111

*/

