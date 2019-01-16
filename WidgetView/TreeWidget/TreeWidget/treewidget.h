#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace Ui {
class TreeWidget;
}

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = 0);
    ~TreeWidget();

public slots:
    void printSlot(QTreeWidgetItem *,int col);

private:
    Ui::TreeWidget *ui;
};

#endif // TREEWIDGET_H
