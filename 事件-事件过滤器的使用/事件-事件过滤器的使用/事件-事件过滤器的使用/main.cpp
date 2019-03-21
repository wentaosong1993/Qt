#include "event_eventfilter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Event_EventFilter w;
	w.show();
	return a.exec();
}
