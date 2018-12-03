#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QThread>
#include <QTcpSocket>

class TimeThread : public QThread
{
public:
    TimeThread(int socketDescriptor,QObject *parent = Q_NULLPTR);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
};

#endif // TIMETHREAD_H
