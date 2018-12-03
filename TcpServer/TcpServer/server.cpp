#include "server.h"
#include <QHostAddress>

Server::Server(QObject *parent,int port): QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void Server::updateClients(QString msg, int length)
{
    emit updateServer(msg,length);
    for(int i = 0; i < tcpClientSocketList.count();i++) ///个客户端
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length) != length) //服务器发送数据
        {
            continue;
        }
    }
}

void Server::slotDisconected(int descriptor)
{
    for(int i =0; i < tcpClientSocketList.count(); i++) ///服务器取消连接
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}

void Server::incomingConnection(int socketDescriptor) //有新的连接时，触发该槽函数
{
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this); //创建通信套接字

    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));

    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpClientSocketList.append(tcpClientSocket);
}
