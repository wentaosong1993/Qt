// 继承的静态关键字.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

using namespace std;

class Parent
{
	/*容易忽略的低级错误*/
	/*
	error: 1>------ 已启动生成: 项目: 继承的静态关键字, 配置: Debug Win32 ------
		   1>继承的静态关键字.cpp
		   1>f:\githubrepository\qt\继承的静态关键字\继承的静态关键字\继承的静态关键字\继承的静态关键字.cpp(38): error C2280: “Child::Child(void)”: 尝试引用已删除的函数
		   1>f:\githubrepository\qt\继承的静态关键字\继承的静态关键字\继承的静态关键字\继承的静态关键字.cpp(34): note: 编译器已在此处生成“Child::Child”
		   1>f:\githubrepository\qt\继承的静态关键字\继承的静态关键字\继承的静态关键字\继承的静态关键字.cpp(34): note: “Child::Child(void)”: 因为 基类 调用已删除或不可访问的函数“Parent::Parent(void)”，所以已隐式删除函数
		   1>已完成生成项目“继承的静态关键字.vcxproj”的操作 - 失败。
		   ========== 生成: 成功 0 个，失败 1 个，最新 0 个，跳过 0 个 ==========
	*/
	//Parent()  ///设计模式--单例模式时构造函数才要求需要默认private类型
	//{
	//	cout << "执行Parent的构造函数";
	//}
public:
	Parent()
	{
		cout << "执行Parent的构造函数";
	}
public:
	static int a;
	int b;
public :
	void printT()
	{
		cout << "执行Parent的成员函数" << "a = " << a << endl;
	}
};

int Parent::a = 0;//告诉C++编译器给我分配内存,我再继承Parent类中用到的那个a，不然一定会在运行的时候报错。

class Child: private Parent
{
public :
	Child()
	{
		cout << "执行Child 的构造函数" << endl;
	}
	void printChild()
	{
		cout << "执行Child的成员函数" << "a = " << a << endl;
	}
};

int main()
{
	Child b;
	b.printChild();
	system("pause");
    return 0;
}

