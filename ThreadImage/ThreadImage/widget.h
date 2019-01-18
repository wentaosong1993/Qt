#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void getImage(QImage tempImage);
    void dealClose();

protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QImage image;
    MyThread *myThread;//自定义线程对象
    QThread *thread;
};

#endif // WIDGET_H
