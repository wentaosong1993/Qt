#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QWidget>
#include <QDialog>
//#include "jpshadow.h"

class MyDialog : public QDialog
{  
    Q_OBJECT
    class CBaseContrlImpl;
    public:
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

        MyDialog(QWidget *parent = Q_NULLPTR);
        ~MyDialog();

        void setZoom(bool bZoom/*, int nMinWidth = 0, int nMinHeight = 0*/);
        void setSize(int iWidth, int iHeight);
        void resetMinimumSize(int minw, int minh);
        void setTitle(const QString& strTitle);
        QWidget* getParent();
        QWidget* getClose();
        void showMinAndMaxButton(bool show);
    protected slots:
        void setDlgMin();
        void setDlgMax();

    protected:
        bool event(QEvent *event);
        bool eventFilter(QObject *watched, QEvent * event);
//        bool nativeEvent(const QByteArray & eventType, void * message, long * result);
        void getRegion(const QPoint&cursorGlobalPoint);

    protected:
        QScopedPointer<CBaseContrlImpl> m_baseContrlImpl;
//        JPShadow	m_shadowWnd;
        bool        m_bDrag;
        QPoint      m_DragPosition;

        bool		m_bZoom;
        Direction	m_direction;

        bool m_bMax;
        bool m_showMinAndMax;
};

#endif // MYDIALOG_H
