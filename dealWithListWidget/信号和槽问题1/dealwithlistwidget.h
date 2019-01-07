#ifndef DEALWITHLISTWIDGET_H
#define DEALWITHLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QMainWindow>

namespace Ui {
class DealWithListWidget;
}

class DealWithListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DealWithListWidget(QWidget *parent = 0);
    ~DealWithListWidget();

    void dealWithData();

private:
    Ui::DealWithListWidget *ui;
    QStringList strList;
    QMainWindow w1;
    QMainWindow w2;
    QMainWindow w3;
};

#endif // DEALWITHLISTWIDGET_H
