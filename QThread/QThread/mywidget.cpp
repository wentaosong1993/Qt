#include "mywidget.h"
#include "ui_mywidget.h"
#include <QThread>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_thread = new MyThread(this);

    connect(m_timer,&QTimer::timeout,this,&MyWidget::dealTimeout);

    connect(ui->pushButton,&QPushButton::clicked,this,&MyWidget::buttonClick);
    connect(m_thread,&MyThread::isDone,this,&MyWidget::timerStop);

}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::buttonClick()
{
    if(m_timer->isActive() == false)
    {
        m_timer->start(100);
    }
    m_thread->start();

    //复杂数据处理子程序，耗时较长
//    QThread::sleep(5);
    //数据处理完成，关闭定时器
//    m_timer->stop();
}

void MyWidget::dealTimeout()
{
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}

void MyWidget::timerStop()
{
    m_timer->stop();
    m_thread->quit();
    m_thread->wait();
}
