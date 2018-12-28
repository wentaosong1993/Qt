#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>

namespace Ui {
class mybutton;
}

class mybutton : public QWidget
{
    Q_OBJECT

public:
    explicit mybutton(QWidget *parent = 0);
    ~mybutton();

private:
    Ui::mybutton *ui;
};

#endif // MYBUTTON_H
