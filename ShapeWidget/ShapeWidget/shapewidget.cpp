#include "shapewidget.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QDialog(parent)
{
    QPixmap pix;
    pix.load(":/1.png",0,Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    setWindowFlags(Qt::FramelessWindowHint);
    setMask(QBitmap(pix.mask()));
}

ShapeWidget::~ShapeWidget()
{

}

void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button() == Qt::RightButton)
    {
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/1.png"));
}
