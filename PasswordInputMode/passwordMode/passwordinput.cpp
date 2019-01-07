#include "passwordinput.h"
#include "ui_passwordinput.h"

passwordInput::passwordInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::passwordInput)
{
    ui->setupUi(this);
}

passwordInput::~passwordInput()
{
    delete ui;
}
