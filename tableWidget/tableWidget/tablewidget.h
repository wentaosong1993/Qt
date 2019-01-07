#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = 0);
    ~TableWidget();

private:
    QTableWidget *tableWidget;
};

#endif // TABLEWIDGET_H
