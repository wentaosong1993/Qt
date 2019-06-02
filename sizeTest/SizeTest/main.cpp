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

    qDebug() << "pos:" << w.pos() << endl << "rect:" << w.rect()
             << endl << "size:" << w.size() << endl << "width:"
             << w.width() << endl << "height:" << w.height();
    //宽、高、大小不包括窗口的外框和菜单栏
    return a.exec();
}

/*
 * x: 200
   y: 100
   geometry: QRect(208,130 400x300) frame: QRect(200,100 416x338)
   pos: QPoint(200,100)
   rect: QRect(0,0 400x300)
   size: QSize(400, 300)
   width: 400
   height: 300
*/
