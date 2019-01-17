#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class myThread : public QObject
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = 0);

    void myTimeOut();
    void setFlag(bool isStop = false);

signals:
    void timeSignal();

public slots:

private:
    bool m_flag;
};

#endif // MYTHREAD_H
