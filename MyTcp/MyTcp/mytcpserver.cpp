#include "mytcpserver.h"
#include "ui_mytcpserver.h"
#include <QHostAddress>

MyTcpServer::MyTcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTcpServer)
{
    ui->setupUi(this);
    tcpServer = nullptr;
    tcpSocket = nullptr;

    setWindowTitle(QStringLiteral("服务器端:8888"));
    //指定父对象，自动回收内存空间
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);

    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
    {
        //取出已建立连接的通信套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方的ip和端口号
        QString ip = tcpSocket->peerAddress().toString();
        qint32 port= tcpSocket->peerPort();
		QString temp = QString("[%1 : %2]").arg(ip).arg(port) + QStringLiteral("成功连接!");
        ui->textEditRead->setText(temp);


        connect(tcpSocket,&QTcpSocket::readyRead,
                [=]()
        {
            //从通信套接字中取出内容
            QByteArray array = tcpSocket->readAll();
            ui->textEditRead->append(QString(array));
        });
    }
    );
}

MyTcpServer::~MyTcpServer()
{
    delete ui;
}

void MyTcpServer::on_sendBtn_clicked()
{
    if(nullptr == tcpSocket)
    {
        return;
    }
    //获取输入框的内容
    QString inputText = ui->textEditWrite->toPlainText();
    tcpSocket->write(inputText.toUtf8().data());
}

void MyTcpServer::on_closeBtn_clicked()
{
    if(nullptr == tcpSocket)
    {
//        qApp->quit();
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = nullptr;
//    qApp->quit();
}
