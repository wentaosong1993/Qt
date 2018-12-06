﻿#include "widget.h"
#include "ui_widget.h"
#include <QMenuBar>
#include <QSqlQueryModel>
#include <QSplitter>

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    setFixedSize(750,500);
    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *factoryModel = new QSqlQueryModel(this);
    factoryModel->setQuery("select name from factory");
    ui->sellFactoryComboBox->setModel(factoryModel);
    QSplitter *splitter = new QSplitter(ui->managePage);
    splitter->resize(700,360);
    splitter->move(0,50);
    splitter->addWidget(ui->toolBox);
    splitter->addWidget(ui->dailyList);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,1);

    createMenuBar();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_manageMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_chartMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_quitMenu_clicked()
{
    this->close();
}

void Widget::createMenuBar()
{
    manageAction = new QAction(QStringLiteral("品牌车管理"),this);
    chartAction = new QAction(QStringLiteral("销售统计"),this);
    quitAction = new QAction(QStringLiteral("退出"),this);

    manageAction->setShortcut(QStringLiteral("Ctrl+M"));
    chartAction->setShortcut(QStringLiteral("Ctrl+C"));
    quitAction->setShortcut(QStringLiteral("Ctrl+Q"));

    manageMenu = menuBar()->addMenu(QStringLiteral("销售管理"));
    manageMenu->addAction(manageAction);
    manageMenu->addAction(chartAction);
    manageMenu->addSeparator();
    manageMenu->addAction(quitAction);
    passwordMenu = menuBar()->addMenu(QStringLiteral("修改密码"));

    connect(manageAction,SIGNAL(triggered()),this,SLOT(on_manageMenu_clicked()));
    connect(chartAction,SIGNAL(triggered()),this,SLOT(on_chartMenu_clicked()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(on_quitMenu_clicked()));
}

void Widget::on_sellFactoryComboBox_activated(const QString &arg1)
{
    if(arg1 == QStringLiteral("请选择厂家"))
    {
        on_sellCancelBtn_clicked();
    }
    else
    {
        ui->sellBrandComboBox->setEnabled(true);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("select name from brand where factory='%1'").arg(arg1));
        ui->sellBrandComboBox->setModel(model);
        ui->sellCancelBtn->setEnabled(true);
    }
}
