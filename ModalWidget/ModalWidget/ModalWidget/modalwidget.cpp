#include "modalwidget.h"
#include <QDebug>


ModalWidget::ModalWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//QDialog dialog(this);
	//dialog.show();

	//QDialog *dialog = new QDialog(this);
	//dialog->show();

	//QDialog dialog(this);
	//dialog.setFixedSize(200, 100); //模态对话框
	//dialog.exec();


	//QDialog dialog(this);
	//dialog.setModal(true);
	//dialog.show();//非模态对话框

	//dialog = new QDialog();
	//dialog->setModal(true);
	//dialog->setFixedSize(200, 100);
	//dialog->show();


	dialog.setFixedSize(200, 100);
	textEdit.setParent(&dialog);

	dialog.setModal(true);//相对当前应用程序的其他窗口是模态的
	dialog.show();


}

//************************************
// Method:    ~ModalWidget
// FullName:  ModalWidget::~ModalWidget
// Access:    public 
// Returns:   
// Qualifier:
//************************************
ModalWidget::~ModalWidget()
{
	//if (dialog)
	//{
	//	delete dialog;
	//	dialog = nullptr;
	//}
}
