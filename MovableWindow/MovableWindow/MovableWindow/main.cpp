#include "movable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Movable w;
    w.show();

    return a.exec();
}
