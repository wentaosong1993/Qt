#ifndef DETAIL_H
#define DETAIL_H
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>


class Detail : public QWidget
{
    Q_OBJECT
public:
    Detail(QWidget *parent = 0);
private:
    QLabel *nationalLabel;
    QComboBox *nationalComboBox;
    QLabel *provinceLabel;
    QComboBox *provinceComboBox;
    QLabel *cityLabel;
    QLineEdit *cityLineEdit;
    QLabel *introductLabel;
    QTextEdit *introductTextEdit;
    QGridLayout *mainLayout;
};

#endif // DETAIL_H
