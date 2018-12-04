#include <QCoreApplication>
#include <QtCore>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlRecord>
#include <QSqlDriver>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("easybook-3313b0");
    db.setDatabaseName("qtDB1.db");
    db.setUserName("songwentao");
    db.setPassword("111111");
    bool ret = db.open();
    if(false == ret)
    {
        db.lastError();
    }
    else
    {
        qDebug() << QStringLiteral("数据库打开成功！");
    }

    //创建数据库
    QSqlQuery query;
    bool success = query.exec("create table automobile \
                              (id int primary key,     \
                               attribute varchar,      \
                               type varchar,           \
                               kind varchar,           \
                               nation int,carnumber int,\
                               elevalator int, \
                               distance int, \
                               oil int,\
                               temperature int)");

    if(success)
    {
        qDebug() << QStringLiteral("数据库表创建成功！\n");
    }
    else
    {
        qDebug() << QStringLiteral("数据库表创建失败！\n");
        qDebug() << query.lastError();
    }

    //查询
    query.exec("select * from automobile");
    QSqlRecord rec = query.record();
    qDebug() << QStringLiteral("automobile表字段数:") << rec.count();
    //插入记录
    QTime t;
    t.start();
    query.prepare("insert into automobile values(?,?,?,?,?,?,?,?,?,?)");

    long records = 100; //向表中插入任意100条记录
    for(int i =0 ; i < records; i++)
    {
        query.bindValue(0,i);
        query.bindValue(1,QStringLiteral("四轮"));
        query.bindValue(2,QStringLiteral("轿车"));
        query.bindValue(3,QStringLiteral("富康"));
        query.bindValue(4,rand() % 100);
        query.bindValue(5,rand() % 10000);
        query.bindValue(6,rand() % 300);
        query.bindValue(7,rand() % 200000);
        query.bindValue(8,rand() % 52);
        query.bindValue(9,rand() % 100);
        success = query.exec();

        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QStringLiteral("插入失败"));
        }
    }
    qDebug() << QStringLiteral("插入 %1 条记录,耗时: %2 ms").arg(records).arg(t.elapsed());

    //排序
    t.restart();
    success = query.exec("select * from automobile order by id desc");

    if(success)
    {
        qDebug() << QStringLiteral("排序 %1 条记录，耗时: %2 ms").arg(records).arg(t.elapsed());
    }
    else
    {
        qDebug() << QStringLiteral("排序失败");
    }
    //更新记录
    t.restart();

    for(int i = 0; i < records; i++)
    {
        query.clear();
        query.prepare(QString("update automobile set attribute = ?, \
                               type = ?,kind = ?, nation = ?,      \
                               carnumber = ?,elevalator = ?,       \
                               distance = ?,oil = ?,temperature = ? \
                               where id = %1").arg(i));

        query.bindValue(0,QStringLiteral("四轮"));
        query.bindValue(1,QStringLiteral("轿车"));
        query.bindValue(2,QStringLiteral("富康"));
        query.bindValue(3,rand() % 100);
        query.bindValue(4,rand() % 10000);
        query.bindValue(5,rand() % 300);
        query.bindValue(6,rand() % 200000);
        query.bindValue(7,rand() % 52);
        query.bindValue(8,rand() % 100);
        success = query.exec();

        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QStringLiteral("更新失败"));
        }
    }
    qDebug() << QStringLiteral("更新 %1 条记录,耗时: %2 ms").arg(records).arg(t.elapsed());

    //排序
    t.restart();
    query.exec("delete * from automobile where id = 15");

    //输出操作耗时
    qDebug() << QStringLiteral("删除一条记录,耗时: %1 ms").arg(t.elapsed());

    return 0;
}
