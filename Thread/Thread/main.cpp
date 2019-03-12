/*
 * 1、多线程程序的行为无法预期，当多次执行上述程序时，每一次的运行结果都可能不同；
 * 2、多线程的执行顺序无法保证，它与操作系统的调度策略和线程优先级等因素有关。
 * 3、多线程的切换可能发生在任何时刻、任何地点
 * 4、多线程对代码的敏感度高，因此对代码的细微修改都可能产生意想不到的结果。
*/


#include "threaddlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadDlg w;
    w.show();

    return a.exec();
}
