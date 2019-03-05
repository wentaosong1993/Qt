#include "tooltip.h"

ToolTip::ToolTip(ArrowDirection ad, const QString &text, QWidget *parent)
    : QWidget(parent)
{

}

ToolTip::~ToolTip()
{

}

void ToolTip::setArrow(ArrowDirection ad)
{
    m_ArrowDirection = ad;
    UpdateSize();
}

void ToolTip::setFont(const QFont &font)
{
    m_Font = font;
    UpdateSize();
}

void ToolTip::setText(const QString &text)
{
    m_Text = text;
    UpdateSize();
}

void ToolTip::setMaxWidth(int w)
{
    m_MaxWidth = w;
    if(m_MaxWidth < 100)
    {
        m_MaxWidth = 100;
    }
    UpdateSize();
}

void ToolTip::showTip(QPoint pos)
{
    QPoint pt;
    switch (m_ArrowDirection)
    {
    case AD_LEFT:
        pt.setX(pos.x());
        pt.setY(pos.y() - height() / 2);
        break;
    case AD_RIGHT:
        pt.setX(pos.x() - width());
        pt.setY(pos.y() - height() / 2);
        break;
    case AD_TOP:
        pt.setX(pos.x() - width() / 2);
        pt.setY(pos.y());
        break;
    case AD_BOTTOM:
        pt.setX(pos.x() - width() / 2);
        pt.setY(pos.y() - height());
        break;
    default: break;
    }
    move(pt);
    show();
}

void ToolTip::InitWindow()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//无边框,最顶层,工具窗口
    setAttribute(Qt::WA_TranslucentBackground);//设置小窗口部件为半透明
    m_Font.setFamily(QString::fromLocal8Bit("微软雅黑"));
    m_Font.setPixelSize(12);
    setFixedSize(60, 30);
}

void ToolTip::UpdateSize()
{
    QFontMetrics fm(m_Font);
    int w = fm.width(m_Text);
    int h = fm.height();
    if (w > m_MaxWidth)
    {
        int row = ceil((float)w / m_MaxWidth);
        w = m_MaxWidth;
        h *= row;
    }
    switch (m_ArrowDirection)
    {
    case AD_LEFT:
    case AD_RIGHT:
        w += m_HMargin * 2 + m_ArrowSize;
        h += m_VMargan * 2;
        break;
    case AD_TOP:
    case AD_BOTTOM:
        w += m_HMargin * 2;
        h += m_VMargan * 2 + m_ArrowSize;
        break;
    default: break;
    }

    setFixedSize(w, h);
}

void ToolTip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.save();

    painter.setRenderHint(QPainter::Antialiasing, true);

    int w = width();
    int h = height();
    QPointF points[3];
    QRectF contentRc;
    switch (m_ArrowDirection)
    {
    case AD_LEFT:
        points[0] = QPointF(m_ArrowSize, h / 2 - m_ArrowSize);
        points[1] = QPointF(0, h / 2);
        points[2] = QPointF(m_ArrowSize, h / 2 + m_ArrowSize);
        contentRc.setRect(m_ArrowSize, 0, w - m_ArrowSize, h);
        break;
    case AD_TOP:
        points[0] = QPointF(w / 2 - m_ArrowSize, m_ArrowSize);
        points[1] = QPointF(w / 2, 0);
        points[2] = QPointF(w / 2 + m_ArrowSize, m_ArrowSize);
        contentRc.setRect(0, m_ArrowSize, w, h - m_ArrowSize);
        break;
    case AD_RIGHT:
        points[0] = QPointF(w - m_ArrowSize, h / 2 - m_ArrowSize);
        points[1] = QPointF(w, h / 2);
        points[2] = QPointF(w - m_ArrowSize, h / 2 + m_ArrowSize);
        contentRc.setRect(0, 0, w - m_ArrowSize, h);
        break;
    case AD_BOTTOM:
        points[0] = QPointF(w / 2 - m_ArrowSize, h - m_ArrowSize);
        points[1] = QPointF(w / 2, h);
        points[2] = QPointF(w / 2 + m_ArrowSize, h - m_ArrowSize);
        contentRc.setRect(0, 0, w, h - m_ArrowSize);
        break;
    default: break;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 175));
    painter.drawRoundedRect(contentRc, 3, 3);
    painter.drawPolygon(points, 3);

    QRectF textRc(contentRc.x() + m_HMargin, contentRc.y() + m_VMargan, contentRc.width() - m_HMargin * 2, contentRc.height() - m_VMargan * 2);
    painter.setFont(m_Font);
    painter.setPen(Qt::white);
    painter.drawText(textRc, m_Text, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    painter.restore();
}
