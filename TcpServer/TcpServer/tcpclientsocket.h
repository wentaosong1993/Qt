#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>
#include <QObject>

class TcpClientSocket : public QTcpSocket
{
public:
    TcpClientSocket(QObject *parent = 0);

signals:
    void updateClients(QString,int);
    void disconnected(int);

protected slots:
    void dataReceived();
    void slotDisconnnected();
};

#endif // TCPCLIENTSOCKET_H
