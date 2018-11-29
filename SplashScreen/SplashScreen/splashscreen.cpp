#include "splashscreen.h"
#include <QTextEdit>
#include <QThread>

SplashScreen::SplashScreen(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Splash Example");
    QTextEdit *edit = new QTextEdit;
    edit->setText("Splash Example!");
    setCentralWidget(edit);
    resize(600,450);
    QThread::sleep(1);

}

SplashScreen::~SplashScreen()
{

}
