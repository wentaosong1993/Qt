#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnnected()));
}





void TcpClientSocket::dataReceived()
{

}

void TcpClientSocket::slotDisconnnected()
{

}
