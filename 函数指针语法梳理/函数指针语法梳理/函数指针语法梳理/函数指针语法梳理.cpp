// 函数指针语法梳理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;


int add(int a,int b )
{
	cout << "func add ...." << endl; 
	return a + b;
}
int main()
{
	cout << add(1, 2) << endl;

	//定义一个函数类型
	{
		typedef int (MyFuncType)(int a, int b); 

		MyFuncType  *myPointerFunc = NULL;//定义一个指针，指向某一种类的函数

		myPointerFunc = &add;
		cout << myPointerFunc(3, 4) << endl; //间接调用

		myPointerFunc = add; //C 是逐渐完善起来的，因为兼容历史版本的原因，这样子写也可以编译通过
		cout << myPointerFunc(5, 6) << endl; //间接调用  
	}

	//定义一个函数指针类型
	{
		typedef int(*MyPointerFuncType)(int a, int b);
		MyPointerFuncType myPointerFunc; //定义一个指针
		myPointerFunc = add;
		cout << myPointerFunc(7, 8) << endl;

	}


	//直接定义函数指针
	{
		int(*MyPointerFunc)(int a, int b);
		MyPointerFunc = add;
		cout << MyPointerFunc(9, 10) << endl;
		 
	}
	cout << "Hello" << endl;
	system("pause");
    return 0;
}

