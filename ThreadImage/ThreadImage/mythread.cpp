#include "mythread.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::drawImage()
{
    QImage myImage(500,500,QImage::Format_ARGB32);

    QPainter painter(&myImage);
    QPen pen;
    pen.setWidth(5);
    painter.setPen(pen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    QPoint a[] = {
        QPoint(qrand() % 500,qrand() % 500),
        QPoint(qrand() % 500,qrand() % 500),
        QPoint(qrand() % 500,qrand() % 500),
        QPoint(qrand() % 500,qrand() % 500),
        QPoint(qrand() % 500,qrand() % 500),
        };

    painter.drawPolygon(a,5);

    //发送图片
    emit updateImage(myImage);
}
