#pragma once
#include <QPushButton>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QEvent>
#include <QMimeData>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include "flowlayout.h"

class TemplateWidget : public QWidget
{
	Q_OBJECT
public:
	TemplateWidget(QString fileName, QWidget *parent = nullptr);
	~TemplateWidget();

protected:
	void focusInEvent(QFocusEvent *event);
	void focusOutEvent(QFocusEvent *event);

private:
	QLabel *m_fileImg = nullptr;
	QLabel *m_fileNameLabel = nullptr;
	QLabel *m_fileSize = nullptr;
	QPushButton* m_Button = nullptr;
};


class DropTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	DropTextEdit(QWidget *parent = nullptr);
	~DropTextEdit();

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dragMoveEvent(QDragMoveEvent *e);
	void dropEvent(QDropEvent *e);

private:
	//QLabel *m_fileImg = nullptr;
	//QLabel *m_fileNameLabel = nullptr;
	//QLabel *m_fileSize = nullptr;
	//QWidget* m_templateWidget = nullptr;
	TemplateWidget* m_templateWidget = nullptr;
	FlowLayout *m_flowLayout = nullptr;
	QWidget *m_widget = nullptr;
};


