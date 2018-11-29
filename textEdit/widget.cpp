#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 窗口大小设置为600*500
    resize(600, 500);
    // 画布大小为200*200，背景为白色
    pix = QPixmap(600, 500);
    pix.fill(Qt::white);

    isDrawing = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
//    QPainter pp(&pix);
//     // 根据鼠标指针前后两个位置绘制直线
//    pp.drawLine(lastPoint, endPoint);
//    // 让前一个坐标值等于后一个坐标值，
//    // 这样就能实现画出连续的线
//    lastPoint = endPoint;
//    QPainter painter(this);
//    painter.drawPixmap(0, 0, pix);
        int x,y,w,h;
        x = lastPoint.x();
		qDebug() << "lastPoint.x" << x;
        y = lastPoint.y();
        w = endPoint.x() - x;
		qDebug() << "endPoint.x" << endPoint.x();
		qDebug() << "w" << w;
        h = endPoint.y() - y;
        QPainter painter(this);
        if(isDrawing) //如果正在绘图，就在辅助画布上绘制
        {
           //将以前pix中的内容复制到tempPix中，保证以前的内容不消失
           tempPix = pix;
           QPainter pp(&tempPix);
           pp.drawRect(x,y,w,h);
           painter.drawPixmap(0, 0, tempPix);
        } else {
           QPainter pp(&pix);
           pp.drawRect(x,y,w,h);
           painter.drawPixmap(0,0,pix);
        }
}

void Widget::mousePressEvent(QMouseEvent * event)
{
    //鼠标左键按下
     if(event->button() == Qt::LeftButton)
      lastPoint = event->pos();

//      endPoint = lastPoint;
      isDrawing = true;   //正在绘图
	  qDebug()  << "leftbutton pressed!" << lastPoint.x();
}

void Widget::mouseMoveEvent(QMouseEvent * event)
{
    // 鼠标左键按下的同时移动鼠标
    if(event->buttons() & Qt::LeftButton)
    {
       endPoint = event->pos();
	   qDebug() << "leftbutton move!";
       update();//进行绘制
    }
}

void Widget::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton) //鼠标左键释放
    {
      endPoint = event->pos();
      isDrawing = false;    //结束绘图
	  qDebug() << "leftbutton released!";
      update();
    }
}
