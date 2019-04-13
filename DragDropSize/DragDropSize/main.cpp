#include "widget.h"
#include "applywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Widget w;
//    w.show();

    ApplyWidget w;
    w.show();

    return a.exec();
}
