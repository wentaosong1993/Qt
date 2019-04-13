#ifndef APPLYWIDGET_H
#define APPLYWIDGET_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class ApplyWidget;
}

class ApplyWidget : public Widget
{
    Q_OBJECT

public:
    explicit ApplyWidget(QWidget *parent = 0);
    ~ApplyWidget();

private:
    Ui::ApplyWidget *ui;
};

#endif // APPLYWIDGET_H
