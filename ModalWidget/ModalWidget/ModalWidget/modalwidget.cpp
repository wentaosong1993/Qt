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
	//dialog.setFixedSize(200, 100); //ģ̬�Ի���
	//dialog.exec();


	//QDialog dialog(this);
	//dialog.setModal(true);
	//dialog.show();//��ģ̬�Ի���

	//dialog = new QDialog();
	//dialog->setModal(true);
	//dialog->setFixedSize(200, 100);
	//dialog->show();


	dialog.setFixedSize(200, 100);
	textEdit.setParent(&dialog);

	dialog.setModal(true);//��Ե�ǰӦ�ó��������������ģ̬��
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
