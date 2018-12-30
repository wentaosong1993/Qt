#include "tryoutofqlineedit.h"
#include "ui_tryoutofqlineedit.h"
#include <QDebug>

TryOutOfQLineEdit::TryOutOfQLineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TryOutOfQLineEdit)
{
    ui->setupUi(this);
    QRegExp regxData("^(\\d|10)(\\.\\d\\d)?$");
    QValidator *validatorData = new QRegExpValidator(regxData, this);
    ui->lineEdit->setValidator(validatorData);

//    connect(ui->lineEdit,&QLineEdit::editingFinished,this,&TryOutOfQLineEdit::PrintOutput);
    connect(ui->lineEdit,SIGNAL(editingFinished()),this,SLOT(PrintOutput()));

    ui->pushButton->setFocus();
    ui->pushButton->setAutoDefault(true);
    ui->pushButton->setDefault(true);

    connect(ui->pushButton,&QPushButton::clicked,this,&TryOutOfQLineEdit::PrintOutput);
}

TryOutOfQLineEdit::~TryOutOfQLineEdit()
{
    delete ui;
}

void TryOutOfQLineEdit::PrintOutput()
{
    qDebug() << "execute once!";
}
