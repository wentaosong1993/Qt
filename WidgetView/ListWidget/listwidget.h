#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = 0);
    ~ListWidget();

public slots:
//    void printCurrentRow(int row);
      void printCurrentRow(QListWidgetItem* item);

private:
    Ui::ListWidget *ui;
};

#endif // LISTWIDGET_H
