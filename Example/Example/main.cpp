#include "content.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("AR PL KaitiM GB",12);
    a.setFont(font);

    //新建水平分割窗对象
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);
    splitterMain->setOpaqueResize(true);
    QListWidget *list = new QListWidget(splitterMain);
    list->insertItem(0,QStringLiteral("基本信息"));
    list->insertItem(1,QStringLiteral("联系方式"));
    list->insertItem(2,QStringLiteral("详细资料"));

    Content *content = new Content(splitterMain);
    QObject::connect(list,SIGNAL(currentRowChanged(int)),content->stack,SLOT(setCurrentIndex(int)));
    //设置主布局框即水平分割窗的最小尺寸
    splitterMain->setWindowTitle(QStringLiteral("修改用户资料"));
    //设置主布局框即水平分割窗的最小尺寸
    splitterMain->setMinimumSize(splitterMain->minimumSize());

    splitterMain->setMaximumSize(splitterMain->maximumSize());

    splitterMain->show();

    return a.exec();
}
