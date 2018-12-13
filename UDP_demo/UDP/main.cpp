#include "widget.h"
#include "otherudp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    OtherUdp w1;
    w1.show();

    return a.exec();
}
