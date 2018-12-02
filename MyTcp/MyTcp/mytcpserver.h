#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MyTcpServer;
}

class MyTcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit MyTcpServer(QWidget *parent = 0);
    ~MyTcpServer();

private slots:
    void on_sendBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::MyTcpServer *ui;

    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //建立连接的通信套接字

};

#endif // MYTCPSERVER_H
