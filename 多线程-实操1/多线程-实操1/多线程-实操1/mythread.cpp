#include "mythread.h"
#include <QDebug>

MyThread::MyThread()
{
}

MyThread::~MyThread()
{
}

void MyThread::run()
{
	qDebug() << "name:" << this->objectName() << QStringLiteral("���߳�ID��") << currentThread()->currentThreadId();
}


