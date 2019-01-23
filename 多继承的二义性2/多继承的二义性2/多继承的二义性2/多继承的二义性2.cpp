// 多继承的二义性2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"


class B1
{
public :
	int b;

};

class B2
{
public:
	int b;
};


class B:  virtual public B1, virtual public B2
{
public :
	int b1;
};


void display()
{
	B b;
	//b.b = 100;
	
}

int main()
{

	system("pause");
    return 0;
}

/*这种模型下，即使加了virtual关键字也无法解决二义性的问题
1>f:\githubrepository\qt\多继承的二义性2\多继承的二义性2\多继承的二义性2\多继承的二义性2.cpp(32): error C2385: 对“b”的访问不明确
1>f:\githubrepository\qt\多继承的二义性2\多继承的二义性2\多继承的二义性2\多继承的二义性2.cpp(32): note: 可能是“b”(位于基“B1”中)
1>f:\githubrepository\qt\多继承的二义性2\多继承的二义性2\多继承的二义性2\多继承的二义性2.cpp(32): note: 也可能是“b”(位于基“B2”中)
*/