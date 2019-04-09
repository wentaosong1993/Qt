#include "movable.h"
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QPalette>

Movable::Movable(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->installEventFilter(this);
    this->setBackgroundRole(QPalette::Window);
}

Movable::~Movable()
{

}

bool Movable::eventFilter(QObject *watched, QEvent *event)
{
    QEvent::Type eType = event->type();
    switch (eType) {
    case QEvent::MouseButtonPress:
    {
        if(watched == this)
        {
            QMouseEvent *mouse = dynamic_cast<QMouseEvent *>(event);
            if(mouse->button() == Qt::LeftButton)
            {
                m_drag = true;
                m_DragPosition = mouse->globalPos() - this->frameGeometry().topLeft();
                return true;
            }
        }
    }
        break;
   case QEvent::MouseMove:
    {
        if(watched == this)
        {
            QMouseEvent *mouse = dynamic_cast<QMouseEvent *>(event);
            if(m_drag)
            {
                QRect rect = QApplication::desktop()->availableGeometry();
                QPoint topLeftDlgPt = mouse->globalPos() - m_DragPosition;
                if(!rect.contains(topLeftDlgPt))
                {
                    QPoint topLeftPt = rect.topLeft();
                    if(topLeftDlgPt.x() < topLeftPt.x())
                    {
                        topLeftDlgPt.setX(topLeftPt.x());
                    }

                    if(topLeftDlgPt.y() < topLeftPt.y())
                    {
                        topLeftDlgPt.setY(topLeftPt.y());
                    }
                }
                 this->move(topLeftDlgPt);
                 return true;
            }
        }
    }
        break;
    case QEvent::MouseButtonRelease:
    {
         if(watched == this)
         {
             QMouseEvent *mouse = dynamic_cast<QMouseEvent *>(event);
             if(mouse->button() == Qt::LeftButton)
             {
                 m_drag = false;
             }
             return true;
         }
    }
        break;
    case QEvent::MouseButtonDblClick:
        if(watched == this)
        {
             QMouseEvent *mouse = dynamic_cast<QMouseEvent *>(event);
             if(mouse->button() == Qt::LeftButton)
             {
                 close();
             }
             return true;
        }
    default:
        break;
    }
    return QObject::eventFilter(watched,event);
}
