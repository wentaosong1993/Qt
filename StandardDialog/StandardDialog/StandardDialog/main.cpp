#include "StandardDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StandardDialog w;
	w.show();
	return a.exec();
}
