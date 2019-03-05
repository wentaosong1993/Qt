/*
 * problem: there is a problem,which  can't be shown (the promoted widget);
 * to be continued to solve;
 * date: 2019,03,05
 * author: wentaosong
*/
#include "stylepushbutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	StylePushButton pushbutton;
	pushbutton.show();
    pushbutton.raise();
    return a.exec();
}
