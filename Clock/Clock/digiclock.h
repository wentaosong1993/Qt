#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>
#include <QMouseEvent>
#include <QPoint>

class DigiClock : public QLCDNumber
{
public:
    DigiClock(QWidget *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public slots:
    void showTime();
private:
    QPoint dragPosition; //保存鼠标点相对电子时钟窗体左上角的偏移值
    bool showColon; //用于显示时间时是否显示"."
};

#endif // DIGICLOCK_H
