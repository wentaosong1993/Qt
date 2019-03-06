#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <QQueue>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    QQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    while (!queue.isEmpty())
    qDebug() << queue.dequeue();
    queue.enqueue(4);
    while (!queue.isEmpty())
    qDebug() << queue.dequeue();

    return a.exec();
}
