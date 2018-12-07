/*
constructing B2  2

constructing B1  1

constructing B3

constructing B1  3

constructing B2  4

constructing B3

child contructor C
child destructor C

destructing B3

destructing B2

destructing B1

destructing B3

destructing B1

destructing B2
*/


#include <QCoreApplication>
#include <QDebug>

// 基类 B1
class B1
{
public:
    B1(int i)
    {
        qDebug()  << "constructing B1 "<<i<<endl;
    }
    ~B1()
    {
        qDebug() << "destructing B1"<<endl;
    }
};

//基类 B2
class B2
{
public:
    B2(int j)
    {
        qDebug() << "constructing B2 "<<j<<endl;
    }
     ~B2()
    {
        qDebug() << "destructing B2"<<endl;
    }
};

//基类 B3
class B3
{
public:
    B3()
    {
        qDebug() << "constructing B3"<<endl;
    }
    ~B3()
    {
        qDebug() << "destructing B3"<<endl;
    }
};

//派生类 C， 继承B2, B1，B3（声明顺序从左至右。 B2->B1->B3）
class C: public B2, public B1, public B3
{
public:
    C(int a, int b, int c, int d):B1(a), memberB2(d), memberB1(c),B2(b)
    {
        //B1，B2的构造函数有参数，B3的构造函数无参数
        //memberB2(d), memberB1(c)是派生类对自己的数据成员进行初始化的过程、
        //构造函数执行顺序， 基类（声明顺序）-> 内嵌成员对象的构造函数（声明顺序） -> 派生类构造函数中的内容

        qDebug() << "child contructor C";

    }
    ~C() {qDebug() << "child destructor C";}
private:
    B1 memberB1;
    B2 memberB2;
    B3 memberB3;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    C obj(1,2,3,4);
    return 0;
}

