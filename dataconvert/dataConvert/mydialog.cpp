#include "mydialog.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>

#define ZOOM_PADDING 2

class MyDialog::CBaseContrlImpl
{
public:
    QVBoxLayout *vlayout_main;

    QFrame *frame_title;
    QGridLayout *glayout_title;
    QLabel *label_title;
    QPushButton *btn_close;
    QPushButton *btn_min;
    QPushButton *btn_max;

    QFrame *frame_content;

    void setupUi(QWidget* parent)
    {
        frame_title = new QFrame(parent);
        frame_title->setObjectName("dialogbase_titleBackground");
        label_title = new QLabel(frame_title);
        label_title->setObjectName("dialogbase_titleText");

        btn_min = new QPushButton(frame_title);
        btn_min->setCursor(Qt::PointingHandCursor);
        btn_min->setObjectName("dialogbase_btnMin");
        btn_min->setToolTip(QString::fromLocal8Bit("最小化"));

        btn_max = new QPushButton(frame_title);
        btn_max->setCursor(Qt::PointingHandCursor);
        btn_max->setObjectName("dialogbase_btnMax");
        btn_max->setToolTip(QString::fromLocal8Bit("最大化"));
        btn_max->setCheckable(true);

        btn_close = new QPushButton(frame_title);
        btn_close->setCursor(Qt::PointingHandCursor);
        btn_close->setObjectName("dialogbase_btnClose");
        btn_close->setToolTip(QString::fromLocal8Bit("关闭"));
        glayout_title = new QGridLayout(frame_title);
        QSpacerItem* hSpacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QSpacerItem* vSpacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        glayout_title->setContentsMargins(10, 0, 0, 0);
        glayout_title->setSpacing(0);
        glayout_title->addWidget(label_title, 0, 0, 2, 1);
        glayout_title->addItem(hSpacerItem1, 0, 1, 2, 1);

        glayout_title->addWidget(btn_min, 0, 2, 1, 1);
        glayout_title->addWidget(btn_max, 0, 3, 1, 1);
        glayout_title->addWidget(btn_close, 0, 4, 1, 1);
        glayout_title->addItem(vSpacerItem1, 1, 2, 1, 1);

        frame_content = new QFrame(parent);
        frame_content->setObjectName("dialogbase_contentBackground");

        vlayout_main = new QVBoxLayout(parent);
        vlayout_main->setContentsMargins(0, 0, 0, 0);
        vlayout_main->setSpacing(0);
        vlayout_main->addWidget(frame_title);
        vlayout_main->addWidget(frame_content);
        vlayout_main->setStretch(1, 1);
    }
};


MyDialog::MyDialog(QWidget *parent)
    :m_baseContrlImpl(new CBaseContrlImpl),QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowOpacity(0.99);
    setAttribute(Qt::WA_AlwaysShowToolTips);
    m_baseContrlImpl->setupUi(this);
    this->installEventFilter(this);
    m_baseContrlImpl->frame_title->installEventFilter(this);
    m_baseContrlImpl->frame_content->installEventFilter(this);

    m_bDrag = false;
    m_direction = NONE;
    m_bMax = false;
    m_showMinAndMax = false;
    connect(m_baseContrlImpl->btn_min, SIGNAL(clicked()), this, SLOT(setDlgMin()));
    connect(m_baseContrlImpl->btn_max, SIGNAL(clicked()), this, SLOT(setDlgMax()));
    connect(m_baseContrlImpl->btn_close, SIGNAL(clicked()), this, SLOT(close()));

    showMinAndMaxButton(false);
}

MyDialog::~MyDialog()
{

}

void MyDialog::setZoom(bool bZoom)
{
    m_bZoom = bZoom;
    //this->setMinimumWidth(nMinWidth);
    //this->setMinimumHeight(nMinHeight);
    this->setMouseTracking(bZoom);
    m_baseContrlImpl->frame_title->setMouseTracking(bZoom);
    m_baseContrlImpl->frame_content->setMouseTracking(bZoom);
}

void MyDialog::setSize(int iWidth, int iHeight)
{
    setFixedSize(iWidth, iHeight);
    resetMinimumSize(iWidth, iHeight);
}

