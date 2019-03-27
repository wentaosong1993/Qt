#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)/*,m_flag(false)*/
{
    ui->setupUi(this);


    m_thread = new myThread;

    m_qThread = new QThread(this);

    m_thread->moveToThread(m_qThread);

    qDebug() << QStringLiteral("主线程号:") << QThread::currentThread();


    connect(this,&MyWidget::startThread,m_thread,&myThread::myTimeOut);//主线程开始执行，触发startThread信号，子线程对象接受该信号，触发myTimeOut槽函数
                                                                       //使该槽函数在新的线程中运行程序，从而实现两个线程同时运行
//    connect(this,&MyWidget::startThread,this,&MyWidget::myTimeOut);

    connect(m_thread,&myThread::timeSignal,this,&MyWidget::dealSignal);
//    connect(this,&MyWidget::timeSignal,this,&MyWidget::dealSignal);

    connect(this,&MyWidget::destroyed,this,&MyWidget::dealClose);


//1、线程处理函数内部，不允许操作图形界面

//2、connect   第五个参数的作用
    //连接方式：（常用）默认，直接，队列
    //默认的时候:
    //如果是多线程，默认是使用队列
    //如果是单线程，默认是直接

    ///区别:
    //队列:槽函数所在的线程和接收者一样
    //直接：槽函数所在的线程和发送者一样

}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::dealSignal()
{
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}

void MyWidget::dealClose()
{
    on_stopBtn_clicked();
    delete m_thread;
    m_thread = NULL;
}


void MyWidget::on_startBtn_clicked()
{
    //启动线程，并没有启动线程处理函数
   if(m_qThread->isRunning() == true)
   {
       return;
   }
   m_qThread->start();
   m_thread->setFlag(false);

//1、不能直接调用线程处理函数，导致，线程处理函数和主线程是在同一线程

//2、 m_thread->myTimeOut();
   /* 子线程号和主线程号一样
    * Starting F:\GitHubRepository\Qt\MyThread\build-MyThread-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug\debug\MyThread.exe...
    "主线程号:" QThread(0x378c30)
    "子线程号:" QThread(0x378c30)
    "子线程号:" QThread(0x378c30)
    "子线程号:" QThread(0x378c30)
   */
//3、只能通过signal - slot 方法调用

   emit startThread();

}

void MyWidget::on_stopBtn_clicked()
{
    if(m_qThread->isRunning() == false)
    {
        return;
    }
    m_thread->setFlag(true);
    m_qThread->quit();
    m_qThread->wait();
}




//void MyWidget::myTimeOut()
//{
//    while(m_flag == false)
//    {
//        QThread::sleep(1);
//        if(true == m_flag)
//        {
//            break;
//        }
//        emit timeSignal();
////        QMessageBox::aboutQt(NULL);
////error: ASSERT failure in QWidget: "Widgets must be created in the GUI thread.", file kernel\qwidget.cpp, line 1150
////        qDebug() << QStringLiteral("子线程号:") << QThread::currentThread();
//    }
//}
