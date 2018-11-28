#ifndef CONTACT_H
#define CONTACT_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>

class Contact : public QWidget
{
    Q_OBJECT
public:
    Contact(QWidget *parent = 0);
private:
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *addrLabel;
    QLineEdit *addrLineEdit;
    QLabel *codeLabel;
    QLineEdit *codeLineEdit;
    QLabel *movieLabel;
    QLineEdit *movieLineEdit;
    QCheckBox *movieTelCheckBox;
    QLabel *protelLabel;
    QLineEdit *proTelLineEdit;
    QGridLayout *mainLayout;

};

#endif // CONTACT_H
