// size.cpp: 定义控制台应用程序的入口点。
//





#include "stdafx.h"
#include "iostream"

using namespace std;


class Parent
{
public :
	Parent(int a = 0)
	{
		this->a = a;
		cout << "Parent constructor" << endl;
	}

	void  virtual printT()
	{
		cout << "Parent printT" << endl;
	}

private :
	int a;
};


class Child: public Parent
{
public:
	Child(int a = 0,int b = 0): Parent(a)
	{
		this->b = b;
		cout << "Child constructor" << endl;
	}

	void  virtual printT()
	{
		cout << "Child printT" << endl;
	}
private:
	int b;
};


int main()
{
	Child array[] = { Child(1),Child(2),Child(3) };

	Parent *pP = NULL;
	Child *pC = NULL;

	pP = array;
	pC = array;

	pP->printT();//有多态发生
	pC->printT();


	cout << "Parent:" <<  sizeof(Parent) << endl;
	cout << "Chilid:" <<  sizeof(Child) << endl;

	pP++;
	pC++;

	pP->printT();//有多态发生 //引发了异常: 读取访问权限冲突。
				 //pP->是 nullptr。

			    //子类和父类的指针步长不一样的问题
				//多态是用父类指针指向子类对象和父类步长++，是两个不同的概念。
	pC->printT();


	system("pause");
    return 0;
}
/*屏蔽子类中的私有成员变量时：
Parent constructor
Child constructor
Parent constructor
Child constructor
Parent constructor
Child constructor
Child printT
Child printT
Parent:8
Chilid:8
Child printT
Child printT


打开子类中的私有成员变量时：error
Parent constructor
Child constructor
Parent constructor
Child constructor
Parent constructor
Child constructor
Child printT
Child printT
Parent:8
Chilid:12
*/
