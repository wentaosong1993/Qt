#include <QCoreApplication>
#include <QDebug>



class A
{
public :
    A(){qDebug() << "constructor";}
    ~A()
    {
        qDebug() << "destructor";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    A *b = new A;
    delete b; //delete调用析构函数，释放对象占用的内存；
    b = nullptr;
    return a.exec();
}
