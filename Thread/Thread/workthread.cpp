#include "workthread.h"
#include <QDebug>

WorkThread::WorkThread()
{

}

void WorkThread::run()
{
    while(true)
    {
        for(int n = 0; n <10; n++)
        {
            qDebug() << n << n << n << n << n << n;
//            printf("%d,%d,%d",n,n,n);//控制台阻塞，程序卡死
        }
    }
}
