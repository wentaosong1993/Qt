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
	connect(ui.calendarWidget, SIGNAL(currentPageChanged(int, int)), SLOT(updateTime(int, int))); //无法在日历更新年月时同步更新其他控件的时间

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
	int ret = QMessageBox::warning(this, QStringLiteral("消息对话框"), QStringLiteral("attention please!") ,QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	if (QMessageBox::Ok == ret)
	{
		qDebug() << "Ok pressed";
	}
}

void StandardDialog::getErrorDialog()
{
	QErrorMessage *errorDialog = new QErrorMessage(this);
	errorDialog->setWindowTitle(QStringLiteral("错误消息对话框"));
	errorDialog->showMessage(QStringLiteral("这是出错信息"));
}

void StandardDialog::getGuideDialog()
{
	QWizard wizard(this);
	wizard.setWindowTitle(QStringLiteral("向导对话框"));
	wizard.addPage(createPage1());
	wizard.addPage(createPage2());
	wizard.addPage(createPage3());
	wizard.exec();
}

void StandardDialog::getProgressDialog()
{
	QProgressDialog dialog(QStringLiteral("文件复制进度"),QStringLiteral("进度"), 0, 50000, this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setWindowTitle(QStringLiteral("进度对话框"));
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
	qDebug() << QStringLiteral("文件复制结束！");
}

void StandardDialog::getInputDialog()
{
	bool ok;
	QString text = QInputDialog::getText(this, QStringLiteral("输入字符串对话框"), QStringLiteral("输入用户名:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
	if (ok && !text.isEmpty())
	{
		qDebug() << "string:" << text;
	}

	int value1 = QInputDialog::getInt(this, QStringLiteral("输入整数对话框"), QStringLiteral("输入-1000到1000之间的整数:"), 100, -1000, 1000, 10, &ok);
																																	  //步进值
	if (ok)
	{
		qDebug() << "value1:" << value1;
	}

	int value2 = QInputDialog::getDouble(this, QStringLiteral("输入浮点数对话框"), QStringLiteral("输入-1000到1000之间的浮点数:"), 0.00, -1000, 1000, 2, &ok);
	if (ok)
	{
		qDebug() << "value2:" << value2;
	}

	QStringList items;
	items << QStringLiteral("条目1") << QStringLiteral("条目2");
	QString item = QInputDialog::getItem(this,QStringLiteral("输入条目对话框"),QStringLiteral("请选择或输入一个条目"), items, 0, true, &ok);

	if (ok)
	{
		qDebug() << "item:" << item;
	}
}

void StandardDialog::getFileDialog()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), QStringLiteral("/宋文涛"), tr("Image Files (*.png *.jpg *.bmp)"));
	if (!fileName.isEmpty())
	{
		qDebug() << "filePath" << fileName;
	}
	else
	{
		QMessageBox::warning(this, QStringLiteral("路径为空"),QStringLiteral("路径为空"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
	}

	QList<QUrl> list = QFileDialog::getOpenFileUrls(this,QStringLiteral("Open Url"),QStringLiteral("/宋文涛"),QStringLiteral("All Files (*.*)"));
	if (list.size() > 0)
	{
		QDesktopServices::openUrl(QUrl(list.at(0)));
		qDebug() << "file Url:" << list.at(0);
	}
	else
	{
		QMessageBox::warning(this, QStringLiteral("路径为空"), QStringLiteral("路径为空"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
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
	page->setTitle(QStringLiteral("介绍"));
	return page;
}

QWizardPage * StandardDialog::createPage2()
{
	QWizardPage *page = new QWizardPage;
	page->setTitle(QStringLiteral("用户选择信息"));
	return page;
}

QWizardPage * StandardDialog::createPage3()
{
	QWizardPage *page = new QWizardPage;
	page->setTitle(QStringLiteral("结束"));
	return page;
}
