#include "applywidget.h"
#include "ui_applywidget.h"

ApplyWidget::ApplyWidget(QWidget *parent) :
    Widget(parent),
    ui(new Ui::ApplyWidget)
{
    ui->setupUi(this);
    this->setTitle(QStringLiteral("使用实例"));
    this->setMinimumSize(600,400);

    this->setZoom(true);

}

ApplyWidget::~ApplyWidget()
{
    delete ui;
}
