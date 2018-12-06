#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QDebug>
#include "qdom.h"


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("easybook-3313b0");
    db.setDatabaseName("data.db");
    db.setUserName("songwentao");
    db.setPassword("123456");

    if(!db.open())
    {
        return false;
    }
    QSqlQuery query;
    query.exec(QString("create table factory(id varchar primary key,name varchar)"));
    query.exec(QString("insert into factory values('0','请选择厂家')"));
    query.exec(QString("insert into factory values('01','一汽大众')"));
    query.exec(QString("insert into factory values('02','二汽神龙')"));
    query.exec(QString("insert into factory values('03','上海大众')"));

    //创建品牌表
    query.exec(QString("create table brand(id varchar primary key,name varchar, \
                       factory varchar,price int,sum int,sell int,last int)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("insert into brand vaues('01','奥迪A6','一汽大众',36,50,10,40)"));

    return true;
}


#endif // CONNECTION_H
