#pragma once

#include <QtWidgets/QDialog>
#include "ui_CustomDlg.h"
#include <QEvent>

class CustomDlg : public QDialog
{
	Q_OBJECT

public:
	CustomDlg(QWidget *parent = Q_NULLPTR);

protected:
	bool eventFilter(QObject *obj, QEvent *event);

public slots:
	void okClicked();


private:
	Ui::CustomDlgClass ui;
	bool m_drag;
	QPoint m_DragPosition;
};
