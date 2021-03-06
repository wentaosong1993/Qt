﻿#include "publishmanager.h"
#include <QDebug>
#include <QAbstractItemView>
#include <QPushButton>
#include "mydialog.h"


PublishManager::PublishManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PublishManager)
{
    ui->setupUi(this);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->pushButtonAll,0);
    buttonGroup->addButton(ui->pushButtonPutaway,1);
    buttonGroup->addButton(ui->pushButtonUnshelve,2);
    buttonGroup->addButton(ui->pushButtonPutawayFail,3);

    initWindow();//实例化表格

    connect(ui->pushButtonDetail,SIGNAL(clicked()),this,SLOT(viewUnionRegulations()));
}

PublishManager::~PublishManager()
{
    delete ui;
}

void PublishManager::initWindow()
{
    QString tabStyle = "QTableWidget{border:none;color:#282828;	gridline-color:#D3DCE6;} \
    QTableWidget::item::selected{background-color:  #b3ecff;}";

    QString transparentScroll = "QScrollBar:horizontal{max-height:7px; border:0px; background:transparent;} \
    QScrollBar::handle:horizontal{background:transparent; border-radius:3px;} \
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal{border:0px; background:none;} \
    QScrollBar::add-line:horizontal{border:0px; height:0px;} \
    QScrollBar::sub-line:horizontal{border:0px; height:0px;}";

    ui->tableWidget_2->setColumnWidth(0, 200);//第1列
    ui->tableWidget_2->setColumnWidth(1, 900);//第2列
    ui->tableWidget_2->setColumnWidth(2, 210);//第3列
//    ui->tableWidget_2->setRowHeight(1,400); //设置表格第一行的高度（不计算行表头的高度）
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);


    m_SrcTabWidget = new QTableWidget(ui->tableWidget_2);
    connect(m_SrcTabWidget,SIGNAL(cellPressed(int,int)),this,SLOT(selectSrcTable(int)));
    m_SrcTabWidget->setStyleSheet(tabStyle + transparentScroll);
    m_SrcTabWidget->verticalHeader()->setVisible(false);
    m_SrcTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_SrcTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_SrcTabWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_SrcTabWidget->setFocusPolicy(Qt::NoFocus);
    m_SrcTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_SrcTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_SrcTabWidget->horizontalHeader()->setStretchLastSection(true);

    //表头
    const QStringList orginalHead = QStringList() << QStringLiteral("品牌")
        << QStringLiteral("物料号") << QStringLiteral("产地");
    m_SrcTabWidget->setColumnCount(orginalHead.size());
    m_SrcTabWidget->setHorizontalHeaderLabels(orginalHead);
    m_SrcTabWidget->setColumnWidth(0, 50);
    m_SrcTabWidget->setColumnWidth(1, 50);
    m_SrcTabWidget->setColumnWidth(2, 50);

    m_SrcTabWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_SrcTabWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_SrcTabWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    //转换数据表
    m_ConverTabWidget = new QTableWidget(ui->tableWidget_2);
    connect(m_ConverTabWidget,SIGNAL(cellPressed(int,int)),this,SLOT(selectConverTable(int)));
    m_ConverTabWidget->verticalHeader()->setVisible(false);
    m_ConverTabWidget->setStyleSheet(tabStyle + transparentScroll);
    m_ConverTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ConverTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ConverTabWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_ConverTabWidget->setFocusPolicy(Qt::NoFocus);
    m_ConverTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ConverTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ConverTabWidget->horizontalHeader()->setStretchLastSection(true);

    QStringList convHead = QStringList() << QStringLiteral("品牌 *") << QStringLiteral("商品号 *")
        << QStringLiteral("产地") << QStringLiteral("商品名称 *") << QStringLiteral("OE号")
        << QStringLiteral("替换号") << QStringLiteral("质保") << QStringLiteral("单位")
        << QStringLiteral("规格及备注");
    m_ConverTabWidget->setColumnCount(convHead.size());
    m_ConverTabWidget->setHorizontalHeaderLabels(convHead);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); //需要放置在设置行数和列数后，否则崩溃
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    m_ConverTabWidget->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);


    m_OperatorTabWidget = new QTableWidget(ui->tableWidget_2);
    connect(m_OperatorTabWidget,SIGNAL(cellPressed(int,int)),this,SLOT(selectOperatorTable(int)));
    m_OperatorTabWidget->verticalHeader()->setVisible(false);
    m_OperatorTabWidget->setStyleSheet(tabStyle + transparentScroll);
    m_OperatorTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_OperatorTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
    m_OperatorTabWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//不可编辑
    m_OperatorTabWidget->setFocusPolicy(Qt::NoFocus);//去掉选中虚线框
    m_OperatorTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_OperatorTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_OperatorTabWidget->horizontalHeader()->setStretchLastSection(true);

    //表头
    QStringList operatorHead = QStringList() << QStringLiteral("状态") << QStringLiteral("操作");
    m_OperatorTabWidget->setColumnCount(operatorHead.size());
    m_OperatorTabWidget->setHorizontalHeaderLabels(operatorHead);

    m_OperatorTabWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_OperatorTabWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableWidget_2->setCellWidget(0, 0, m_SrcTabWidget);
    ui->tableWidget_2->setCellWidget(0, 1, m_ConverTabWidget);
    ui->tableWidget_2->setCellWidget(0, 2, m_OperatorTabWidget);


    m_SrcTabWidget->clearContents();
    m_SrcTabWidget->setFixedHeight(200);

    m_SrcTabWidget->setRowCount(4);
    m_SrcTabWidget->setColumnCount(3);

    for(int i = 0; i < 4;i++) //行
    {
        for(int j = 0 ; j < 3; j++)//列
        {
//          QWidget *pItemWidget = new QWidget(this);
            m_SrcTabWidget->setItem(i,j,new QTableWidgetItem("111"));
            m_SrcTabWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    m_ConverTabWidget->clearContents();
    m_ConverTabWidget->setFixedHeight(200);

    m_ConverTabWidget->setRowCount(4);
    m_ConverTabWidget->setColumnCount(9);
    m_ConverTabWidget->verticalHeader()->setDefaultSectionSize(30);
    for(int i = 0; i < 4;i++) //行
    {
        for(int j = 0 ; j < 9; j++)//列
        {
            m_ConverTabWidget->setItem(i,j,new QTableWidgetItem("111"));
            m_ConverTabWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    m_OperatorTabWidget->clearContents();
    m_OperatorTabWidget->setFixedHeight(200);
    m_OperatorTabWidget->setRowCount(4);
    m_OperatorTabWidget->setColumnCount(2);
    m_OperatorTabWidget->verticalHeader()->setDefaultSectionSize(30);

    for(int i = 0; i < 4;i++) //行
    {
        for(int j = 0 ; j < 2; j++)//列
        {
            QWidget *pItemWidget = new QWidget(this);
            m_button = new QIconPushButton(this);
            m_OperatorTabWidget->setCellWidget(i,j,m_button);
        }
    }
}

void PublishManager::selectSrcTable(int row/*,int column*/)
{
    m_ConverTabWidget->selectRow(row);
    m_OperatorTabWidget->selectRow(row);
    qDebug() << "Src" ;
//    disconnect(m_ConverTabWidget,0,this,0);
}


void PublishManager::selectConverTable(int row/*,int column*/)
{
    m_SrcTabWidget->selectRow(row);
    m_OperatorTabWidget->selectRow(row);
    qDebug() << "ConverPressed" ;
//    disconnect(m_SrcTabWidget,0,this,0);
}

void PublishManager::selectOperatorTable(int row/*,int column*/)
{
    m_SrcTabWidget->selectRow(row);
    m_ConverTabWidget->selectRow(row);
    qDebug() << "Operator" ;
    //    disconnect(m_SrcTabWidget,0,this,0);
}

void PublishManager::viewUnionRegulations()
{
//    QDialog *unionRegulation = new QDialog(0);

//    unionRegulation->setWindowTitle(QStringLiteral("查看群规则"));
//    unionRegulation->show();
//    MyDialog *myDlg = new MyDialog(0);
//    myDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    myDlg->setWindowOpacity(0.99);
//    myDlg->resize(300,400);
//    myDlg->setTitle(QStringLiteral("查看群规则"));
//    myDlg->exec();
}
