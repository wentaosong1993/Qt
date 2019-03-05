#ifndef STYLEPUSHBUTTON_H
#define STYLEPUSHBUTTON_H

#include <QWidget>

namespace Ui {
class StylePushButton;
}

class StylePushButton : public QWidget
{
    Q_OBJECT

public:
    explicit StylePushButton(QWidget *parent = 0);
    ~StylePushButton();

private:
    Ui::StylePushButton *ui;
};

#endif // STYLEPUSHBUTTON_H
