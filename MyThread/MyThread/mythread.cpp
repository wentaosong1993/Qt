#include "mythread.h"
#include <QDebug>
#include <QMessageBox>


myThread::myThread(QObject *parent) : QObject(parent)
{
    m_flag = false; //默认为false,代表线程尚未启动
}

void myThread::myTimeOut()
{
    while(m_flag == false)
    {
        QThread::sleep(1);
        if(true == m_flag)
        {
            break;
        }
        emit timeSignal();
//        QMessageBox::aboutQt(NULL);
//error: ASSERT failure in QWidget: "Widgets must be created in the GUI thread.", file kernel\qwidget.cpp, line 1150
        qDebug() << QStringLiteral("子线程号:") << QThread::currentThread();
    }
}

void myThread::setFlag(bool isStop)
{
    m_flag = isStop;
}
