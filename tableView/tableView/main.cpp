#include "tableviewdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TableViewDemo w;
    w.show();

    return a.exec();
}
