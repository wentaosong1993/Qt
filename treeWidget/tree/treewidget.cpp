#include "treewidget.h"
#include "ui_treewidget.h"
#include <QTableWidgetItem>
#include <QDebug>

treeWidget::treeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::treeWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(4);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "a" << "b" << "c" << "d");//类似操作需要在设置表格的行数和列数后有效
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "aa" << "bb" << "cc" << "dd");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setFixedHeight(300);
    QWidget *pItemWidget = new QWidget(this);
    for(int i = 0; i < 4;i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ui->tableWidget->setCellWidget(i, j, pItemWidget);
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString("%1_%2").arg(i).arg(j)));
            if(ui->tableWidget->item(i,j))
            {
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(setCurrentItemStyle(int,int)));
}

treeWidget::~treeWidget()
{
    delete ui;
}

void treeWidget::setCurrentItemStyle(int row, int column)
{
    QTableWidgetItem *curItem = ui->tableWidget->item(row,column);
    if(curItem)
    {
        curItem->setBackground(QBrush(Qt::red));
    }
//    QWidget *pSender = dynamic_cast<QWidget*>(this->sender());
//    if(pSender)
//    {
//       qDebug() << pSender;
//       pSender->setStyleSheet("QWidget{background: red;}");
//    }
//    else
//    {
//        qDebug() << "kkdk";
//    }

}
