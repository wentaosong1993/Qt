#include "dealwithlistwidget.h"
#include "ui_dealwithlistwidget.h"
#include <QMessageBox>
#include <QDebug>

DealWithListWidget::DealWithListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DealWithListWidget)
{
    ui->setupUi(this);
    w1.resize(180,100);
    w2.resize(180,100);
    w3.resize(180,100);
    strList << "1" << "2" << "3" << "4";
    ui->listWidget->addItems(strList);

    for(int i = 0; i < 3; i++)
    {
        connect(ui->listWidget,&QListWidget::itemClicked,this,&DealWithListWidget::dealWithData);
    }
}

DealWithListWidget::~DealWithListWidget()
{
    delete ui;
}

void DealWithListWidget::dealWithData()
{
    static int i = 0;
    i++;
//    QMessageBox::information(this,tr("ListItem"),tr("1"),QMessageBox::Yes | QMessageBox::No);
    if(i == 1)
    {
        w1.setWindowTitle("1_1");
        w1.show();
    }
    if(i == 2)
    {
        w2.setWindowTitle("1_2");
        w2.show();
    }
    if(i == 3)
    {
        w3.setWindowTitle("1_3");
        w3.show();
    }
    qDebug() << i;
}
