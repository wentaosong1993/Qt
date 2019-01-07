#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
//    tableWidget = new QTableWidget(12, 3, this);
//     resize(400,300);
    resize(this->width(),this->height());
     tableWidget = new QTableWidget(this);
     tableWidget->resize(this->width(),this->height());
     tableWidget->setRowCount(10);
     tableWidget->setColumnCount(5);
     tableWidget->setHorizontalHeaderLabels(QStringList() << "a" << "b" << "c" << "d");
     tableWidget->setVerticalHeaderLabels(QStringList() << "A" << "B" << "C" << "D");
//     tableWidget->horizontalHeader()->setStretchLastSection(true);
//     tableWidget->horizontalHeader()
     tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
     tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
     tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
     tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
}

TableWidget::~TableWidget()
{

}
