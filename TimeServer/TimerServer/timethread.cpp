#include "timethread.h"
#include <QDateTime>
#include <QByteArray>
#include <QDataStream>


TimeThread::TimeThread(int socketDescriptor, QObject *parent)
    :QThread(parent),socketDescriptor(socketDescriptor)
{

}

void TimeThread::run()
{
    QTcpSocket tcpSocket; //创建通信套接字
    if(!tcpSocket.setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket.error());
        return;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    uint time2u = QDateTime::currentDateTime().toTime_t();
    out << time2u;
    tcpSocket.write(block); //发送当前服务器端时间
    tcpSocket.disconnectFromHost(); //准备关闭当前通信套接字
    tcpSocket.waitForDisconnected(); //等待关闭
}
