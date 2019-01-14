#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));
//    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));

    connect(ui->pushButton,SIGNAL(toggled(bool)),this,SLOT(buttonClick(bool)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buttonClick()
{
//    disconnect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));
//    qDebug() << "execution";
////    emit clickSignal();
//        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(buttonClick()));
    //临时文件路径
//    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("Open the dialog"),QStandardPaths::writableLocation(QStandardPaths::TempLocation),QStringLiteral("Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"));
//    if(!fileName.isEmpty())
//    {
//        qDebug() << fileName;
//    }

   QStringList standardPath = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
   qDebug() << standardPath;
}

void Widget::buttonClick(bool isChecked)
{
    if(isChecked)
    {
        qDebug() << "true";
    }
    else
    {
        qInfo() << "false";
    }
}
