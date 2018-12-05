#include "connectdlg.h"
#include "ui_connectdlg.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>

ConnectDlg::ConnectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDlg)
{
    ui->setupUi(this);
    QStringList drivers = QSqlDatabase::drivers();
    ui->comboDriver->addItems(drivers);
    connect(ui->comboDriver,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(driverChanged(const QString &)));
    ui->status_lineEdit->setText(QStringLiteral("准备连接数据库！"));
}

ConnectDlg::~ConnectDlg()
{
    delete ui;
}

QString ConnectDlg::driverName() const
{
    return ui->comboDriver->currentText();
}

QString ConnectDlg::databaseName() const
{
    return ui->editDatabase->text();
}

QString ConnectDlg::userName() const
{
    return ui->editUsername->text();
}

QString ConnectDlg::password() const
{
    return ui->editPassword->text();
}

QString ConnectDlg::hostName() const
{
    return ui->editHostname->text();
}

int ConnectDlg::port() const
{
    return ui->portSpinBox->value();
}

QSqlError ConnectDlg::addConnection(const QString &driver, const QString &dbName, const QString &host, const QString &user, const QString &passwd, int port)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if(!db.open(user,passwd))
    {
        err = db.lastError();
    }
    return err;
}

void ConnectDlg::createDB()
{
    QSqlQuery query;
	//query.exec(QStringLiteral("create table factory (id int primary key,manufactory varchar(60),address varchar(60))"));
	//query.exec(QStringLiteral("insert into factory values(1,'一汽大众','长春')"));
	//query.exec(QStringLiteral("insert into factory values(2,'二汽神龙','武汉')"));
	//query.exec(QStringLiteral("insert into factory values(3,'一起大众','长春')"));
	//query.exec(QStringLiteral("insert into factory values(4,'二汽神龙','武汉')"));
	//query.exec(QStringLiteral("create table cars (carid int primary key,name varchar(50),factoryid int,year int)"));
	//query.exec(QStringLiteral("insert into cars values(1,'奥迪A6',1,2005)"));
	//query.exec(QStringLiteral("insert into cars values(2,'捷达',1,1993)"));
	//query.exec(QStringLiteral("insert into cars values(3,'宝来',1,2000)"));
	//query.exec(QStringLiteral("insert into cars values(4,'毕加索',2,1999)"));
	//query.exec(QStringLiteral("insert into cars values(5,'富康',2,2004)"));
	//query.exec(QStringLiteral("insert into cars values(6,'标志307',2,2001)"));
	//query.exec(QStringLiteral("insert into cars values(7,'桑塔拉',3,1995)"));
	//query.exec(QStringLiteral("insert into cars values(8,'帕萨特',3,2000)"));
	//query.exec(QStringLiteral("insert into cars values(9,'桑塔拉',3,1995)"));
	//query.exec(QStringLiteral("insert into cars values(10,'帕萨特',3,2000)"));
	query.exec(QObject::tr("create table factory (id int primary key,manufactory varchar(60),address varchar(60))"));
	query.exec(QObject::tr("insert into factory values(1,'一汽大众','长春')"));
	query.exec(QObject::tr("insert into factory values(2,'二汽神龙','武汉')"));
	query.exec(QObject::tr("insert into factory values(3,'一起大众','长春')"));
	query.exec(QObject::tr("insert into factory values(4,'二汽神龙','武汉')"));
	query.exec(QObject::tr("create table cars (carid int primary key,name varchar(50),factoryid int,year int)"));
	query.exec(QObject::tr("insert into cars values(1,'奥迪A6',1,2005)"));
	query.exec(QObject::tr("insert into cars values(2,'捷达',1,1993)"));
	query.exec(QObject::tr("insert into cars values(3,'宝来',1,2000)"));
	query.exec(QObject::tr("insert into cars values(4,'毕加索',2,1999)"));
	query.exec(QObject::tr("insert into cars values(5,'富康',2,2004)"));
	query.exec(QObject::tr("insert into cars values(6,'标志307',2,2001)"));
	query.exec(QObject::tr("insert into cars values(7,'桑塔拉',3,1995)"));
	query.exec(QObject::tr("insert into cars values(8,'帕萨特',3,2000)"));
	query.exec(QObject::tr("insert into cars values(9,'桑塔拉',3,1995)"));
	query.exec(QObject::tr("insert into cars values(10,'帕萨特',3,2000)"));

	qDebug() << query.exec("SELECT * FROM cars");
	//query.seek(0);
	QSqlRecord record = query.record();
	QString name = record.value("name").toString();
	qDebug() << "name:" << name;
	qDebug() << query.lastError();

}

void ConnectDlg::readDB()
{

}

void ConnectDlg::addSqliteConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    db.setDatabaseName(QStringLiteral("databasefile"));
    if(!db.open())
    {
        ui->status_lineEdit->setText(db.lastError().text());
        return;
    }
    ui->status_lineEdit->setText(QStringLiteral("创建sqlite数据库成功!"));
}

void ConnectDlg::on_okButton_clicked()
{
    if(ui->comboDriver->currentText().isEmpty())
    {
        ui->status_lineEdit->setText(QStringLiteral("请选择一个数据库驱动！"));
        ui->comboDriver->setFocus();
    }
    else if(ui->comboDriver->currentText() == "QSQLITE")
    {
        addSqliteConnection();
        //创建数据库表，如已存在则无须执行
        createDB();
		readDB();
        accept();
    }
    else
    {
        QSqlError err = addConnection(driverName(),databaseName(),hostName(),userName(),password(),port());
        if(err.type() != QSqlError::NoError)
        {
            ui->status_lineEdit->setText(err.text());
        }
        else
        {
            ui->status_lineEdit->setText(QStringLiteral("连接数据库成功！"));
        }
        //创建数据库表，如已存在则无须执行
        accept();
    }
}

void ConnectDlg::driverChanged(const QString & text)
{
    if(text == "QSQLITE")
    {
        ui->editDatabase->setEnabled(false);
        ui->editUsername->setEnabled(false);
        ui->editHostname->setEnabled(false);
        ui->editPassword->setEnabled(false);
        ui->portSpinBox->setEnabled(false);
    }
    else
    {
        ui->editDatabase->setEnabled(true);
        ui->editUsername->setEnabled(true);
        ui->editHostname->setEnabled(true);
        ui->editPassword->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
    }
}


