﻿#ifndef PUBLISHMANAGER_H
#define PUBLISHMANAGER_H

#include <QWidget>
#include <QTableWidget>
#include <QCheckBox>

namespace Ui {
class PublishManager;
}

class PublishManager : public QWidget
{
    Q_OBJECT

public:
    explicit PublishManager(QWidget *parent = 0);
    ~PublishManager();

    void initWindow();

private:
    Ui::PublishManager *ui;

    QTableWidget *m_SrcTabWidget = nullptr;
    QTableWidget *m_ConverTabWidget = nullptr;
    QTableWidget *m_OperatorTabWidget = nullptr;


    QCheckBox *m_SelectAllButton = nullptr;
};

#endif // PUBLISHMANAGER_H
