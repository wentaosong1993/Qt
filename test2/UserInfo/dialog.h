#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
//#include <QHBoxLayout>
//#include <QVBoxLayout>
#include <QGridLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    QLabel *userNameLabel;
    QLabel *nameLabel;
    QLabel *sexLabel;
    QLabel *departmentLabel;
    QLabel *ageLabel;
    QLabel *otherLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *nameLineEdit;
    QComboBox *sexCombobox;
    QTextEdit *departmentTextEdit;
    QLineEdit *ageLineEdit;
    QGridLayout *leftLayout;

    //右侧
    QLabel *headLabel;
    QLabel *headIconLabel;
    QPushButton *updateHeadBtn;
    QHBoxLayout *topRightLayout;
    QLabel *introductionLabel;
    QTextEdit *introductionTextEdit;
    QVBoxLayout *rightLayout;

    //底部
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QHBoxLayout *buttonLayout;
};

#endif // DIALOG_H
