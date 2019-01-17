#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *parent = Q_NULLPTR);

   virtual void run();
signals:
    void isDone();
};

#endif // MYTHREAD_H
