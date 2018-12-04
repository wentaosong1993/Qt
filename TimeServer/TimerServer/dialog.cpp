#include "dialog.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include "timeserver.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QStringLiteral("多线程时间服务器"));
    label1 = new QLabel(QStringLiteral("服务器端口:"));
    label2 = new QLabel;
    quitBtn = new QPushButton(QStringLiteral("退出"));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(quitBtn);
    btnLayout->addStretch(1);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label1);
    mainLayout->addWidget(label2);
    mainLayout->addLayout(btnLayout);

    connect(quitBtn,SIGNAL(clicked()),this,SLOT(close()));

    count = 0;
    timeServer = new TimeServer(this); //创建监听套接字
    if(!timeServer->listen())
    {
        QMessageBox::critical(this,QStringLiteral("多线程时间服务器"),QStringLiteral("无法启动服务器：%1.").arg(timeServer->errorString()));
        close();
        return;
    }
    label1->setText(QStringLiteral("服务器端口: %1.").arg(timeServer->serverPort())); //返回监听的端口号
}

Dialog::~Dialog()
{

}

void Dialog::slotShow()
{
    label2->setText(QStringLiteral("第%1请求完毕。").arg(++count));
}
