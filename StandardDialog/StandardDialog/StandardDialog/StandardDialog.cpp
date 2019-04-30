#include "StandardDialog.h"
#include <QDebug>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QErrorMessage>
#include <QProgressDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDir>
#include <QDesktopServices>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QCalendarWidget>
#include <QDate>

StandardDialog::StandardDialog(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.colorButton,SIGNAL(clicked()),this, SLOT(getColorDialog()));
	connect(ui.fontButton, SIGNAL(clicked()), this, SLOT(getFontDialog()));
	connect(ui.messageButton, SIGNAL(clicked()), this, SLOT(getMessageDialog()));
	connect(ui.errorButton,SIGNAL(clicked()),this, SLOT(getErrorDialog()));
	connect(ui.guideButton,SIGNAL(clicked()),this,SLOT(getGuideDialog()));
	connect(ui.progressButton, SIGNAL(clicked()), this, SLOT(getProgressDialog()));
	connect(ui.inputButton, SIGNAL(clicked()), this, SLOT(getInputDialog()));
	connect(ui.fileButton, SIGNAL(clicked()), this, SLOT(getFileDialog()));

	ui.dateTimeEdit->setDate(QDate::currentDate());
	ui.dateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
	ui.dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
	ui.dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:MM::ss");

	ui.dateEdit->setDate(QDate::currentDate());
	ui.dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));
	ui.dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
	ui.dateEdit->setDisplayFormat("yyyy-MM-dd HH:MM::ss");

	ui.calendarWidget->setGridVisible(true);
	connect(ui.calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(getSelectedDate(QDate)));
	connect(ui.calendarWidget, SIGNAL(currentPageChanged(int, int)), SLOT(updateTime(int, int))); //�޷���������������ʱͬ�����������ؼ���ʱ��

	connect(ui.dateTimeEdit,SIGNAL(dateChanged(QDate)),this, SLOT(setSelectedDate(QDate)));
	connect(ui.dateEdit,SIGNAL(dateChanged(QDate)),this, SLOT(setSelectedDate(QDate)));

	connect(ui.dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(setSelectedDateOfTimeEdit(QDate)));
	connect(ui.dateTimeEdit,SIGNAL(dateChanged(QDate)),this, SLOT(setSelectedDateOfDateTimeEdit(QDate)));



	ui.textEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:MM::ss"));
}

void StandardDialog::getColorDialog()
{
	//QColorDialog *colorDialog = new QColorDialog(this);
	QColor color = QColorDialog::getColor(Qt::red,this,QStringLiteral("color Dialog"));
	//qDebug() << "choced color:" << color;
	ui.textEdit->setTextColor(color);

}

void StandardDialog::getFontDialog()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10),this);
	//qDebug() << "choced font:" << font;
	if (ok)
	{
		ui.textEdit->setFont(font);
	}
}

