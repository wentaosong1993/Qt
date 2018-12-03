﻿#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class TimeServer;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void slotShow();

private:
    QLabel *label1;
    QLabel *label2;
    QPushButton *quitBtn;

    TimeServer *timeServer;
    int count;
};

#endif // DIALOG_H
