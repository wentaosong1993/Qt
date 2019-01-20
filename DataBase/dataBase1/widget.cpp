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
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("info");

    if(!db.open())
    {
//        QMessageBox::warning(this,QStringLiteral("message"),db.lastError().text());
      qDebug() << db.lastError().text();
    }

}

Widget::~Widget()
{
    delete ui;
}
