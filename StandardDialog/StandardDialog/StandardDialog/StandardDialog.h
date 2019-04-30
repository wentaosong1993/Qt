#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StandardDialog.h"
#include <QWizard>

class StandardDialog : public QMainWindow
{
	Q_OBJECT

public:
	StandardDialog(QWidget *parent = Q_NULLPTR);

public slots:
	void getColorDialog();
	void getFontDialog();
	void getMessageDialog();
	void getErrorDialog();
	void getGuideDialog();
	void getProgressDialog();
	void getInputDialog();
	void getFileDialog();
	void getSelectedDate(QDate selectedDate);
	void setSelectedDate(QDate selectedDate);
	void setSelectedDateOfTimeEdit(QDate selectedDate);
	void setSelectedDateOfDateTimeEdit(QDate selectedDate);
	void updateTime(int year,int month);

private:
	Ui::StandardDialogClass ui;
	QWizardPage *createPage1();
	QWizardPage *createPage2();
	QWizardPage *createPage3();
};
