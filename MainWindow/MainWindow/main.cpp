#include "mainwindow.h"
#include <QApplication>
#include "connectdlg.h"
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    ConnectDlg dialog;

    if(dialog.exec() != QDialog::Accepted)
    {
        return -1;
    }

    QFile *carDetails = new QFile("./attribs.xml");
    MainWindow window("factory","car",carDetails);
    window.show();

    return a.exec();
}
