#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "regexpinterface.h"
#include "ui_widget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    bool loadPlugin();
private slots:
    void on_pushButton_clicked();

private:
     RegExpInterface *regExpInterface;
     Ui::Form *ui;
};

#endif // WIDGET_H
