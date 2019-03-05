#ifndef MOVABLE_H
#define MOVABLE_H

#include <QDialog>
#include <QPoint>

class Movable : public QDialog
{
    Q_OBJECT

public:
    Movable(QWidget *parent = 0);
    ~Movable();

protected:
    bool eventFilter(QObject *watched, QEvent *event); //事件过滤器
private:
    bool m_drag;
    QPoint m_DragPosition;
};

#endif // MOVABLE_H
