#include "modalwidget.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ModalWidget w;

	//QMessageBox msgBox;
	//if (msgBox.exec() == QMessageBox::Ok)
	//{
	//	w.show();
	//	return a.exec();
	//}
	QDialog dialog(&w);
	QPushButton *button = new QPushButton();
	button->setParent(&dialog);
	button->setFixedSize(30, 30);
	QObject::connect(button, &QPushButton::clicked, &dialog, &QDialog::accept);
	//accept is a slot,carry it out to hide the modal dialog and set the result code to Accepted;

	if (dialog.exec() == QDialog::Accepted)//点击按钮进入
	{
		w.show();
		return a.exec();
	}
	else
	{
		return 0;
	}
}
