#pragma once
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QTextStream>


class DropTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	DropTextEdit(QWidget *parent = nullptr);

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);
};