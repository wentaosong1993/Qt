#include "splashscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/1.jpg");
    QSplashScreen splash(pixmap);//设置启动图片，创建一个QSplashScreen对象
    splash.show(); //使程序在显示启动动画的同时任然能响应鼠标等其他事件

    a.processEvents();
    SplashScreen w;
    w.show();

    splash.finish(&w); //在主窗体初始化完成后，结束动画

    return a.exec();
}
