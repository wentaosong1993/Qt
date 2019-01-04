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

public slots:
        void setCurrentItemStyle(int row,int column);
private:
    Ui::treeWidget *ui;
};

#endif // TREEWIDGET_H
