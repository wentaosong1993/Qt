#include "passwordmode.h"
#include "passwordinput.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    PasswordMode w;
//    w.show();

    passwordInput input;
    input.show();


    return a.exec();
}
