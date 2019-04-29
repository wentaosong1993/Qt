#pragma once

#include <QtWidgets/QWidget>
#include <QDialog>
#include <QTextEdit>
#include "ui_modalwidget.h"

class ModalWidget : public QWidget
{
	Q_OBJECT

public:
	ModalWidget(QWidget *parent = Q_NULLPTR);
	~ModalWidget();

private:
	Ui::ModalWidgetClass ui;
	//QDialog *dialog = nullptr;
	QDialog dialog;
	QTextEdit textEdit;
};
