#ifndef BASEINFO_H
#define BASEINFO_H


#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

class BaseInfo : public QDialog
{
    Q_OBJECT

public:
    BaseInfo(QWidget *parent = 0);
    ~BaseInfo();
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

#endif // BASEINFO_H
