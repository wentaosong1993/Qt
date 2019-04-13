#include "widget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

class Widget::CBaseContrlImpl
{
public:
    QVBoxLayout *vlayout_main = nullptr;

    QFrame *frame_title = nullptr;
    QGridLayout *glayout_title = nullptr;
    QLabel *label_title = nullptr;
    QPushButton *btn_close = nullptr;
    QPushButton *btn_min = nullptr;
    QPushButton *btn_max = nullptr;

    QFrame *frame_content = nullptr;

    void setupUi(QWidget* parent)
    {
        frame_title = new QFrame(parent);
        frame_title->setObjectName("dialogbase_titleBackground");
        frame_title->setStyleSheet("QFrame{min-height:36px;max-height:36px;border-top:0px solid #d3dce6;} \
                                    QFrame{border-right:0px solid #d3dce6;border-bottom:0px;border-left:0px solid #d3dce6;} \
                                    QFrame{background-color:#55b7ff;}");

        label_title = new QLabel(frame_title);
        label_title->setObjectName("dialogbase_titleText");
        label_title->setStyleSheet("QLabel{background-color:transparent;border:0px;font:16px;color:#ffffff;}");

        btn_min = new QPushButton(frame_title);
        btn_min->setCursor(Qt::PointingHandCursor);
        btn_min->setObjectName("dialogbase_btnMin");
        btn_min->setToolTip(QString::fromLocal8Bit("最小化"));
        btn_min->setStyleSheet("QPushButton{width:36px;height:36px;border:0px;background-color:transparent;border-image:url(:/Resources/min_nor.png);} \
                                QPushButton:hover{border:0px;background-color:transparent;border-image:url(:/Resources/min_hover.png);} \
                                QPushButton:pressed{border:0px;background-color:transparent;border-image:url(:/Resources/min_press.png)}");

        btn_max = new QPushButton(frame_title);
        btn_max->setCursor(Qt::PointingHandCursor);
        btn_max->setObjectName("dialogbase_btnMax");
        btn_max->setToolTip(QString::fromLocal8Bit("最大化"));
        btn_max->setCheckable(true);
        btn_max->setStyleSheet("QPushButton{width:36px;height:36px;border:0px;background-color:transparent;border-image:url(:/Resources/max_nor.png);} \
                                QPushButton:hover{border:0px;background-color:transparent;border-image:url(:/Resources/max_hover.png);} \
                                QPushButton:pressed{border:0px;background-color:transparent;border-image:url(:/Resources/max_press.png)}");

        btn_close = new QPushButton(frame_title);
        btn_close->setCursor(Qt::PointingHandCursor);
        btn_close->setObjectName("dialogbase_btnClose");
        btn_close->setToolTip(QString::fromLocal8Bit("关闭"));
        btn_close->setStyleSheet("QPushButton{width:36px;height:36px;border:0px;background-color:transparent;border-image:url(:/Resources/close_nor.png);} \
                                  QPushButton:hover{border:0px;background-color:transparent;border-image:url(:/Resources/close_hover.png);} \
                                  QPushButton:pressed{border:0px;background-color:transparent;border-image:url(:/Resources/close_press.png)}");

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

Widget::Widget(QWidget *parent) :
    m_baseContrlImpl(new CBaseContrlImpl),
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinMaxButtonsHint);
    setWindowOpacity(0.99);
    setAttribute(Qt::WA_AlwaysShowToolTips);
    m_baseContrlImpl->setupUi(this);
    this->installEventFilter(this);
    m_baseContrlImpl->frame_title->installEventFilter(this);
    m_baseContrlImpl->frame_content->installEventFilter(this);
    m_bDrag = false;
    m_direction = NONE;
    m_bMax = false;
    this->setMinimumSize(600,400);

    this->setTitle(QStringLiteral("定制弹框-支持鼠标拖动以及缩放"));
    this->setWindowIcon(QIcon(":/Resources/mml_logo.png"));

    connect(m_baseContrlImpl->btn_min, SIGNAL(clicked()), this, SLOT(setDlgMin()));
    connect(m_baseContrlImpl->btn_max, SIGNAL(clicked()), this, SLOT(setDlgMax()));
    connect(m_baseContrlImpl->btn_close, SIGNAL(clicked()), this, SLOT(close()));

    this->setZoom(true);//开启鼠标拖动缩放的功能
}

Widget::~Widget()
{
}

void Widget::setZoom(bool bZoom)
{
    m_bZoom = bZoom;
    this->setMouseTracking(bZoom);
    m_baseContrlImpl->frame_title->setMouseTracking(bZoom);
    m_baseContrlImpl->frame_content->setMouseTracking(bZoom);
}

void Widget::getRegion(const QPoint &cursorGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();//获取内部窗口矩形,不含外部窗口框架的边距设置数据
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

void Widget::setTitle(const QString &strTitle)
{
    m_baseContrlImpl->label_title->setText(strTitle);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
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
                        //拖动时如果是最大化,先最小化窗口
                        m_DragPosition = mouseEvent->globalPos() - this->frameGeometry().topLeft();
                        if(m_bMax)
                        {
                             setNormal();
                        }
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
            if (m_bMax)
            {
                setDlgMin();
            }
            else
            {
                setDlgMax();
            }
            break;
        }
        default:
            break;
        }

        return __super::eventFilter(watched, event);
}

void Widget::setDlgMin()
{
    this->setWindowState(Qt::WindowMinimized);
}

void Widget::setDlgMax()
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

void Widget::setNormal()
{
    this->setWindowState(Qt::WindowNoState);
}
