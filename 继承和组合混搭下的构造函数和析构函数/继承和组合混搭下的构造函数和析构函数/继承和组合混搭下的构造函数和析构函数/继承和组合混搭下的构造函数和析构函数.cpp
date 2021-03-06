// 继承和组合混搭下的构造函数和析构函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;



class Object
{
public:
	Object(int a, int b)
	{
		this->m_a = a;
		this->m_b = b;
		i++;
		cout << "执行Object的构造函数" << "m_a = " << this->m_a << ";"  << "m_b = " << this->m_b << ";" << "i = " << i <<  endl;
	}
	~Object()
	{
		cout << "执行Object的析构函数" << endl;
	}
private:
	int m_a, m_b;
	static int i;
};


class Parent :public Object
{
public:
	Parent(int c): Object(c,c)
	{
		this->m_c = c;
		cout << "执行Parent的构造函数" << "m_c = " << this->m_c << ";" << endl;
	}
	~Parent()
	{
		cout << "执行Parent的析构函数" << endl;
	}
private:
	int m_c;
};


class Child : public Parent
{
public :
	Child(int d): Parent(d),obj1(d,d),obj2(d,d)
	{
		this->m_d = d; 
		cout << "执行Child的构造函数" << "m_d = " << m_d << ";" << endl;
	}
	~Child()
	{
		cout << "执行Child的析构函数" << endl;
	}
private:
	int m_d;
	Object obj1;
	Object obj2;
};


void display()
{
	Child child(4);
}

int Object::i = 0;

int main()
{
	display();
	system("pause");
    return 0;
}


/*the output is:*/
/*
执行Object的构造函数m_a = 4;m_b = 4;i = 1
执行Parent的构造函数m_c = 4;
执行Object的构造函数m_a = 4;m_b = 4;i = 2
执行Object的构造函数m_a = 4;m_b = 4;i = 3
执行Child的构造函数m_d = 4;
执行Child的析构函数
执行Object的析构函数
执行Object的析构函数
执行Parent的析构函数
执行Object的析构函数
*/

