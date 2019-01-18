#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myThread = new MyThread;

    //创建子线程
    thread = new QThread(this);

    //把自定义模块加入到子线程
    myThread->moveToThread(thread);

    thread->start();//启动子线程


    //线程处理函数 需要通过 signal -slot 来调用

    //多线程，默认为队列连接方式
    connect(ui->pushButton,&QPushButton::clicked,myThread,&MyThread::drawImage,Qt::QueuedConnection);
    connect(myThread,&MyThread::updateImage,this,&Widget::getImage);
    connect(this,&Widget::destroyed,this,&Widget::dealClose);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::getImage(QImage tempImage)
{
    image = tempImage;
    update();
}

void Widget::dealClose()
{
    //退出子线程
    thread->quit();
    //等待回收资源
    thread->wait();
    //手动释放内存
    delete myThread;
    myThread = NULL;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); //窗口画图
    painter.drawImage(50,50,image);
    return __super::paintEvent(event);
}
