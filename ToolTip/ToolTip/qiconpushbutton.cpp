#include "qiconpushbutton.h"
#include "commonfunc.h"
#include <QHBoxLayout>


QIconPushButton::QIconPushButton(QWidget *parent)
{
    InitWidget();
}

QIconPushButton::QIconPushButton(bool bIsIconLeft, QWidget *parent)
{
    InitWidget(bIsIconLeft);
}

QIconPushButton::~QIconPushButton()
{
    if (m_pToolTip)
    {
        delete m_pToolTip;
        m_pToolTip = nullptr;
    }
}

void QIconPushButton::SetIcon(const QString &iconNormal, const QString &iconHover, const QString &iconPressed, int iconsize)
{
    m_IconNormal = iconNormal;
    m_IconHover = iconHover;
    m_IconPressed = iconPressed;
    m_IconSize = iconsize;

    if (m_pLabelIcon)
    {
        m_pLabelIcon->setFixedSize(m_IconSize, m_IconSize);

        QImage icon(m_IconNormal);
        if (icon.height() > m_IconSize)
        {
            icon = GetRoundedRectImage(icon, m_IconSize, m_IconSize, 2, 2);
        }
        m_pLabelIcon->setPixmap(QPixmap::fromImage(icon));
    }
}

void QIconPushButton::SetText(const QString &text, const QString &styleNormal, const QString &styleHover, const QString &stylePressed)
{
    m_TextStyleNormal = styleNormal;
    m_TextStyleHover = styleHover;
    m_TextStylePressed = stylePressed;

    if (text.isEmpty())
    {
        m_pLabelText->hide();
    }
    else
    {
        m_pLabelText->show();
        m_pLabelText->setText(text);
        if (!m_TextStyleNormal.isEmpty())
        {
            m_pLabelText->setStyleSheet(m_TextStyleNormal);
        }
    }
}

void QIconPushButton::setText(const QString &text)
{
    if (text.isEmpty())
    {
        m_pLabelText->hide();
    }
    else
    {
        m_pLabelText->show();
        m_pLabelText->setText(text);
    }
}

void QIconPushButton::SetToolTip(ArrowDirection ad, const QString &tip, int maxW)
{
    m_TipDirection = ad;
    if (!tip.isEmpty())
    {
        if (m_pToolTip == nullptr)
        {
            m_pToolTip = new ToolTip(ad, tip);
            m_pToolTip->hide();
        }
        else
        {
            m_pToolTip->setText(tip);
        }
        m_pToolTip->setMaxWidth(maxW);
    }
}

void QIconPushButton::InitWidget(bool bIsIconLeft)
{
    // 图标
   m_pLabelIcon = new QLabel;
   m_pLabelIcon->setAlignment(Qt::AlignCenter);
   m_pLabelIcon->setStyleSheet("QLabel{background-color:transparent;}");
   // 文字
   m_pLabelText = new QLabel;
   m_pLabelText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
   m_pLabelText->setStyleSheet("QLabel{color:#2087d3;background-color:transparent;}");
   m_pLabelText->hide();
   // 布局
   QHBoxLayout *pLayout = new QHBoxLayout(this);
   pLayout->setContentsMargins(0, 0, 0, 0);
   pLayout->setSpacing(3);
   if (bIsIconLeft)
   {
       pLayout->addWidget(m_pLabelIcon);
       pLayout->addWidget(m_pLabelText);
   }
   else
   {
       pLayout->addWidget(m_pLabelText);
       pLayout->addWidget(m_pLabelIcon);
   }
}

void QIconPushButton::enterEvent(QEvent *event)
{
    if (m_pLabelIcon)
    {
        QImage icon(m_IconHover);
        if (icon.height() > m_IconSize)
        {
            icon = GetRoundedRectImage(icon, m_IconSize, m_IconSize, 2, 2);
        }
        m_pLabelIcon->setPixmap(QPixmap::fromImage(icon));
    }
    if (m_pLabelText)
    {
        if (!m_TextStyleHover.isEmpty())
        {
            m_pLabelText->setStyleSheet(m_TextStyleHover);
        }
    }

    // 鼠标悬浮，显示提示气泡
    if (m_pToolTip)
    {
        QPoint pos;
        int w = width();
        int h = height();
        switch (m_TipDirection)
        {
        case AD_LEFT:
            pos = this->mapToGlobal(QPoint(w, h / 2));
            break;
        case AD_TOP:
            pos = this->mapToGlobal(QPoint(w / 2, h));
            break;
        case AD_RIGHT:
            pos = this->mapToGlobal(QPoint(0, h / 2));
            break;
        case AD_BOTTOM:
            pos = this->mapToGlobal(QPoint(w / 2, 0));
            break;
        default:
            break;
        }
        m_pToolTip->showTip(pos);
    }
}

void QIconPushButton::leaveEvent(QEvent *event)
{
    if (m_pLabelIcon)
    {
        QImage icon(m_IconNormal);
        if (icon.height() > m_IconSize)
        {
            icon = GetRoundedRectImage(icon, m_IconSize, m_IconSize, 2, 2);
        }
        m_pLabelIcon->setPixmap(QPixmap::fromImage(icon));
    }
    if (m_pLabelText)
    {
        if (!m_TextStyleNormal.isEmpty())
        {
            m_pLabelText->setStyleSheet(m_TextStyleNormal);
        }
    }

    if (m_pToolTip)
    {
        m_pToolTip->hide();
    }
}
