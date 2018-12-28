#ifndef PASSWORDMODE_H
#define PASSWORDMODE_H

#include <QWidget>
#include <QLineEdit>

class PasswordMode : public QLineEdit
{
    Q_OBJECT

public:
    explicit PasswordMode(QWidget *parent = 0);
    ~PasswordMode();

};

#endif // PASSWORDMODE_H
