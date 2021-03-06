// 函数指针做函数参数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"


using namespace std;

//函数的实现者
int add(int a, int b)
{
	cout << "add…" << endl;
	return a + b;
}

int add2(int a, int b)
{
	cout << "add2…" << endl;
	return a + b;
}

int add3(int a, int b)
{
	cout << "add3…" << endl;
	return a + b;
}

int add4(int a, int b)
{
	cout << "add4…" << endl;
	return a + b;
}



//定义函数指针类型
typedef int (*MyFuncType)(int a, int b);

//函数指针做函数参数
int MainOp(MyFuncType myFuncAdd)
{
	return myFuncAdd(2,4);
}

//同样的函数指针做函数参数
int MainOp2(int(*MyPointerFuncAdd)(int a, int b))
{
	return MyPointerFuncAdd(3, 4);
}


//实现了 任务的调用 和任务的实现分开 
//实现了程序的解耦合，讲任务的实现者和任务的调用者分开了（类比诸葛亮给刘备的精囊妙计的故事）
//函数指针做函数参数---效果：回调函数
//函数指针类型的本质作用： 提前做了一个协议的约定，把函数的参数、函数的返回值提前约定
//回调函数的本质：同上
//回调函数的思想： 任务的调用和任务实现解耦。
int main()
{
/*
	cout << add(1, 2) << endl; //直接调用


    //MyFuncType函数的调用者
	MyFuncType myFuncAdd = NULL;
	myFuncAdd = add; 

	//间接调用
	cout << myFuncAdd(1,3) << endl; 
	 
	cout << MainOp2(add) << endl;

	cout << MainOp(add) << endl;
*/
	//在MainOp函数框架没有发生任何改变的情况下，可以把后来写的代码调用起来
	cout << MainOp(add2) << endl; //传入函数的入口地址
	cout << MainOp(add3) << endl;
	cout << MainOp(add4) << endl;


	system("pause");
    return 0;
}