void MyDialog::resetMinimumSize(int minw, int minh)
{
    QRect rect = this->geometry();
    if (rect.width() < minw)
    {
        rect.setWidth(minw);
    }

    if (rect.height() < minh)
    {
        rect.setHeight(minh);
    }

    this->setGeometry(rect);
    this->setMinimumWidth(minw);
    this->setMinimumHeight(minh);
}

void MyDialog::setTitle(const QString &strTitle)
{
    m_baseContrlImpl->label_title->setText(strTitle);
}

QWidget *MyDialog::getParent()
{
    return m_baseContrlImpl->frame_content;
}

QWidget *MyDialog::getClose()
{
    return m_baseContrlImpl->btn_close;
}

void MyDialog::showMinAndMaxButton(bool show)
{
        m_showMinAndMax = show;
        if (!m_showMinAndMax)
        {
            m_baseContrlImpl->btn_min->hide();
            m_baseContrlImpl->btn_max->hide();
        }
        else
        {
            m_baseContrlImpl->btn_min->show();
            m_baseContrlImpl->btn_max->show();
        }
}

void MyDialog::setDlgMin()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MyDialog::setDlgMax()
{
    if (!m_bMax)
    {
        this->setWindowState(Qt::WindowMaximized);
        m_baseContrlImpl->btn_max->setChecked(!m_bMax);
        m_baseContrlImpl->btn_max->setToolTip(QString::fromLocal8Bit("还原"));
    }
    else
    {
        this->setWindowState(Qt::WindowNoState);
        m_baseContrlImpl->btn_max->setChecked(!m_bMax);
        m_baseContrlImpl->btn_max->setToolTip(QString::fromLocal8Bit("最大化"));
    }
    m_bMax = !m_bMax;
}

bool MyDialog::event(QEvent *event)
{
    QEvent::Type type = event->type();
//    if (event->type() == QEvent::WinIdChange)
//    {
//        m_shadowWnd.Create((HWND)winId());
//        m_shadowWnd.SetDarkness(50);
//        m_shadowWnd.SetSharpness(20);
//        m_shadowWnd.SetSize(11);
//        m_shadowWnd.SetPosition(0, 2);
//    }

    return __super::event(event);
}

