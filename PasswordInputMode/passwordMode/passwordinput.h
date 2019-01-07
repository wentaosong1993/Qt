#ifndef PASSWORDINPUT_H
#define PASSWORDINPUT_H

#include <QWidget>

namespace Ui {
class passwordInput;
}

class passwordInput : public QWidget
{
    Q_OBJECT

public:
    explicit passwordInput(QWidget *parent = 0);
    ~passwordInput();

private:
    Ui::passwordInput *ui;
};

#endif // PASSWORDINPUT_H
