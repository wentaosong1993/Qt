#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>
#include <QListView>
#include <QStandardItemModel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
   QStringListModel *m_listModel;
   QListView *m_listView;
   QStandardItemModel *m_standModel;
};

#endif // WIDGET_H
