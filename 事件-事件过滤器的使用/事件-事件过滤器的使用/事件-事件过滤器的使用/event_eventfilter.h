#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_event_eventfilter.h"
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QEnterEvent>
#include <QHoverEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QPushButton>
#include <QFocusEvent>

class Event_EventFilter : public QMainWindow
{
	Q_OBJECT

public:
	Event_EventFilter(QWidget *parent = Q_NULLPTR);
	~Event_EventFilter();
protected:
	virtual bool event(QEvent *event) override;
	virtual bool eventFilter(QObject *watched, QEvent *event) override;

	virtual void keyPressEvent(QKeyEvent *event) override;
	virtual void keyReleaseEvent(QKeyEvent *event) override;

	virtual void enterEvent(QEvent *event) override;
	virtual void leaveEvent(QEvent *event) override;

	virtual void dragEnterEvent(QDragEnterEvent *event) override;
	virtual void dragMoveEvent(QDragMoveEvent *event) override;
	virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
	virtual void dropEvent(QDropEvent *event) override;

	virtual void focusInEvent(QFocusEvent *event) override;
	virtual void focusOutEvent(QFocusEvent *event) override;

	virtual void hideEvent(QHideEvent *event) override;

	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

	virtual void moveEvent(QMoveEvent *event) override;
	virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
	virtual void paintEvent(QPaintEvent *event) override;
	virtual void resizeEvent(QResizeEvent *event) override;
	virtual void showEvent(QShowEvent *event) override;
	virtual void wheelEvent(QWheelEvent *event) override;

	virtual void closeEvent(QCloseEvent *event) override;

public slots:
	//void on_pushButton_clicked();
	void pushButton1Clicked();

private:
	Ui::Event_EventFilterClass ui;
};
