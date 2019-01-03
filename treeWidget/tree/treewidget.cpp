#include "treewidget.h"
#include "ui_treewidget.h"
#include <QTableWidgetItem>

treeWidget::treeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::treeWidget)
{
    ui->setupUi(this);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->horizontalHeader()->setVisible(true);

      ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "a" << "b" << "c" << "d");
//    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "aa" << "bb" << "3" << "4");
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setFixedHeight(300);
    QWidget *pItemWidget = new QWidget(this);
//    for(int i = 0; i < 4;i++)
//    {
//        for(int j = 0; j < 4; j++)
//        {
//            if(i == 0)
//            {
//                 ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "a" << "b" << "c" << "d");
//            }
//            ui->tableWidget->setCellWidget(i, j, pItemWidget);
//            ui->tableWidget->setItem(i,j, new QTableWidgetItem("111"));
//        }
//    }



}

treeWidget::~treeWidget()
{
    delete ui;
}
