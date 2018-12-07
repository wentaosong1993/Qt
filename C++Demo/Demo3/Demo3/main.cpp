/* C++编译系统只执行最后的派生类对虚基类的构造函数的调用，
 * 而忽略虚基类的其他派生类（如类B和类C）对虚基类的构造函数的调用，
 * 这就保证了虚基类的数据成员不会被多次初始化。
a= 1

b= 2

c= 3

d= 4
*/

#include <QCoreApplication>
#include <QDebug>
class A{
protected:
    int a;
public:
    A(int a):a(a){}
};

class B: virtual public A{  //声明虚基类
protected:
    int b;
public:
    B(int a, int b):A(a),b(b){}
};

class C: virtual public A{  //声明虚基类
protected:
    int c;
public:
    C(int a, int c):A(a),c(c){}
};

class D: virtual public B, virtual public C{  //声明虚基类
private:
    int d;
public:
    D(int a, int b, int c, int d):A(a),B(a,b),C(a,c),d(d){}
    void display();
};
void D::display(){
    qDebug() << "a=" << a << endl;
    qDebug() << "b=" << b << endl;
    qDebug() << "c=" << c << endl;
    qDebug() << "d=" << d << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    (new D(1, 2, 3, 4)) -> display();
    return a.exec();
}
