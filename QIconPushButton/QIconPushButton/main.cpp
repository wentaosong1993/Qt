﻿#include "qiconpushbutton.h"
#include <QApplication>
#include "mybutton.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mybutton w1;
    w1.show();


    return a.exec();
}
