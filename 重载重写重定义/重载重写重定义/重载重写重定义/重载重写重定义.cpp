// 重载重写重定义.cpp: 定义控制台应用程序的入口点。

//重写PK重载
/*
////////函数重载：
必须在同一个类中进行
子类无法重载父类的函数，父类同名函数将被名称覆盖
重载是在编辑期间根据参数类型和个数决定函数调用的

////////函数重写：
必须发生于父类与子类之间
并且父类与子类中的函数必须有完全相同的原型
使用virtual声明之后能够产生多态（如果不使用virtual，那叫重定义）
多态是在运行期间根据具体对象的类型决定函数调用
*/

///备注：
///该demo中如果子类没有func()函数，则不会出现类似报错

#include "stdafx.h"
#include "iostream"

using namespace std;

class Parent
{
public :
	void func()
	{
		cout << "Parent的func()" << endl;
	}

	void func(int i)
	{
		cout << "Parent的func(int i)" << endl;
	}
	void func(int i, int j)
	{
		cout << "Parent的func(int i,int j)" << endl;
	}
	void func(int i, int j, int k, int z)
	{
		cout << "Parent的func(int i,int j,int k,int z)" << endl;
	}
};


class Child: public Parent
{
public:
	
	/*void func(int i, int j)
	{
		cout << "Parent的func(int i,int j)" << endl;
	}
	void func(int i,int j,int k)
	{
		cout << "Parent的func(int i,int j,int k)" << endl;
	}*/
};


int main()
{
	Child myC;


	//1、 C++编译器看到func名字，因子类中func名字已经存在了（名称覆盖）,所以C++编译器不会去找父类的4个参数的func函数
	//2、 C++编译器只会在子类中，查找func函数，找到了func,一个是2个参数的，一个是3个参数的
	//3、 C++编译器开始报错……error C2661: “Child::func”: 没有重载函数接受 4 个参数
	//4、 若想调用父类的func,只能加上父类的域名，这样去调用……
	//myC.func(1, 2, 3, 4);

	myC.Parent::func(1,2,3,4);

	//myC.func();
	//1>重载重写重定义.cpp(46): error C2661: “Child::func”: 没有重载函数接受 0 个参数
	//1>已完成生成项目“重载重写重定义.vcxproj”的操作 - 失败。
	//func函数的名字，在子类中发生了名称覆盖；子类的函数的名字，占用了父类的函数的名字的位置
	//因为子类中已经有了func名字的重载形式
	//编译器开始在子类中func函数，但是没有0个参数的func函数
	//myC.Parent::func();




	system("pause");
    return 0;
}

