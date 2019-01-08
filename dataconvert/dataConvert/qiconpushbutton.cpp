#include "qiconpushbutton.h"


QIconPushButton::QIconPushButton(QWidget *parent) :
    QPushButton(parent)
{
    isIconLeft = true;
//    this->setFixedSize(60,30);
    this->setFixedHeight(30);
    this->setStyleSheet("QPushButton {background-color: #29A1F7;border: 0px solid blue;margin-left: 0;}\
                         QPushButton:hover {background-color: #4AB0FB; border: 0px solid lightblue; margin: 0;}\
                         QPushButton:pressed {background-color: #2087D3;border: 0px solid lightblue; margin: 0;}");

    m_label = new QLabel;
    m_label->setText("abc");
    m_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QFont serifFont("Times", 10, QFont::Bold);
    m_label->setFont(serifFont);
    m_label->setStyleSheet("QLabel{background-color: transparent;color: black; font: 14px; } \
                            QLabel:hover {background-color:transparent;color: #6bb4ff;font:12px; } \
                            QLabel:pressed {background-color:transparent;color: #338ff0;font:12px;}");

    m_icon = new QLabel;
    m_icon->setPixmap(QPixmap::fromImage(QImage(":/Img/tips.png")));
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





