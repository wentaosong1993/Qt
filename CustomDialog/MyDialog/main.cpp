#include "mydialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    CShadow::Initialize(qWinAppInst());
    QApplication a(argc, argv);
    CJPDialogBase w;
    w.show();

    return a.exec();
}
