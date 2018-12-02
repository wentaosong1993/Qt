﻿#include "server.h"
#include <QHostAddress>

Server::Server(QObject *parent,int port): QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void Server::updateClients(QString msg, int length)
{
    emit updateServer(msg,length);
    for(int i = 0; i < tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length) != length)
        {
            continue;
        }
    }
}

void Server::slotDisconected(int descriptor)
{
    for(int i =0; i < tcpClientSocketList.count(); i++)
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

void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);

    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));

    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpClientSocketList.append(tcpClientSocket);
}