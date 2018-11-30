#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QUdpSocket>


class UdpClient : public QDialog
{
    Q_OBJECT

public:
    UdpClient(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~UdpClient();
public slots:
    void closeBtnClicked();
    void dataReceived();
private:
    QTextEdit *receiveTextEdit;
    QPushButton *closeBtn;
    QVBoxLayout *mainLayout;
    int port;
    QUdpSocket *udpSocket;
};

#endif // UDPCLIENT_H
