#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include "mythread.h"

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void buttonClick();
    void dealTimeout();
    void timerStop();

private:
    Ui::MyWidget *ui;
    QTimer *m_timer;
    MyThread *m_thread;
};

#endif // MYWIDGET_H
