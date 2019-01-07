#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDesktopServices>
#include <QUrl>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}