void StandardDialog::getMessageDialog()
{
	int ret = QMessageBox::warning(this, QStringLiteral("��Ϣ�Ի���"), QStringLiteral("attention please!") ,QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	if (QMessageBox::Ok == ret)
	{
		qDebug() << "Ok pressed";
	}
}

void StandardDialog::getErrorDialog()
{
	QErrorMessage *errorDialog = new QErrorMessage(this);
	errorDialog->setWindowTitle(QStringLiteral("������Ϣ�Ի���"));
	errorDialog->showMessage(QStringLiteral("���ǳ�����Ϣ"));
}

void StandardDialog::getGuideDialog()
{
	QWizard wizard(this);
	wizard.setWindowTitle(QStringLiteral("�򵼶Ի���"));
	wizard.addPage(createPage1());
	wizard.addPage(createPage2());
	wizard.addPage(createPage3());
	wizard.exec();
}

void StandardDialog::getProgressDialog()
{
	QProgressDialog dialog(QStringLiteral("�ļ����ƽ���"),QStringLiteral("����"), 0, 50000, this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setWindowTitle(QStringLiteral("���ȶԻ���"));
	dialog.show();
	for (int i = 0; i < 50000; i++)
	{
		dialog.setValue(i);
		QCoreApplication::processEvents();
		if (dialog.wasCanceled())
		{
			break;
		}
	}
	dialog.setValue(50000);
	qDebug() << QStringLiteral("�ļ����ƽ�����");
}

void StandardDialog::getInputDialog()
{
	bool ok;
	QString text = QInputDialog::getText(this, QStringLiteral("�����ַ����Ի���"), QStringLiteral("�����û���:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
	if (ok && !text.isEmpty())
	{
		qDebug() << "string:" << text;
	}

	int value1 = QInputDialog::getInt(this, QStringLiteral("���������Ի���"), QStringLiteral("����-1000��1000֮�������:"), 100, -1000, 1000, 10, &ok);
																																	  //����ֵ
	if (ok)
	{
		qDebug() << "value1:" << value1;
	}

	int value2 = QInputDialog::getDouble(this, QStringLiteral("���븡�����Ի���"), QStringLiteral("����-1000��1000֮��ĸ�����:"), 0.00, -1000, 1000, 2, &ok);
	if (ok)
	{
		qDebug() << "value2:" << value2;
	}

	QStringList items;
	items << QStringLiteral("��Ŀ1") << QStringLiteral("��Ŀ2");
	QString item = QInputDialog::getItem(this,QStringLiteral("������Ŀ�Ի���"),QStringLiteral("��ѡ�������һ����Ŀ"), items, 0, true, &ok);

	if (ok)
	{
		qDebug() << "item:" << item;
	}
}

void StandardDialog::getFileDialog()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), QStringLiteral("/������"), tr("Image Files (*.png *.jpg *.bmp)"));
	if (!fileName.isEmpty())
	{
		qDebug() << "filePath" << fileName;
	}
	else
	{
		QMessageBox::warning(this, QStringLiteral("·��Ϊ��"),QStringLiteral("·��Ϊ��"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
	}

	QList<QUrl> list = QFileDialog::getOpenFileUrls(this,QStringLiteral("Open Url"),QStringLiteral("/������"),QStringLiteral("All Files (*.*)"));
	if (list.size() > 0)
	{
		QDesktopServices::openUrl(QUrl(list.at(0)));
		qDebug() << "file Url:" << list.at(0);
	}
	else
	{
		QMessageBox::warning(this, QStringLiteral("·��Ϊ��"), QStringLiteral("·��Ϊ��"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
}

void StandardDialog::getSelectedDate(QDate selectedDate)
{
	ui.dateTimeEdit->setDate(selectedDate);
	ui.dateEdit->setDate(selectedDate);
	ui.textEdit->setText(selectedDate.toString("yyyy-MM-dd HH:MM::ss"));
}

void StandardDialog::setSelectedDate(QDate selectedDate)
{
	ui.calendarWidget->setSelectedDate(selectedDate);
	ui.dateTimeEdit->setDate(selectedDate);
	ui.textEdit->setText(selectedDate.toString("yyyy-MM-dd HH:MM::ss"));
}

void StandardDialog::setSelectedDateOfTimeEdit(QDate selectedDate)
{
	ui.dateTimeEdit->setDate(selectedDate);
	ui.textEdit->setText(selectedDate.toString("yyyy-MM-dd HH:MM::ss"));
}

void StandardDialog::setSelectedDateOfDateTimeEdit(QDate selectedDate)
{
	ui.dateEdit->setDate(selectedDate);
	ui.textEdit->setText(selectedDate.toString("yyyy-MM-dd HH:MM::ss"));
}

void StandardDialog::updateTime(int year, int month)
{
	//ui.textEdit->setText(QDate);
	QDateTime dateTime = QDateTime::currentDateTime();
}

QWizardPage * StandardDialog::createPage1()
{
	QWizardPage *page = new QWizardPage;
	page->setTitle(QStringLiteral("����"));
	return page;
}

QWizardPage * StandardDialog::createPage2()
{
	QWizardPage *page = new QWizardPage;
	page->setTitle(QStringLiteral("�û�ѡ����Ϣ"));
	return page;
}

QWizardPage * StandardDialog::createPage3()
{
	QWizardPage *page = new QWizardPage;
	page->setTitle(QStringLiteral("����"));
	return page;
}
