﻿#ifndef PALETTE_H
#define PALETTE_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QFrame>
#include <QPalette>

class Palette : public QDialog
{
    Q_OBJECT

public:
    Palette(QWidget *parent = 0);
    ~Palette();

    void createCtrlFrame(); //左边
    void createContentFrame();// 右边
    void fillColorList(QComboBox *);//向颜色下拉列表框中插入颜色的工作

private slots:
    void showWindow();
    void showWindowText();
    void showButton();
    void showButtonText();
    void showBase();
private:
    QFrame *ctrlFrame;
    QLabel *windowLabel;
    QComboBox *windowComboBox;
    QLabel *windowTextLabel;
    QComboBox *windowTextComboBox;
    QLabel *buttonLabel;
    QComboBox *buttonComboBox;
    QLabel *buttonTextLabel;
    QComboBox *buttonTextComboBox;
    QLabel *baseLabel;
    QComboBox *baseComboBox;
    QFrame *contentFrame;
    QLabel *label1;
    QComboBox *comboBox1;
    QLabel *label2;
    QLineEdit *lineEdit2;
    QTextEdit *textEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
};

#endif // PALETTE_H
