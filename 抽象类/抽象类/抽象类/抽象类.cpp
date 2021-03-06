// 抽象类.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

//抽象类
class Figure
{
public:
	virtual void getArea() = 0;//纯虚函数
private:
	int a;
};


class Circle : public Figure
{
public :
	virtual void getArea()
	{
		cout << "Circle的面积为:" << 3.14 * a1* a1 << endl;
	}
	Circle(int a, int b)
	{
		this->a1 = a;
		this->b1 = b;
	}
private:
	int a1;
	int b1;
};

class Tri : public Figure
{
public:
	Tri(int a, int b)
	{
		this->a2 = a;
		this->b2 = b;
	}

	virtual void getArea()
	{
		cout << "Tri的面积为:" << a2 * b2 / 2 << endl;
	}

private:
	int a2;
	int b2;
};


class Square : public Figure
{
public:
	Square(int a, int b)
	{
		this->a3 = a;
		this->b3 = b;
	}

	virtual void getArea()
	{
		cout << "Square的面积为:" << a3 * b3 << endl;
	}

private:
	int a3;
	int b3;
};



void display(Figure *base)
{
	base->getArea();
}


int main()
{
	Figure *base = NULL;

	Circle c(10, 10);
	display(&c);

	Tri t(10, 10);
	display(&t);

	Square s(10, 10);
	display(&s);

	cout << "Hello" << endl;
	system("pause");
    return 0;
}

