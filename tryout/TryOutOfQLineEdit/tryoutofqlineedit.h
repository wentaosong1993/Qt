#ifndef TRYOUTOFQLINEEDIT_H
#define TRYOUTOFQLINEEDIT_H

#include <QWidget>

namespace Ui {
class TryOutOfQLineEdit;
}

class TryOutOfQLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TryOutOfQLineEdit(QWidget *parent = 0);
    ~TryOutOfQLineEdit();

public slots:
    void PrintOutput();

private:
    Ui::TryOutOfQLineEdit *ui;
};

#endif // TRYOUTOFQLINEEDIT_H
