#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("端口号为8888"));
    udpSocket = new QUdpSocket(this);

    //绑定
    udpSocket->bind(8888);


//    udpSocket->bind(QHostAddress::AnyIPv4, 8888);
//    //组播地址是D类地址
//    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.2")); //加入
//    udpSocket->leaveMulticastGroup(QHostAddress("224.0.0.2"));//退出

    //收到数据时
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::dealMsg);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealMsg()
{
    char buf[1024] = {0};
    QHostAddress cliAddress;
    quint16 port;
    qint64  len = udpSocket->readDatagram(buf,sizeof(buf),&cliAddress,&port);
    if(len > 0)
    {
        QString str = QString("[%1:%2] %3").arg(cliAddress.toString()).arg(port).arg(buf);
        ui->textEdit->setText(str);
    }
}

void Widget::on_sendBtn_clicked()
{
    //发送数据，writeDatagram
    QString strIP = ui->lineEditIP->text().trimmed();
    quint16 strPort = ui->lineEditPort->text().trimmed().toInt();

    QString str = ui->textEdit->toPlainText().trimmed();

    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(strIP),strPort);
}
