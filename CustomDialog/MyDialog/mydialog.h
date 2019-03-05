
#include "shadow.h"
#include <QDialog>

#define ZOOM_PADDING 2

class  CJPDialogBase : public QDialog
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

    CJPDialogBase(QWidget *parent = NULL);
    ~CJPDialogBase();

    void setFrameTitleVisible(bool visible);
    void setZoom(bool bZoom/*, int nMinWidth = 0, int nMinHeight = 0*/);
    void setSize(int iWidth, int iHeight);
    void resetMinimumSize(int minw, int minh);
    void setTitle(const QString& strTitle);
    QWidget* getParent();
    QWidget* getClose();
    void ShowMinAndMaxButton(bool show);
protected slots:
    void setDlgMin();
    void setDlgMax();

protected:
    bool event(QEvent *event);
    bool eventFilter(QObject *watched, QEvent * event);
    bool nativeEvent(const QByteArray & eventType, void * message, long * result);
    void getRegion(const QPoint&cursorGlobalPoint);

protected:
    QScopedPointer<CBaseContrlImpl>		m_baseContrlImpl;
    CShadow     m_shadowWnd;
    bool        m_bDrag;
    QPoint      m_DragPosition;

    bool		m_bZoom;
    Direction	m_direction;

    bool m_bMax;
    bool m_ShowMinAndMax;
};

