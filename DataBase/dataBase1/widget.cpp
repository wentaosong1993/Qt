#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("songwentao");
    //setdatabasename（）必须是已经存在的数据库
    db.setDatabaseName("info");
//    db.setPort(3306);//3307

    if(!db.open())
    {
      QMessageBox::warning(this,QStringLiteral("message"),db.lastError().text());
      qDebug() << db.lastError().text();
    }
    else
    {
        QMessageBox::information(this,QStringLiteral("message"),"Success!");
    }

}

Widget::~Widget()
{
    delete ui;
}
