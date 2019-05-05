#include "filedragdrop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileDragDrop w;
	w.show();
	return a.exec();
}
