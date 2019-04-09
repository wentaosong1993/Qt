#include "tcpclient.h"
#include <QMessageBox>
#include <QHostInfo>


TcpClient::TcpClient(QWidget *parent)
    : QDialog(parent)
{
    tcpSocket = NULL;
    setWindowTitle(QStringLiteral("TCP Client"));
    contentListWidget = new QListWidget;
    sendLineEdit = new QLineEdit;
    sendBtn = new QPushButton(QStringLiteral("发送:"));
    userNameLabel = new QLabel(QStringLiteral("用户名:"));
    userNameLineEdit = new QLineEdit;
    userNameLineEdit->setText(QStringLiteral("涛哥"));
    serverIPLabel = new QLabel(QStringLiteral("服务器地址:"));
    serverIPLineEdit = new QLineEdit;
    serverIPLineEdit->setText(QStringLiteral("127.0.0.1"));
    portLabel = new QLabel(QStringLiteral("端口:"));
    portLineEdit = new QLineEdit;
    enterBtn = new QPushButton(QStringLiteral("进入聊天室"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(sendLineEdit,1,0);
    mainLayout->addWidget(sendBtn,1,1);
    mainLayout->addWidget(userNameLabel,2,0);
    mainLayout->addWidget(userNameLineEdit,2,1);
    mainLayout->addWidget(serverIPLabel,3,0);
    mainLayout->addWidget(serverIPLineEdit,3,1);
    mainLayout->addWidget(portLabel,4,0);
    mainLayout->addWidget(portLineEdit,4,1);
    mainLayout->addWidget(enterBtn,5,0,1,2);

    status = false;
    port = 8010;
    portLineEdit->setText(QString::number(port));
    serverIP = new QHostAddress();
    connect(enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(slotSend()));

    sendBtn->setEnabled(true);


}

TcpClient::~TcpClient()
{

}

void TcpClient::slotEnter()
{
    if(!status)
    {
        QString ip = serverIPLineEdit->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this,QStringLiteral("error"),QStringLiteral("server ip address error"));
            return;
        }
        if(userNameLineEdit->text() == "")
        {
            QMessageBox::information(this,QStringLiteral("error"),QStringLiteral("User name error!"));
            return;
        }
        userName = userNameLineEdit->text();
        //创建一个QTcpSocket 类对象，并将信号槽链接起来
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        tcpSocket->connectToHost(*serverIP,port);
        status = true;
    }
    else
    {
        int length = 0;
        enterBtn->setText(QStringLiteral("进入"));
        QString msg = userName + QStringLiteral(":Leave Chat Room");
        if(length = tcpSocket->write(msg.toLatin1(),msg.length()) != msg.length())
        {
            return;
        }
        tcpSocket->disconnectFromHost();
        status = false;
    }
}

void TcpClient::slotConnected()
{
    sendBtn->setEnabled(true);
    enterBtn->setText(QStringLiteral("离开"));
    int length = 0;
    QString msg = userName + QStringLiteral(":Enter Chat Room");
    if((length = tcpSocket->write(msg.toLatin1(),msg.length())) != msg.length())
    {
        return;
    }
}

void TcpClient::slotDisconnected()
{
    sendBtn->setEnabled(false);
    enterBtn->setText(QStringLiteral("进入聊天室"));
}

void TcpClient::dataReceived()
{
    while(tcpSocket->bytesAvailable() > 0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(datagram.data(),datagram.size());
        QString msg = datagram.data();
        contentListWidget->addItem(msg.left(datagram.size()));
    }
}

void TcpClient::slotSend()
{
//    if(sendLineEdit->text() == "")
//    {
//        return;
//    }
    if(NULL == tcpSocket)
    {
        return;
    }
    QString msg = userName + ":" + sendLineEdit->text();
    tcpSocket->write(msg.toLatin1(),msg.length());
    sendLineEdit->clear();
}
