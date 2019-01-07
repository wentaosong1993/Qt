#include "passwordmode.h"

PasswordMode::PasswordMode(QWidget *parent) :
    QLineEdit(parent)
{
    this->setMaxLength(8);
    this->setEchoMode(QLineEdit::Password);
}

PasswordMode::~PasswordMode()
{
}