bool MyDialog::eventFilter(QObject *watched, QEvent *event)
{
    QEvent::Type eType = event->type();
    switch (eType)
    {
    case QEvent::MouseButtonPress:
        if (m_baseContrlImpl->frame_title == watched || m_baseContrlImpl->frame_content == watched || this == watched)
        {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent && mouseEvent->button() == Qt::LeftButton)
            {
                m_bDrag = true;
                if (m_bZoom && m_direction != NONE)
                {
                    this->mouseGrabber();
                }
                else
                {
                    m_DragPosition = mouseEvent->globalPos() - this->frameGeometry().topLeft();
                }

                return true;
            }
        }
        break;

    case QEvent::MouseMove:
        {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent)
            {
                QPoint gloPoint = mouseEvent->globalPos();
                if (!m_bDrag)
                {
                    if (m_bZoom)
                        getRegion(gloPoint);
                }
                else
                {
                    if (!m_bZoom || m_direction == NONE)
                    {
                        QRect rect = QApplication::desktop()->availableGeometry();
                        QPoint topLeftDlgPt = mouseEvent->globalPos() - m_DragPosition;
                        //QPoint bottomRightpt(topLeftDlgPt.x() + width(), topLeftDlgPt.y() + height());
                        if (!rect.contains(topLeftDlgPt)/* || !rect.contains(bottomRightpt)*/)
                        {
                            QPoint topLeftPt = rect.topLeft();
                            //QPoint bottomRightPt = rect.bottomRight();
                            if (topLeftDlgPt.x() < topLeftPt.x())
                            {
                                topLeftDlgPt.setX(topLeftPt.x());
                            }
                            //else if (bottomRightpt.x() > bottomRightPt.x())
                            //{
                            //	topLeftDlgPt.setX(bottomRightPt.x() - width());
                            //}

                            if (topLeftDlgPt.y() < topLeftPt.y())
                            {
                                topLeftDlgPt.setY(topLeftPt.y());
                            }
                            //else if (bottomRightpt.y() > bottomRightPt.y())
                            //{
                            //	topLeftDlgPt.setY(bottomRightPt.y() - height());
                            //}
                        }

                        move(topLeftDlgPt);
                    }
                    else
                    {
                        QRect rect = this->rect();
                        QPoint tl = mapToGlobal(rect.topLeft());
                        QPoint rb = mapToGlobal(rect.bottomRight());

                        QRect rMove(tl, rb);
                        int nWidth = this->minimumWidth();
                        int nHeight = this->minimumHeight();
                        switch (m_direction)
                        {
                        case LEFT:
                            if (rb.x() - gloPoint.x() <= this->minimumWidth())
                                rMove.setX(tl.x());
                            else
                                rMove.setX(gloPoint.x());
                            break;
                        case RIGHT:
                            rMove.setWidth(gloPoint.x() - tl.x());
                            break;
                        case UP:
                            if (rb.y() - gloPoint.y() <= this->minimumHeight())
                                rMove.setY(tl.y());
                            else
                                rMove.setY(gloPoint.y());
                            break;
                        case DOWN:
                            rMove.setHeight(gloPoint.y() - tl.y());
                            break;
                        case LEFTTOP:
                            if (rb.x() - gloPoint.x() <= this->minimumWidth())
                                rMove.setX(tl.x());
                            else
                                rMove.setX(gloPoint.x());
                            if (rb.y() - gloPoint.y() <= this->minimumHeight())
                                rMove.setY(tl.y());
                            else
                                rMove.setY(gloPoint.y());
                            break;
                        case RIGHTTOP:
                            rMove.setWidth(gloPoint.x() - tl.x());
                            rMove.setY(gloPoint.y());
                            break;
                        case LEFTBOTTOM:
                            rMove.setX(gloPoint.x());
                            rMove.setHeight(gloPoint.y() - tl.y());
                            break;
                        case RIGHTBOTTOM:
                            rMove.setWidth(gloPoint.x() - tl.x());
                            rMove.setHeight(gloPoint.y() - tl.y());
                            break;
                        default:
                            break;
                        }

                        this->setGeometry(rMove);
                    }
                }
                return true;
            }
        }
        break;

    case QEvent::MouseButtonRelease:
        {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent && mouseEvent->button() == Qt::LeftButton)
            {
                m_bDrag = false;
                if (m_direction != NONE)
                {
                    this->releaseMouse();
                    this->setCursor(QCursor(Qt::ArrowCursor));
                }

                return true;
            }
        }
        break;
    case QEvent::MouseButtonDblClick:
    {
        //if (m_ShowMinAndMax)
        //{
        //	setDlgMax();
        //}
        break;
    }
    default:
        break;
    }

    return __super::eventFilter(watched, event);
}

//bool MyDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    bool r = __super::nativeEvent(eventType, message, result);
//        MSG *msg = static_cast<MSG *>(message);
//        switch (msg->message)
//        {
//        case WM_KILLFOCUS:
//            m_bDrag = false;
//            break;
//        }

//        return  r = __super::nativeEvent(eventType, message, result);
//}

void MyDialog::getRegion(const QPoint &cursorGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if (tl.x() + ZOOM_PADDING >= x && tl.x() <= x && tl.y() + ZOOM_PADDING >= y && tl.y() <= y)
    {
        // 左上角
        m_direction = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if (x >= rb.x() - ZOOM_PADDING && x <= rb.x() && y >= rb.y() - ZOOM_PADDING && y <= rb.y())
    {
        // 右下角
        m_direction = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (x <= tl.x() + ZOOM_PADDING && x >= tl.x() && y >= rb.y() - ZOOM_PADDING && y <= rb.y())
    {
        //左下角
        m_direction = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - ZOOM_PADDING && y >= tl.y() && y <= tl.y() + ZOOM_PADDING)
    {
        // 右上角
        m_direction = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= tl.x() + ZOOM_PADDING && x >= tl.x())
    {
        // 左边
        m_direction = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - ZOOM_PADDING)
    {
        // 右边
        m_direction = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (y >= tl.y() && y <= tl.y() + ZOOM_PADDING)
    {
        // 上边
        m_direction = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (y <= rb.y() && y >= rb.y() - ZOOM_PADDING)
    {
        // 下边
        m_direction = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        // 默认
        m_direction = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}


