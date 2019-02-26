#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    this->installEventFilter(this);
    //安装过滤器和被安装过滤器的组件必须在同一线程内，否则，无效。
    ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);
    timerId = this->startTimer(1000);
    ui->pushButton->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_2)
    {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if(event->type() == QEvent::MouseMove)
        {
            QString str = QString("<center><h1>MouseMove: %1 </h1></center>")
                    .arg(e->x());
            ui->label_2->setText(str);
            return true;
        }
        else
        {
            return QObject::eventFilter(watched,event);
        }
    }
    else if(watched == ui->pushButton)
    {
         if(event->type() == QEvent::MouseButtonPress)
         {

             ui->pushButton->setText("123");
             return true;
         }
         //缺少else,pushbutton根本无法显示到UI上
         //条件语句中，返回了true,导致关于按钮的所有事件都被过滤掉了，其中就有QShowEvent事件
         else
         {
             return QObject::eventFilter(watched,event);
         }
    }
    else
    {
        return QObject::eventFilter(watched,event);
    }
}

bool Widget::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::Close:
    {
        QCloseEvent *ev = static_cast<QCloseEvent *>(event);
        closeEvent(ev);
        return true;
    }
    case QEvent::KeyPress:
    {
        QKeyEvent *ev = static_cast<QKeyEvent *>(event);
        keyPressEvent(ev);
        return true;
    }

    case QEvent::KeyRelease:
    {
        QKeyEvent *ev = static_cast<QKeyEvent *>(event);
        keyReleaseEvent(ev);
        return true;
    }

    case QEvent::MouseMove:
    {
        QMouseEvent *ev = static_cast<QMouseEvent *>(event);
        mouseMoveEvent(ev);
        return true;
    }

    case QEvent::Timer:
    {
//        QTimerEvent *ev = static_cast<QTimerEvent *>(event);
//        timerEvent(ev);
//        return true;
//        //干掉定时器，事件停止传播
        return true;
    }
        //......
    default:
        return QWidget::event(event);
    }

    return QWidget::event(event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        qDebug() << "Key_A:Press:" << (char)(Qt::Key_A);
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        qDebug() << "Key_A:Release:" << (char)(Qt::Key_A);
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
     int ret =  QMessageBox::question(this,"close","close?");
     if(ret == QMessageBox::Yes)
     {
         //关闭窗口，接收事件，事件不会再往下传递
         event->accept();
     }
     else if(ret == QMessageBox::No)
     {
         //不关闭窗口
         event->ignore();
     }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "Left";
    }
    else if(event->button() == Qt::RightButton)
    {
        qDebug() << "Right";
    }
    else if(event->button() == Qt::MiddleButton)
    {
        qDebug() << "Middle";
    }
    else
    {

    }
    int i = event->x();
    int j = event->y();
    QString str = QString("<center><h1>press: %1 %2</h1></center>")
            .arg(i).arg(j);
    ui->label_1->setText(str);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    int i = event->x();
    int j = event->y();
    QString str = QString("<center><h1>release: %1 %2</h1></center>")
            .arg(i).arg(j);
    ui->label_1->setText(str);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int i = event->x();
    int j = event->y();
    QString str = QString("<center><h1> move: %1 %2</h1></center>")
            .arg(i).arg(j);
    ui->label_1->setText(str);
}

void Widget::timerEvent(QTimerEvent *event)
{
    static int sec = 0;
    ui->label_2->setText(QString("<center><h1> timer: %1</h1></center>").arg(sec++));
    if(5 == sec)
    {
        this->killTimer(timerId);
    }
}



void Widget::on_pushButton_clicked()
{
    qDebug() << "clicked" << endl;
}
