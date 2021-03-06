// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;


//class Parent
//{
//public:
//	Parent()
//	{
//		cout << "我是爹。" << endl;
//	}
//	Parent(const Parent &a) { cout << "爹的拷贝构造函数" << endl; }
//};
//
//
//class Child :public Parent
//{
//public :
//	Child()
//	{
//		cout << "我是儿子。" << endl;
//	}
//};
//
//int main()
//{
//	Child a;
//	Parent b = a;
//	system("pause");
//    return 0;
//}

/*the output*/
/*
我是爹。
我是儿子。
爹的拷贝构造函数
*/


///1、自类对象在创建时会首先调用父类的构造函数
///2、父类的构造函数执行结束后，执行自类的构造函数
///3、当父类的构造函数有参数时，需要在自类的初始化列表中显示调用
///4、析构函数的调用顺序与构造函数的调用顺序相反。

class Parent
{
public:
	Parent(int a,int b)
	{
		this->a = a;
		this->b = b;
		cout << "父类的构造函数" << endl;
	}
	Parent(const Parent &a) { cout << "爹的拷贝构造函数" << endl; }

	~Parent() { cout << "父类的析构函数" << endl; }
private:
	int a, b;
};


class Child :public Parent
{
public:
	Child(int c):Parent(c,c)
	{
		this->c = c;
		cout << "子类的构造函数" << endl;
	}
	~Child() { cout << "子类的析构函数" << endl; }
private:
	int c;
};

void printT()
{
	Child(2);
}

int main()
{
	//Parent a(1,2);
	printT();
	system("pause");
	return 0;
}



/*the output is:*/
/*
父类的构造函数
子类的构造函数
子类的析构函数
父类的析构函数
*/

