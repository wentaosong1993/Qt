#include "mybutton.h"
#include "ui_mybutton.h"
#include "qiconpushbutton.h"

mybutton::mybutton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mybutton)
{
    ui->setupUi(this);
}

mybutton::~mybutton()
{
    delete ui;
}
