#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QHeaderView>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(8);
    QStringList strList = QStringList() << QStringLiteral("编号1") << QStringLiteral("编号2") << QStringLiteral("编号3") << QStringLiteral("编号4")
                                        << QStringLiteral("编号5") << QStringLiteral("编号6") << QStringLiteral("编号7") << QStringLiteral("编号8");
    ui->tableWidget->setHorizontalHeaderLabels(strList);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    //样式表实现了像QQ聊天页面右侧的滑条悬浮效果，(*￣︶￣)
    ui->tableWidget->setStyleSheet("QTableWidget {selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,stop: 0 #FF92BB, stop: 1 white); } \
                                    QTableWidget QTableCornerButton::section {background: red;border: 2px outset red;} \
                                    QScrollBar::horizontal{max-height: 7px;border:0px;background: white;border-radius: 3;} \
                                    QScrollBar:horizontal:hover{max-height: 7px;border:0px;background:  #d2d2d2;border-radius: 3;} \
                                    QScrollBar::handle:horizontal{background:lightgrey; border-radius: 3px;} \
                                    QScrollBar::handle:horizontal:hover{background:grey; border-radius: 3px;} \
                                    QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal{border: 0px;background: none;} \
                                    QScrollBar::add-line:horizontal{border: 0px;height: 0px;} \
                                    QScrollBar::sub-line:horizontal{border: 0px;height: 0px;}");


    QStringList stringList;
    for(int i = 0; i < 26;i++)
    {
        QChar myChar = QChar('A' + i);
        stringList.append(QString(myChar));
    }

    for(int i = 0; i < 26;i++)
    {
        QChar myChar = QChar('A' + i);
        QString myLetter = QString(myChar);
        for(int j = 0; j < 1; j++)
        {
            QChar myChar1 = QChar('A' + j);
            QString myLetter1 = QString(myChar1);
            QString letter = myLetter + myLetter1;
            stringList.append(letter);
        }
    }

     qDebug() << stringList;


    for(int i = 0; i < ui->tableWidget->rowCount();i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount();j++)
        {
#if 0 //这样子无法插入数据
            if(ui->tableWidget->item(i,j))
            {
                QString temp = stringList.at((i+1)*(j+1));
                ui->tableWidget->item(i,j)->setText(temp);
            }
            else
            {
                    qDebug() << stringList;
            }
#endif
            QString temp = stringList.at((i+1)*(j+1));
            QTableWidgetItem* item = new QTableWidgetItem;
            ui->tableWidget->setItem(i,j,item);
            if( ui->tableWidget->item(i,j))
            {
                ui->tableWidget->item(i,j)->setText(temp);
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }



}

TableWidget::~TableWidget()
{
    delete ui;
}
