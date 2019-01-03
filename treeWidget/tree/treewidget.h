#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>

namespace Ui {
class treeWidget;
}

class treeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit treeWidget(QWidget *parent = 0);
    ~treeWidget();

private:
    Ui::treeWidget *ui;
};

#endif // TREEWIDGET_H
