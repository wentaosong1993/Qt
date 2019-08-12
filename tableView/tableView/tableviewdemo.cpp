#include "tableviewdemo.h"

TableViewDemo::TableViewDemo(QWidget *parent)
    : QWidget(parent)
{
     tableView = new QTableView(this);
     tableModel = new TableModel(0);
     tableModel->setHeaderData(0,Qt::Horizontal,"Column1", Qt::EditRole);
     tableModel->setHeaderData(1,Qt::Horizontal,"Column2", Qt::EditRole);

     tableModel->setHeaderData(0,Qt::Vertical,"Row1", Qt::EditRole);
     tableModel->setHeaderData(1,Qt::Vertical,"Row2", Qt::EditRole);

//    QModelIndex curIndex = QModelIndex();

     tableView->setModel(tableModel);
     tableView->show();


}

TableViewDemo::~TableViewDemo()
{

}
