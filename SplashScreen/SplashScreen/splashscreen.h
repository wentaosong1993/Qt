#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QMainWindow>
#include <QSplashScreen>

class SplashScreen : public QMainWindow
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = 0);
    ~SplashScreen();
};

#endif // SPLASHSCREEN_H
