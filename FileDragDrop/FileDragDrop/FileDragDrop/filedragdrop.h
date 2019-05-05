#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_filedragdrop.h"
#include <QDragEnterEvent>
#include <QEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>

class FileDragDrop : public QMainWindow
{
	Q_OBJECT

public:
	FileDragDrop(QWidget *parent = Q_NULLPTR);

//protected: 
//	void dragEnterEvent(QDragEnterEvent *e);
//	void dropEvent(QDropEvent *e);

private:
	Ui::FileDragDropClass ui;
};
