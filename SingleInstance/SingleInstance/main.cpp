#include <QCoreApplication>
#include <QDebug>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"


////单例模式--懒汉式
//class Sigleton
//{
//private:
//    Sigleton()
//    {
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
