#include "mytcpserver.h"
#include "mytcpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTcpServer w;
    w.show();

    MyTcpClient w2;
    w2.show();

    return a.exec();
}
