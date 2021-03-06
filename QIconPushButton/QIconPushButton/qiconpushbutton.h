﻿#ifndef QICONPUSHBUTTON_H
#define QICONPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>


class QIconPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QIconPushButton(QWidget *parent = 0);
    ~QIconPushButton();

//    void setText(QString str);

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
private:
    QLabel *m_label;
    QLabel *m_icon;
    bool isIconLeft;

    QHBoxLayout *hLayout;
};

#endif // QICONPUSHBUTTON_H
