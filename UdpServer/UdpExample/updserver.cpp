#include "udpserver.h"
#include <QHostAddress>

UdpServer::UdpServer(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent,f)
{
    resize(200,100);
    setWindowTitle(QStringLiteral("UDP Server"));
    timerLabel = new QLabel(QStringLiteral("计时器:"),this);
    timerLineEdit = new QLineEdit;
    timerLineEdit->setPlaceholderText(QStringLiteral("请输入定时时间(单位：ms)"));
    textLineEdit = new QLineEdit;
    startBtn = new QPushButton(QStringLiteral("开始"),this);
    mainLayout = new QVBoxLayout(this);
    horLayout = new QHBoxLayout;
    horLayout->addWidget(timerLabel);
    horLayout->addWidget(timerLineEdit);
    mainLayout->addLayout(horLayout);
    mainLayout->addWidget(textLineEdit);
    mainLayout->addWidget(startBtn);

    connect(startBtn,SIGNAL(clicked()),this,SLOT(startBtnClicked()));
    port = 5555; //初始化端口
    isStarted = false;
    udpSocket = new QUdpSocket(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerOut()));
}

UdpServer::~UdpServer()
{

}

void UdpServer::startBtnClicked()
{
    if(!isStarted)
    {
        startBtn->setText(QStringLiteral("停止"));
        timer->start(timerLineEdit->text().trimmed().toInt());
        isStarted = true;
    }
    else
    {
        startBtn->setText(QStringLiteral("开始"));
        timer->stop();
        isStarted = false;
    }
}

void UdpServer::timerOut()
{
    QString msg = textLineEdit->text();
    if(msg == "")
    {
        return;
    }
    if(udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::Broadcast,port) != msg.length()) //发送数据报
    {
        return;
    }

}
