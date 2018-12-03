#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QObject>
#include "tcpclientsocket.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = Q_NULLPTR,int port = 0);
    QList<TcpClientSocket *> tcpClientSocketList;

signals:
    void updateServer(QString,int );

public slots:
    void updateClients(QString msg, int length);
    void slotDisconected(int descriptor);
protected:
    void incomingConnection(int socketDescriptor);

};

#endif // SERVER_H
