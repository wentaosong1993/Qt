#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class MyTcpClient;
}

class MyTcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit MyTcpClient(QWidget *parent = 0);
    ~MyTcpClient();

private slots:
    void on_buttonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::MyTcpClient *ui;
    QTcpSocket *tcpSocket;
};

#endif // MYTCPCLIENT_H
