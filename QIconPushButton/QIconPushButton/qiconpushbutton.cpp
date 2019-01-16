#include "qiconpushbutton.h"


QIconPushButton::QIconPushButton(QWidget *parent) :
    QPushButton(parent)
{
    isIconLeft = true;
    this->setFixedSize(60,40);
    this->setStyleSheet("QWidget {background-color: #29A1F7; border: 1px solid blue;margin: -2;}\
                         QWidget:hover {background-color: #4AB0FB; border: 1px solid lightblue; margin: -2;}\
                         QWidget:pressed {background-color: #2087D3; border: 1px solid lightblue; margin: -2;}");

    m_label = new QLabel;
    m_label->setText("abc");
    m_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QFont serifFont("Times", 10, QFont::Bold);
    m_label->setFont(serifFont);
    m_label->setStyleSheet("QLabel{background-color: transparent;color: white; font: 14px;margin-left: 10px; }");

    m_icon = new QLabel;
    m_icon->setPixmap(QPixmap::fromImage(QImage(":/image/tips.png")));
    m_icon->setStyleSheet("QLabel{background-color: transparent;}");
    hLayout = new QHBoxLayout(this);
    if(isIconLeft)
    {
        hLayout->addWidget(m_icon);
        hLayout->addWidget(m_label);
    }
    else
    {
        hLayout->addWidget(m_label);
        hLayout->addWidget(m_icon);
    }

}

QIconPushButton::~QIconPushButton()
{
}

//void QIconPushButton::setText(QString str)
//{
//    m_label->setText(str);
//}

void QIconPushButton::enterEvent(QEvent *event)
{
    if(m_icon)
    {
        m_icon->setToolTip("balabala");
    }
}

void QIconPushButton::leaveEvent(QEvent *event)
{
    if(m_icon)
    {
        m_icon->setToolTip("");
    }
}





