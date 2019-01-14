#include "treewidget.h"
#include "ui_treewidget.h"
#include <QDebug>
#include <QBrush>


TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWidget)
{
    ui->setupUi(this);
//    ui->treeWidget->setColumnCount(1);
//    QList<QTreeWidgetItem *> items;
//    for(int i = 0; i < 10; i++)
//    {
//        items.append(new QTreeWidgetItem((QTreeWidget*)(0),QStringList(QString("item: %1").arg(i))));
//    }
//    ui->treeWidget->insertTopLevelItems(0,items);
//    ui->treeWidget->insertTopLevelItem(10,new QTreeWidgetItem((QTreeWidget*)(0),QStringList(QString("item:x")))); //index指的是item索引

//    for(int i = 0; i <ui->treeWidget->topLevelItemCount();i++)
//    {
//        qDebug() << ui->treeWidget->topLevelItemCount();
//        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
//        if(item)
//        {
////            qDebug() << item->text(0);
////            ui->treeWidget->setToolTip(item->text(0)); //不行
//            item->setToolTip(0,item->text(0)); //可行
//            item->setCheckState(0,Qt::Checked);
//        }
//    }

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(QStringLiteral("图像选择"));
    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QStringLiteral("图像1")));
    imageItem1->setToolTip(0,imageItem1->text(0));


    QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QStringLiteral("brand1")));
    imageItem1_1->setToolTip(0,imageItem1_1->text(0));
    imageItem1->addChild(imageItem1_1);


    QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(ui->treeWidget,QStringList(QStringLiteral("图像2")));
    imageItem2->setToolTip(0,imageItem2->text(0));
    QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2,QStringList(QStringLiteral("brand1")));
    imageItem2_1->setToolTip(0,imageItem2_1->text(0));
    QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2,QStringList(QStringLiteral("brand2")));
    imageItem2_2->setToolTip(0,imageItem2_2->text(0));

    imageItem2->addChild(imageItem2_1);
    imageItem2->addChild(imageItem2_2);

    ui->treeWidget->expandAll();
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(printSlot(QTreeWidgetItem*,int)));


#if 0 //效果同上
    QList<QTreeWidgetItem*> rootList;

    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem;
    imageItem1->setText(0,QStringLiteral("图像1"));
    rootList.append(imageItem1);

    QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QStringLiteral("brand1")));

    imageItem1->addChild(imageItem1_1);


    QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(ui->treeWidget,QStringList(QStringLiteral("图像2")));
    rootList.append(imageItem2);


    QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2,QStringList(QStringLiteral("brand1")));
    QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2,QStringList(QStringLiteral("brand2")));

    imageItem2->addChild(imageItem2_1);
    imageItem2->addChild(imageItem2_2);

    ui->treeWidget->insertTopLevelItems(0,rootList);
    ui->treeWidget->expandAll();
#endif
}

TreeWidget::~TreeWidget()
{
    delete ui;
}

void TreeWidget::printSlot(QTreeWidgetItem *item,int col)
{
    if(item)
    {
//        item->setToolTip(col,item->text(col));
        item->setBackground(0,QBrush(Qt::red));
    }
    else
    {
        qDebug() << "null";
    }
}
