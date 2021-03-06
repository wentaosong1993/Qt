// 虚析构函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

class B
{
public:
	B()
	{
		m_b = new char[10];
		strcpy(m_b,"objB");
		cout << "B的构造函数" << endl;
	}
	virtual ~B()
	{
		delete[] m_b;
		cout << "B的析构函数" << endl;
	}
private:
	char *m_b;
};

class B1: public B
{
public:
	B1()
	{
		m_b1 = new char[10];
		strcpy(m_b1, "objB1");
		cout << "B1的构造函数" << endl;
	}
	/*virtual*/ ~B1()
	{
		delete[] m_b1;
		cout << "B1的析构函数" << endl;
	}
private:
	char *m_b1;
};


class C : public B1
{
public:
	C()
	{
		m_c = new char[10];
		strcpy(m_c, "objC");
		cout << "C的构造函数" << endl;
	}
	~C()
	{
		delete[] m_c;
		cout << "C的析构函数" << endl;
	}
private:
	char *m_c;
};

//只执行了父类的析构函数

//多态的意义;
//通过父类指针把所有的子类对象的析构函数都执行一遍
//通过父类指针释放所有的子类资源

void display(B *base)
{
	delete base; //这句话不会表现成多态这个属性
}

int main()
{
	C *c = new C;
	display(c);
	//delete c;//直接通过自类对象释放资源，不需要添加virtual关键字
	system("pause");

    return 0;
}



/* 
给基类的析构函数加virtual关键字、打开display()方法的输出信息:
	B的构造函数
	B1的构造函数
	C的构造函数
	C的析构函数
	B1的析构函数
	B的析构函数
	请按任意键继续. . .
*/


/*  正常的构造和析构
屏蔽掉基类的析构函数的virtual关键字、屏蔽display()方法的输出信息:
	B的构造函数
	B1的构造函数
	C的构造函数
	C的析构函数
	B1的析构函数
	B的析构函数
	请按任意键继续. . .
*/


