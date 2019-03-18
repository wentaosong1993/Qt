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
	qDebug() << "name:" << this->objectName() << QStringLiteral("×ÓÏß³ÌID£º") << currentThread()->currentThreadId();
}


