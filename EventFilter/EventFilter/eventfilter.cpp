﻿#include "eventfilter.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMatrix>
#include <QPixmap>

EventFilter::EventFilter(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(QStringLiteral("事件过滤"));
    label1 = new QLabel;
    Image1.load(":/1.jpg");
    label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label1->setPixmap(QPixmap::fromImage(Image1));

    label2 = new QLabel;
    Image2.load(":/2.jpg");
    label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label2->setPixmap(QPixmap::fromImage(Image2));

    label3 = new QLabel;
    Image3.load(":/3.jpg");
    label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label3->setPixmap(QPixmap::fromImage(Image3));

    stateLabel = new QLabel(QStringLiteral("鼠标按下标志"));
    stateLabel->setAlignment(Qt::AlignHCenter);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(stateLabel);
    label1->installEventFilter(this);
    label2->installEventFilter(this);
    label3->installEventFilter(this);
}

EventFilter::~EventFilter()
{

}

bool EventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == label1)
    {
        //判断发生的事件类型
        if(event->type() == QEvent::MouseButtonPress)
        {
            //将事件转化为鼠标事件
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            //分类
            if(mouseEvent->buttons() & Qt::LeftButton)
            {
                stateLabel->setText(QStringLiteral("左键按下左边的图片"));
            }
            if(mouseEvent->buttons() & Qt::RightButton)
            {
                stateLabel->setText(QStringLiteral("右键按下左边的图片"));
            }
            if(mouseEvent->buttons() & Qt::MiddleButton)
            {
                stateLabel->setText(QStringLiteral("中间键按下左边的图片"));
            }

            //显示缩小的图片
            QMatrix matrix;
            matrix.scale(1.8,1.8);
            QImage tmpImage = Image1.transformed(matrix);
            label1->setPixmap(QPixmap::fromImage(tmpImage));
        }
        //鼠标释放事件的处理，恢复图片的大小
        if(event->type() == QEvent::MouseButtonRelease)
        {
            stateLabel->setText(QStringLiteral("鼠标释放左边图片"));
            label1->setPixmap(QPixmap::fromImage(Image1));
        }
    }

    if(watched == label2)
    {
        //判断发生的事件类型
        if(event->type() == QEvent::MouseButtonPress)
        {
            //将事件转化为鼠标事件
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            //分类
            if(mouseEvent->buttons() & Qt::LeftButton)
            {
                stateLabel->setText(QStringLiteral("左键按下中间的图片"));
            }
            if(mouseEvent->buttons() & Qt::RightButton)
            {
                stateLabel->setText(QStringLiteral("右键按下中间的图片"));
            }
            if(mouseEvent->buttons() & Qt::MiddleButton)
            {
                stateLabel->setText(QStringLiteral("中间键按下中间的图片"));
            }

            //显示缩小的图片
            QMatrix matrix;
            matrix.scale(1.8,1.8);
            QImage tmpImage = Image2.transformed(matrix);
            label2->setPixmap(QPixmap::fromImage(tmpImage));
        }
        //鼠标释放事件的处理，恢复图片的大小
        if(event->type() == QEvent::MouseButtonRelease)
        {
            stateLabel->setText(QStringLiteral("鼠标释放中间的图片"));
            label2->setPixmap(QPixmap::fromImage(Image2));
        }
    }

    if(watched == label3)
    {
        //判断发生的事件类型
        if(event->type() == QEvent::MouseButtonPress)
        {
            //将事件转化为鼠标事件
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            //分类
            if(mouseEvent->buttons() & Qt::LeftButton)
            {
                stateLabel->setText(QStringLiteral("左键按下右边的图片"));
            }
            if(mouseEvent->buttons() & Qt::RightButton)
            {
                stateLabel->setText(QStringLiteral("右键按下右边的图片"));
            }
            if(mouseEvent->buttons() & Qt::MiddleButton)
            {
                stateLabel->setText(QStringLiteral("中间键按下右边的图片"));
            }

            //显示缩小的图片
            QMatrix matrix;
            matrix.scale(1.8,1.8);
            QImage tmpImage = Image3.transformed(matrix);
            label3->setPixmap(QPixmap::fromImage(tmpImage));
        }
        //鼠标释放事件的处理，恢复图片的大小
        if(event->type() == QEvent::MouseButtonRelease)
        {
            stateLabel->setText(QStringLiteral("鼠标释放中间的图片"));
            label3->setPixmap(QPixmap::fromImage(Image3));
        }
    }

    //将事件交给上层对话框
    return QDialog::eventFilter(watched,event);
}