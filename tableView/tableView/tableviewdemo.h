#ifndef TABLEVIEWDEMO_H
#define TABLEVIEWDEMO_H

#include <QWidget>
#include <QTableView>
#include "tablemodel.h"

class TableViewDemo : public QWidget
{
    Q_OBJECT

public:
    TableViewDemo(QWidget *parent = 0);
    ~TableViewDemo();

private:
    TableModel *tableModel = nullptr;

    QTableView *tableView = nullptr;
};

#endif // TABLEVIEWDEMO_H
