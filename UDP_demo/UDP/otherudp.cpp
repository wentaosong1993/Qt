#include "otherudp.h"
#include "ui_otherudp.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>

OtherUdp::OtherUdp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtherUdp)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("我的端口：8888"));

    otherUdpSocket = new QUdpSocket(this);
    otherUdpSocket->bind(8888);

    //data Available
    connect(otherUdpSocket,&QUdpSocket::readyRead,this,&OtherUdp::dealMsg);

}

OtherUdp::~OtherUdp()
{
    delete ui;
}

void OtherUdp::dealMsg()
{
    //格式化获取的数据
   char buf[1024] = {0};
   QHostAddress dFIP;
   quint16 dFPort;

   qint64 len = otherUdpSocket->readDatagram(buf,sizeof(buf),&dFIP,&dFPort);
    if(len > 0)
    {
        QString textShow = QString("[%1 : %2] %3").arg(dFIP.toString()).arg(dFPort).arg(buf);
        ui->otherTextEdit->setText(textShow);
    }
    else
    {
        QMessageBox::warning(this, tr("My Application"),
                             tr("can't get the remote data."),
                             QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
    }
}

void OtherUdp::on_otherSendBtn_clicked()
{
    QString myIP = ui->otherLineEditIP->text().trimmed();
    quint16 myPort = ui->otherLineEditPort->text().trimmed().toInt();
    QString str = ui->otherTextEdit->toPlainText().trimmed();
    qint64 len= otherUdpSocket->writeDatagram(str.toUtf8(),QHostAddress(myIP),myPort);
    if(str.isEmpty())
    {
        return;
    }
    if(len != str.length())
    {
        QMessageBox::warning(this, tr("My Application"),
                             tr("send failed."),
                             QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
    }
    ui->otherTextEdit->clear();
}

void OtherUdp::on_otherCloseBtn_clicked()
{
    otherUdpSocket->disconnectFromHost();
    close();
}
