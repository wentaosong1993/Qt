#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QThread
{
public:
    MyThread(QObject *parent = Q_NULLPTR);

   virtual void run();
};

#endif // MYTHREAD_H
