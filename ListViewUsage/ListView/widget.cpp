#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_listView = new QListView(this);
    m_standModel = new QStandardItemModel(this);
//    m_listView->setViewMode(QListView::ListMode);//QListView::IconMode
//    m_listModel  = new QStringListModel();
//    QStringList list;
//    list << "a" << "b" << "c";
//    m_listModel->setStringList(list);
//    m_listView->setModel(m_listModel);
//    m_standModel = new QStandardItemModel(this);
//    QStandardItem *item = new QStandardItem("item1");
//    m_standModel->appendRow(item);
//    item = new QStandardItem("item2");
//    m_standModel->appendRow(item);
//    m_listView->setModel(m_standModel);

//    item = new QStandardItem("item3");
//    m_standModel->appendRow(item);
       QStringList strList;
       strList.append("string1");
       strList.append("string2");
       strList.append("string3");
       strList.append("string4");
       strList.append("string5");
       strList.append("string6");
       strList.append("string7");
       strList << "string8";
       strList += "string9";
       int nCount = strList.size();

    for(int i = 0 ;i < nCount;i++)
    {
        QString string =strList.at(i);
        QStandardItem *item = new QStandardItem(string);
        if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, Qt::darkGreen);
            linearGrad.setColorAt(1, Qt::yellow);
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        m_standModel->appendRow(item);
    }
    m_listView->setModel(m_standModel);
    m_listView->setFixedSize(200,150);

    QModelIndex qindex = m_standModel->index(1,0);   //默认选中 index
    m_listView->setCurrentIndex(qindex);

    m_listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

Widget::~Widget()
{

}
