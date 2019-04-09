

#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QWidget>
#include "lighter.h"
#include <QWidget>


QT_BEGIN_NAMESPACE
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE


class TextFinder : public QWidget
{
    Q_OBJECT

public:
    TextFinder(QWidget *parent = 0);
	void setOriginText(QString str);


private slots:
    void on_findButton_clicked();

private:
    QWidget* loadUiFile();
    void loadTextFile();

    QPushButton *ui_findButton = nullptr;
    QTextEdit *ui_textEdit = nullptr;
    QLineEdit *ui_lineEdit = nullptr;
	Highlighter *m_lighter = nullptr;
	QString m_originText = QString("");
    //bool isFirstTime;
};
//! [0]

    QPushButton *ui_findButton;
    QTextEdit *ui_textEdit;
    QLineEdit *ui_lineEdit;
    bool isFirstTime;
};
#endif
