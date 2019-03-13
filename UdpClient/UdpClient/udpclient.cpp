#include "udpclient.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QByteArray>

UdpClient::UdpClient(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent,f)
{
    setWindowTitle(QStringLiteral("UDP Client"));
    receiveTextEdit = new QTextEdit;
    closeBtn = new QPushButton(QStringLiteral("关闭"));
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(receiveTextEdit);
    mainLayout->addWidget(closeBtn);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(closeBtnClicked()));
    port = 5555;
    udpSocket = new QUdpSocket(this);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));//接收数据

    bool result = udpSocket->bind(port);//广播

    if(!result)
    {
        QMessageBox::information(this,QStringLiteral("error"),QStringLiteral("udp socket create error!"));
        return;
    }
}

UdpClient::~UdpClient()
{

}

void UdpClient::closeBtnClicked()
{
    close();
}

void UdpClient::dataReceived()
{
    while(udpSocket->hasPendingDatagrams()) //有数据报等待接收
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());

        QString msg = datagram.data();
        receiveTextEdit->insertPlainText(msg);
    }
}
