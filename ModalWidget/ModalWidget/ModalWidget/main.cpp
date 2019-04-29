#include "modalwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ModalWidget w;
	w.show();
	return a.exec();
}
