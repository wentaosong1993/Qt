#include "publishmanager.h"
#include "ui_publishmanager.h"
#include <QDebug>


PublishManager::PublishManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PublishManager)
{
    ui->setupUi(this);
    ui->tableWidget_2->setColumnWidth(0, 330);
    ui->tableWidget_2->setColumnWidth(2, 210);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    QString tabStyle = "QTableWidget{border:none;color:#282828;	gridline-color:#D3DCE6;		\
        background-color:transparent; alternate-background-color: #282828;		\
        selection-color:black;selection-background-color:#C6E3F8;border:0px;}		\
        .QHeaderView{color: #282828;font: bold 12px;background-color:transparent;border-left:1px solid #D3DCE6;	\
        border-top:1px solid #D3DCE6;border-right:0px solid #d3dce6;border-bottom:1px solid #d3dcet;}	\
        .QHeaderView::section{font:12px;color:#282828;background-color:#E7F1FC;text-align:center;		\
        border-right:1px solid #d3dce6;border-bottom:1px solid #d3dce6;border-left:0px solid #D3DCE6;border-top:0px solid #d3dce6;min-height:30px;}";

    QString srcStyle = "QTableWidget{border:none;color:#282828;	gridline-color:#D3DCE6;		\
        background-color:transparent; alternate-background-color: #282828;		\
        selection-color:black;selection-background-color:#C6E3F8;border:0px;}		\
        .QHeaderView{color: #282828;font: bold 12px;background-color:transparent;border-left:0px;	\
        border-top:1px solid #D3DCE6;border-right:0px;border-bottom:0px;}	\
        .QHeaderView::section{font:12px;color:#282828;background-color:#E7F1FC;text-align:center;		\
        border-right:0px;border-bottom:1px solid #d3dce6;border-left:1px solid #D3DCE6;border-top:0px solid #d3dce6;min-height:30px;}";


    m_SrcTabWidget = new QTableWidget(ui->tableWidget_2);
    m_SrcTabWidget->verticalHeader()->setVisible(false);
    m_SrcTabWidget->setStyleSheet(srcStyle);
    m_SrcTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_SrcTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_SrcTabWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_SrcTabWidget->setFocusPolicy(Qt::NoFocus);
    m_SrcTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_SrcTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //表头
    const QStringList orginalHead = QStringList() << QString() << QStringLiteral("品牌")
        << QStringLiteral("物料号") << QStringLiteral("产地");
    m_SrcTabWidget->setColumnCount(orginalHead.size());
    m_SrcTabWidget->setHorizontalHeaderLabels(orginalHead);

    m_SrcTabWidget->setColumnWidth(0, 30);
    m_SrcTabWidget->setColumnWidth(3, 100);
    m_SrcTabWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_SrcTabWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    m_SelectAllButton = new QCheckBox(m_SrcTabWidget);
    m_SelectAllButton->setStyleSheet("QCheckBox{font:14px;color:#282828;spacing:10px;margin-left:6px;background-color:#E7F1FC;}		\
        QCheckBox::indicator:checked{height:16px; width:16px;border-image:url(:/Resources/opt_set.png) }		\
        QCheckBox::indicator:checked:hover{height:16px; width:16px; border-image:url(:/Resources/opt_set_hover.png) }		\
        QCheckBox::indicator:!checked{height:16px; width:16px; border-image:url(:/Resources/opt_nor.png) }		\
        QCheckBox::indicator:!checked:hover{height:16px; width:16px; border-image:url(:/Resources/opt_nor_hover.png) };		\
        QCheckBox::indicator:disabled:{height:16px; width:16px; border-image:url(:/Resources/opt_set_hover.png)}; ");
    m_SelectAllButton->setGeometry(1, 1, 28, 28);


    //转换数据表
    m_ConverTabWidget = new QTableWidget(ui->tableWidget_2);
    m_ConverTabWidget->verticalHeader()->setVisible(false);
//    m_ConverTabWidget->setStyleSheet(srcStyle);
    m_ConverTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ConverTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ConverTabWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ConverTabWidget->setFocusPolicy(Qt::NoFocus);
    m_ConverTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ConverTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_ConverTabWidget->horizontalHeader()->setStretchLastSection(true);//关键

    QStringList convHead = QStringList() << QStringLiteral("品牌 *") << QStringLiteral("商品号 *")
        << QStringLiteral("产地") << QStringLiteral("商品名称 *") << QStringLiteral("OE号")
        << QStringLiteral("替换号") << QStringLiteral("质保") << QStringLiteral("单位")
        << QStringLiteral("规格及备注");
    m_ConverTabWidget->setColumnCount(convHead.size());
    m_ConverTabWidget->setHorizontalHeaderLabels(convHead);

    m_OperatorTabWidget = new QTableWidget(ui->tableWidget_2);
    m_OperatorTabWidget->verticalHeader()->setVisible(false);
    m_OperatorTabWidget->setStyleSheet(tabStyle);
    m_OperatorTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_OperatorTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
    m_OperatorTabWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    m_OperatorTabWidget->setFocusPolicy(Qt::NoFocus);//去掉选中虚线框
    m_OperatorTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_OperatorTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_OperatorTabWidget->horizontalHeader()->setStretchLastSection(true);//关键


    //表头
    QStringList operatorHead = QStringList() << QStringLiteral("状态") << QStringLiteral("操作");
    m_OperatorTabWidget->setColumnCount(operatorHead.size());
    m_OperatorTabWidget->setHorizontalHeaderLabels(operatorHead);

    ui->tableWidget_2->setCellWidget(0, 0, m_SrcTabWidget);
    ui->tableWidget_2->setCellWidget(0, 1, m_ConverTabWidget);
    ui->tableWidget_2->setCellWidget(0, 2, m_OperatorTabWidget);

    initWindow();
}

PublishManager::~PublishManager()
{
    delete ui;
}

void PublishManager::initWindow()
{
    m_ConverTabWidget->clearContents();
    m_ConverTabWidget->setRowCount(0);

    m_ConverTabWidget->setColumnCount(10);
    m_ConverTabWidget->setRowCount(4);
    QWidget *pItemWidget = new QWidget(this);
    for(int i = 0; i < 10;i++) //行
    {
        for(int j = 1 ; j < 4; j++)//列
        {
            m_ConverTabWidget->setCellWidget(i,j,pItemWidget);
            m_ConverTabWidget->setItem(i,j,new QTableWidgetItem("111"));
        }
    }
    qDebug() << m_ConverTabWidget->columnCount();
}
