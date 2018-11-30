#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QTimer>

class UdpServer : public QDialog
{
    Q_OBJECT

public:
    UdpServer(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~UdpServer();

public slots:
    void startBtnClicked();
    void timerOut();

private:
    QLabel *timerLabel;
    QLineEdit *timerLineEdit;
    QLineEdit *textLineEdit;
    QPushButton *startBtn;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horLayout;

private:
    int port;
    bool isStarted;
    QUdpSocket *udpSocket;
    QTimer *timer;
};

#endif // UDPSERVER_H
