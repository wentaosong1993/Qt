#include "mytcpclient.h"
#include "ui_mytcpclient.h"

#include <QHostAddress>

MyTcpClient::MyTcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTcpClient)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("客户端"));
    tcpSocket = NULL;

    //创建通信套接字，指定父对象，自动内存回收
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
            {
                ui->textEditRead->setText(QStringLiteral("成功与服务器建立好连接"));
            }
    );


    //客户端收到的内容
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                //获取对方发送的所有数据
                QByteArray array = tcpSocket->readAll();
                ui->textEditRead->append(QString(array));
            }
    );
}

MyTcpClient::~MyTcpClient()
{
    delete ui;
}

void MyTcpClient::on_buttonConnect_clicked()
{
    //获取服务器端口和ip
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();

    //与服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void MyTcpClient::on_pushButtonSend_clicked()
{
    //从输入框获取发送发送的内容
    QString content = ui->textEditWrite->toPlainText();
    tcpSocket->write(content.toUtf8().data());
}

void MyTcpClient::on_pushButtonClose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
//    qApp->quit();
}
