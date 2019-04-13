#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QScopedPointer>


#define ZOOM_PADDING 2

class Widget : public QWidget
{
    Q_OBJECT
    class CBaseContrlImpl;

    enum Direction
    {
        UP = 0,
        DOWN = 1,
        LEFT,
        RIGHT,
        LEFTTOP,
        LEFTBOTTOM,
        RIGHTBOTTOM,
        RIGHTTOP,
        NONE
    };
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setZoom(bool bZoom);
    void getRegion(const QPoint&cursorGlobalPoint);
    void setTitle(const QString& strTitle);

protected:
    bool eventFilter(QObject *watched, QEvent * event);


protected slots:
    void setDlgMin();
    void setDlgMax();
    void setNormal();

private:
    bool        m_bDrag;
    QPoint      m_DragPosition;

    bool		m_bZoom;
    Direction	m_direction;

    bool		m_bMax;

    QScopedPointer<CBaseContrlImpl>	m_baseContrlImpl;
};

#endif // WIDGET_H
