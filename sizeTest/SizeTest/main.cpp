#include "widget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(400,300);
    w.move(200,100);
    w.show();

    int x = w.x();
    qDebug("x: %d",x);
    int y = w.y();
    qDebug("y: %d",y);

    QRect geometry = w.geometry();
    QRect frame = w.frameGeometry();
    qDebug() << "geometry:" << geometry << "frame:" << frame;
    return a.exec();
}

/*
 * x: 200
   y: 100
   geometry: QRect(208,130 400x300) frame: QRect(200,100 416x338)
*/
