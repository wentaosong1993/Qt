#include <QCoreApplication>

class A
{
    public:
    int a;
};
class B1 : public A
{
    private:
    int b1;
};
class B2 : public A
{
private:
    int b2;
};
class C : public B1, public B2
{
public:
    int f();
private:
    int c;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    C c1;
//    c1.a; //B1、B2中通过继承过来，已经有一个私有成员变量a,该访问在B1\B2\C中无法判别；error
    c1.A::a;
    c1.B1::a; //直接访问B1从A中继承过来的a,即直接访问到了B1中的a;
    c1.B2::a; //同上
    return 0;
}
