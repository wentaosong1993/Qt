#include "widget.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

//    QWidget *w = new QWidget(this);
//    w->show();

//    Widget *w = new Widget;
//    w->setAttribute(Qt::WA_DeleteOnClose);
//    w->show();

//program crash!
//    QLabel label("123");//栈上分配
//    QWidget view;
//    label.setParent(&view);
//    view.show();

    QWidget view;//view后析构
    QLabel label("123");//label先析构
    label.setParent(&view);
    view.show();

    return a.exec();
}
