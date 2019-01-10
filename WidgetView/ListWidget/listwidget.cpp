#include "listwidget.h"
#include "ui_listwidget.h"
#include <QDebug>
#include <QAbstractItemView>

ListWidget::ListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidget->setViewMode(QListView::ListMode);//QListView::IconMode
    ui->listWidget->setFlow(QListView::TopToBottom);//QListView::LeftToRight
    ui->listWidget->setResizeMode(QListView::Adjust); //QListView::Fixed
    QStringList itemText;
    for(int j = 0; j < 26; j++)
    {
        QChar temp = QChar('A' + j);
        itemText.append(QString(temp));
    }

    ui->listWidget->addItems(itemText);
    for(int i = 0 ; i < ui->listWidget->count();i++)
    {
        QListWidgetItem *curItem = ui->listWidget->item(i);
        curItem->setIcon(QIcon(":/img/add-hover.png"));
        curItem->setToolTip(curItem->text());
        curItem->setSizeHint(QSize(this->width(),40));
    }
    ui->listWidget->setStyleSheet("QListWidget {alternate-background-color: yellow;} \
                                  QListView::item:alternate {background: #EEEEEE;} \
                                  QListView::item:selected {border: 1px solid #6a6ea9;} \
                                  QListView::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6a6ea9, stop: 1 #888dd9); } \
                                  QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAFBFE, stop: 1 #DCDEF1);} \
                                  QScrollBar:vertical{max-width: 10px;border: 0px;background:transparent;} \
                                  QScrollBar:handle:vertical {background: lightgrey;border-radius: 5px;} \
                                  QScrollBar:handle:vertical:hover{background: grey;border-radius: 5px;} \
                                  QScrollBar:add-page:vertical,QScrollBar:sub-page:vertical{border: 0px; background: none;} \
                                  QScrollBar:add-line:vertical{border: 0px;height: 0px;} \
                                  QScrollBar:sub-line:vertical{border: 0px;height: 0px;} \
                                  QScrollBar:horizontal{max-height: 10px;border: 0px;background:transparent;} \
                                  QScrollBar:handle:horizontal {background: lightgrey;border-radius: 5px;} \
                                  QScrollBar:handle:horizontal:hover{background: grey;border-radius: 5px;} \
                                  QScrollBar:add-page:horizontal,QScrollBar:sub-page:horizontal{border: 0px; background: none;} \
                                  QScrollBar:add-line:horizontal{border: 0px;height: 0px;} \
                                  QScrollBar:sub-line:horizontal{border: 0px;height: 0px;}");

//    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(printCurrentRow(int)));
      connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(printCurrentRow(QListWidgetItem *)));

}

ListWidget::~ListWidget()
{
    delete ui;
}

//void ListWidget::printCurrentRow(int row)
//{
//    qDebug() << row;
//}

void ListWidget::printCurrentRow(QListWidgetItem* item)
{
    if(item)
    {
        int row = ui->listWidget->row(item);
        qDebug() << row;
    }
}
