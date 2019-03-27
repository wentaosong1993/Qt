#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealSignal();
    void dealClose();
//    void myTimeOut();
signals:
    void startThread(); //启动子线程的信号
//    void timeSignal();

private slots:
    void on_startBtn_clicked();

    void on_stopBtn_clicked();

private:
    Ui::MyWidget *ui;

    myThread *m_thread;
    QThread *m_qThread;
//    bool m_flag;
};

#endif // MYWIDGET_H
