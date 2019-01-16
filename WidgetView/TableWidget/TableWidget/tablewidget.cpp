#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QHeaderView>
#include <QDebug>
#include <QComboBox>
#include <QStyledItemDelegate>

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
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);
    //样式表实现了像QQ聊天页面右侧的滑条悬浮效果，(*￣︶￣)
    ui->tableWidget->setStyleSheet("QTableWidget{border: none;color: #282828;gridline-color: #D3DCE6;} \
                                    QTableWidget::item::selected{border: 2px solid #20a0ff;background: transparent;color: black;} \
                                    QScrollBar::horizontal{max-height: 7px;border:0px;background: white;border-radius: 3;} \
                                    QScrollBar:horizontal:hover{max-height: 7px;border:0px;background:  #d2d2d2;border-radius: 3;} \
                                    QScrollBar::handle:horizontal{background:lightgrey; border-radius: 3px;} \
                                    QScrollBar::handle:horizontal:hover{background:grey; border-radius: 3px;} \
                                    QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal{border: 0px;background: none;} \
                                    QScrollBar::add-line:horizontal{border: 0px;height: 0px;} \
                                    QScrollBar::sub-line:horizontal{border: 0px;height: 0px;} \
                                    QScrollBar::vertical{max-width: 7px;border:0px;background: white;border-radius: 3;} \
                                    QScrollBar:vertical:hover{max-height: 7px;border:0px;background:  #d2d2d2;border-radius: 3;} \
                                    QScrollBar::handle:vertical{background:lightgrey; border-radius: 3px;} \
                                    QScrollBar::handle:vertical:hover{background:grey; border-radius: 3px;} \
                                    QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{border: 0px;background: none;} \
                                    QScrollBar::add-line:vertical{border: 0px;height: 0px;} \
                                    QScrollBar::sub-line:vertical{border: 0px;height: 0px;}");


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
                ui->tableWidget->item(i,j)->setFlags(ui->tableWidget->item(i,j)->flags() & (~Qt::ItemIsEditable)); //让单元格不可编辑
            }

            if(ui->tableWidget->item(i,j))
            {
                //让单元格可以编辑，并且实现了选中本行后，可以单击使单元格进入编辑状态；
                ui->tableWidget->item(0,j)->setFlags(ui->tableWidget->item(i,j)->flags() | (Qt::ItemIsEditable | Qt::ItemIsSelectable));
            }
        }
    }

    QComboBox *combox = new QComboBox;
    combox->insertItems(0,strList);
    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
    combox->setItemDelegate(itemDelegate);
//    combox->setStyleSheet("QComboBox {border: 1px solid #32A8FF;border-radius: 3px;padding: 1px 18px 1px 3px;min-width: 6em;} \
//                           QComboBox:editable {background: white;} }");
    combox->setStyleSheet("\
                          QComboBox{background:#F9FAFC;border:1px solid #d3dce6;padding:0px 0px 0px 10px;color:#222222;font:16px;}\
                          QComboBox:focus{background:#ffffff;border:1px solid #20a0ff;padding:0px 0px 0px 10px;color:#222222;font:16px;}\
                          QComboBox:on{background:#ffffff;border:1px solid #20a0ff;padding:0px 0px 0px 10px;color:#222222;font:16px;}\
                          QComboBox:disabled{background:#f3f5f7;border:1px solid #d3dce6;padding:0px 0px 0px 10px;color:#c9d0d5;font:16px;}\
                          QComboBox::drop-down{width:24px;height: 24;background:transparent;border-image: url(:/Resources/drop-down_nor.png);}\
                          QComboBox::drop-down:hover{width:24px;height:24;background:transparent;border-image: url(:/Resources/drop-down_hover.png);}\
                          QComboBox::drop-down:pressed{width:24px;height: 24;background:transparent;border-image: url(:/Resources/drop-down_press.png);}\
                          QComboBox QAbstractItemView{border:1px solid #20a0ff;outline:0px;selection-background-color: #bdddf5;height:40px;background:white;}\
                          QComboBox QAbstractItemView::item{height:35px;font:16px;color:black;padding-left:10px;}\
                          QComboBox QAbstractItemView::item:selected{background-color: #bdddf5;} \
                          QComboBox QScrollBar:vertical{ max-width:7px; border:0px; background:#F6F7F9; } \
                          QComboBox QScrollBar::handle:vertical{ background:rgba(100,100,100,30%); border-radius:3px;} \
                          QComboBox QScrollBar::handle:vertical:hover{ background:rgba(100,100,100,50%);} \
                          QComboBox QScrollBar::add-line:vertical{ border:0px; height:0px; } \
                          QComboBox QScrollBar::sub-line:vertical{ border:0px; height:0px; }");
    ui->tableWidget->setCellWidget(0,7,combox);


}

TableWidget::~TableWidget()
{
    delete ui;
}
