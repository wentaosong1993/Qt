#include "widget.h"
#include <QAction>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_pushButton = new QPushButton(this);
    m_menu = new QMenu(this);
    m_menu->addAction(QIcon(":/information.png"),tr("Zoom IN"));
//    m_menu->addAction(QIcon("qrc:/information.png"),tr("Zoom IN"));//不行
    m_pushButton->setMenu(m_menu);
}

Widget::~Widget()
{

}
