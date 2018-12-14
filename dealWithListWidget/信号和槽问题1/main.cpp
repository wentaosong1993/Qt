#include "dealwithlistwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DealWithListWidget w;
    w.show();

    return a.exec();
}
