#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>


namespace Ui {
class widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QMenu *manageMenu;
    QMenu *passwordMenu;

    QAction *manageAction;
    QAction *chartAction;
    QAction *quitAction;

private slots:
    void on_manageMenu_clicked();
    void on_chartMenu_clicked();
    void on_quitMenu_clicked();

private:
    Ui::widget *ui;

    void createMenuBar();
};

#endif // WIDGET_H
