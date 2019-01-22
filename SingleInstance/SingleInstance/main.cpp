#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"


////单例模式--懒汉式
/// 缺点：每次创建创建对象时都需要判断m_single是否为NULL，于无形之中会降低性能
/// 多线程时会遇到问题，一般都会使用线程同步处理
//class Sigleton
//{
//private:
//    Sigleton()
//    {
//        cout << QStringLiteral("调用构造函数");
//        QThread::sleep(1);
//        cout << QStringLiteral("调用构造函数");
//    }

//public :
//       static Sigleton *getInstance()
//        {
//            if(m_single == NULL)
//            {
//                m_single = new Sigleton;
//            }
//            return m_single;
//        }

//        static void releaseInstance()
//        {
//            if(m_single != NULL)
//            {
//               delete m_single ;
//               m_single = NULL;
//            }
//        }

//private:
//   static  Sigleton *m_single;
//};


//Sigleton * Sigleton::m_single = NULL;

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    Sigleton *p1 = Sigleton::getInstance();
//    Sigleton *p2 = Sigleton::getInstance() ;

//    Sigleton::releaseInstance();


//    if(p1 == p2)
//    {
//        cout << QStringLiteral("是同一个对象");
//    }
//    else
//    {
//        cout << QStringLiteral("不是同一个对象");
//    }


//    return a.exec();
//}




//单例模式--饿汉式
// 缺点：无论用户是否使用该实例，对象一定会创建出来，浪费内存

///            打印内容为：调用构造函数
///            sss
///           是同一个对象
///
// 多线程时不存在线程出现竞争的问题，因为
// 饿汉式特点：先创建实例，再执行打印语句
class Sigleton
{
private:
    Sigleton()
    {
        cout << QStringLiteral("调用构造函数");
    }

public :
       static Sigleton *getInstance()
        {
//            if(m_single == NULL)
//            {
//                m_single = new Sigleton;
//            }
            return m_single;
        }

        static void releaseInstance()
        {
            if(m_single != NULL)
            {
               delete m_single ;
               m_single = NULL;
               cout << QStringLiteral("释放");
            }
        }

private:
   static  Sigleton *m_single;
};


//Sigleton * Sigleton::m_single = NULL;
Sigleton * Sigleton::m_single =  new Sigleton;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "sss";
    Sigleton *p1 = Sigleton::getInstance();
    Sigleton *p2 = Sigleton::getInstance() ;

    if(p1 == p2)
    {
        cout << QStringLiteral("是同一个对象");
    }
    else
    {
        cout << QStringLiteral("不是同一个对象");
    }

    Sigleton::releaseInstance();


    return a.exec();
}
