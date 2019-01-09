#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));
    connect(this,SIGNAL(clickSignal()),this,SLOT(buttonClick()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buttonClick()
{
    disconnect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));
    qDebug() << "execution";
//    emit clickSignal();
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));
}
