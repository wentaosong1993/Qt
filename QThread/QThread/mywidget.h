#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>

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

private:
    Ui::MyWidget *ui;
    QTimer *m_timer;
};

#endif // MYWIDGET_H
