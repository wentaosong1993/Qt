#include "connectdlg.h"
#include "ui_connectdlg.h"
#include <QSqlDatabase>
#include <QtSql>

ConnectDlg::ConnectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDlg)
{
    ui->setupUi(this);
    QStringList drivers = QSqlDatabase::drivers();
    ui.comboDriver->addItems(drivers);
    connect(ui.comboDriver,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(driverChanged(const QString &)));
    ui.status_label->setText(QStringLiteral("准备连接数据库！"));
}

ConnectDlg::~ConnectDlg()
{
    delete ui;
}

QString ConnectDlg::driverName() const
{
    return ui.comboDriver->currentText();
}

QString ConnectDlg::databaseName() const
{
    return ui.editDatabase->text();
}

QString ConnectDlg::userName() const
{
    return ui.editUsername->text();
}

QString ConnectDlg::password() const
{
    return ui.editPassword->text();
}

QString ConnectDlg::hostName() const
{
    return ui.editHostname->text();
}

int ConnectDlg::port() const
{
    return ui.portSpinBox->value();
}

void ConnectDlg::on_okButton_clicked()
{
    if(ui.comboDriver->currentText().isEmpty())
    {
        ui.status_label->setText(QStringLiteral("请选择一个数据库驱动！"));
        ui.comboDriver->setFocus();
    }
    else if(ui.comboDriver->currentText() == "QSQLITE")
    {
        addSqliteConnection();
        //创建数据库表，如已存在则无须执行
        creatDB();
        accept();
    }
    else
    {
        QSqlError err = addConnection(driverName(),databaseName(),hostName(),userName(),password(),port());
        if(err.type() != QSqlError::NoError)
        {
            ui.status_label->setText(err.text());
        }
        else
        {
            ui.status_label->setText(QStringLiteral("连接数据库成功！"));
        }
        //创建数据库表，如已存在则无须执行
        accept();
    }
}

void ConnectDlg::driverChanged(const QString & text)
{
    if(text == "QSQLITE")
    {
        ui.editDatabase->setEnabled(false);
        ui.editUsername->setEnabled(false);
        ui.editHostname->setEnabled(false);
        ui.editPassword->setEnabled(false);
        ui.portSpinBox->setEnabled(false);
    }
    else
    {
        ui.editDatabase->setEnabled(true);
        ui.editUsername->setEnabled(true);
        ui.editHostname->setEnabled(true);
        ui.editPassword->setEnabled(true);
        ui.portSpinBox->setEnabled(true);
    }
}
