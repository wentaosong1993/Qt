#include "mythread.h"

MyThread::MyThread(QObject *parent)
    :QThread(parent)
{

}

void MyThread::run()
{
    //复杂耗时程序
    sleep(5);
}
