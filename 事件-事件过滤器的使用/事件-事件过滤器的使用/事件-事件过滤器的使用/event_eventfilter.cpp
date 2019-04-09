#include "event_eventfilter.h"
#include <QDebug>

Event_EventFilter::Event_EventFilter(QWidget *parent)
	: QMainWindow(parent)
{
	//QPushButton * pushButton = new QPushButton(this);
	//pushButton->setObjectName("pushButton");
	ui.setupUi(this);
	ui.pushButton1->installEventFilter(this);
	//pushButton->installEventFilter(this);
	//connect(ui.pushButton1,&QPushButton::clicked,this,&Event_EventFilter::pushButton1Clicked);
	connect(ui.pushButton1,SIGNAL(clicked()),this,SLOT(pushButton1Clicked()));
}

Event_EventFilter::~Event_EventFilter()
{
}

bool Event_EventFilter::eventFilter(QObject *watched, QEvent *event)
{
	if (ui.pushButton1 == watched)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			qDebug() << "MouseButtonPress";
			return __super::eventFilter(watched, event);
		}
		return __super::eventFilter(watched, event);
	}
	return __super::eventFilter(watched, event);
}

void Event_EventFilter::keyPressEvent(QKeyEvent *event)
{
	__super::keyPressEvent(event);
}

void Event_EventFilter::keyReleaseEvent(QKeyEvent *event)
{
	__super::keyReleaseEvent(event);
}

void Event_EventFilter::enterEvent(QEvent *event)
{
	__super::enterEvent(event);
}

void Event_EventFilter::leaveEvent(QEvent * event)
{
	__super::leaveEvent(event);
}

void Event_EventFilter::dragEnterEvent(QDragEnterEvent * event)
{
	__super::dragEnterEvent(event);
}

void Event_EventFilter::dragMoveEvent(QDragMoveEvent * event)
{
	__super::dragMoveEvent(event);
}

void Event_EventFilter::dragLeaveEvent(QDragLeaveEvent * event)
{
	__super::dragLeaveEvent(event);
}

void Event_EventFilter::dropEvent(QDropEvent * event)
{
	__super::dropEvent(event);
}

void Event_EventFilter::focusInEvent(QFocusEvent * event)
{
	__super::focusInEvent(event);
}

void Event_EventFilter::focusOutEvent(QFocusEvent * event)
{
	__super::focusOutEvent(event);
}

void Event_EventFilter::hideEvent(QHideEvent * event)
{
	__super::hideEvent(event);
}

void Event_EventFilter::mousePressEvent(QMouseEvent * event)
{
	__super::mousePressEvent(event);
}

void Event_EventFilter::mouseMoveEvent(QMouseEvent * event)
{
	__super::mouseMoveEvent(event);
}

void Event_EventFilter::mouseReleaseEvent(QMouseEvent * event)
{
	__super::mouseReleaseEvent(event);
}

void Event_EventFilter::mouseDoubleClickEvent(QMouseEvent * event)
{
	__super::mouseDoubleClickEvent(event);
}

void Event_EventFilter::moveEvent(QMoveEvent * event)
{
	__super::moveEvent(event);
}

bool Event_EventFilter::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
	return false;
}

void Event_EventFilter::paintEvent(QPaintEvent * event)
{
	__super::paintEvent(event);
}

void Event_EventFilter::resizeEvent(QResizeEvent * event)
{
	__super::resizeEvent(event);
}

void Event_EventFilter::showEvent(QShowEvent * event)
{
	__super::showEvent(event);
}

void Event_EventFilter::wheelEvent(QWheelEvent * event)
{
	__super::wheelEvent(event);
}

void Event_EventFilter::closeEvent(QCloseEvent *event)
{
	close();
	__super::closeEvent(event);
	//QWidget::closeEvent(event);
}

void Event_EventFilter::pushButton1Clicked()
{
	qDebug() << "pushButton1 clicked!~";
}

//void Event_EventFilter::on_pushButton_clicked()
//{
//	qDebug() << "pushButton clicked!";
//}

bool Event_EventFilter::event(QEvent * event)
{
	switch (event->type())
	{
	case QEvent::Close:
	{
		QCloseEvent *closeEve = dynamic_cast<QCloseEvent *>(event);
		closeEvent(closeEve);
		return true;
	}
	case QEvent::MouseButtonPress:
	{
		QMouseEvent *mouseEve = dynamic_cast<QMouseEvent *>(event);
		mousePressEvent(mouseEve);
		return true;
	}

	case QEvent::MouseMove:
	{
		QMouseEvent *mouseEve = dynamic_cast<QMouseEvent *>(event);
		mouseMoveEvent(mouseEve);
		return true;
	}

	case QEvent::MouseButtonRelease:
	{
		QMouseEvent *mouseEve = dynamic_cast<QMouseEvent *>(event);
		mouseReleaseEvent(mouseEve);
		return true;
	}
	case QEvent::MouseButtonDblClick:
	{
		QMouseEvent *mouseEve = dynamic_cast<QMouseEvent *>(event);
		mouseDoubleClickEvent(mouseEve);
		return true;
	}
	case QEvent::KeyPress:
	{
		QKeyEvent *keyPressEve = dynamic_cast<QKeyEvent *>(event);
		keyPressEvent(keyPressEve);
		return true;
	}
	case QEvent::KeyRelease:
	{
		QKeyEvent *keyReleaseEve = dynamic_cast<QKeyEvent *>(event);
		keyReleaseEvent(keyReleaseEve);
		return true;
	}
	case QEvent::Enter:
	{
		enterEvent(event);
		return true;
	}
	case QEvent::Leave:
	{
		leaveEvent(event);
		return true;
	}
	case QEvent::DragEnter:
	{
		QDragEnterEvent *dragEve = dynamic_cast<QDragEnterEvent *>(event);
		dragEnterEvent(dragEve);
		return true;
	}
	case QEvent::DragMove:
	{
		QDragMoveEvent *dragMoveEve = dynamic_cast<QDragMoveEvent *>(event);
		dragMoveEvent(dragMoveEve);
		return true;
	}
	case QEvent::DragLeave:
	{
		QDragLeaveEvent *dragLeaveEve = dynamic_cast<QDragLeaveEvent *>(event);
		dragLeaveEvent(dragLeaveEve);
		return true;
	}
	case QEvent::Drop:
	{
		QDropEvent * dropEve = dynamic_cast<QDropEvent *>(event);
		dropEvent(dropEve);
		return true;
	}
	case QEvent::Hide:
	{
		QHideEvent *hideEve = dynamic_cast<QHideEvent *>(event);
		hideEvent(hideEve);
		return true;
	}
	case QEvent::Move:
	{
		QMoveEvent *moveEve = dynamic_cast<QMoveEvent *>(event);
		moveEvent(moveEve);
		return true;
	}
	case QEvent::Paint:
	{
		QPaintEvent *paintEve = dynamic_cast<QPaintEvent *>(event);
		paintEvent(paintEve);
		return true;
	}
	case QEvent::Show:
	{
		QShowEvent *showEve = dynamic_cast<QShowEvent *>(event);
		showEvent(showEve);
		return true;
	}
	case QEvent::Wheel:
	{
		QWheelEvent *wheelEve = dynamic_cast<QWheelEvent *>(event);
		wheelEvent(wheelEve);
		return true;
	}
	case QEvent::Resize:
	{
		QResizeEvent *resizeEve = dynamic_cast<QResizeEvent *>(event);
		resizeEvent(resizeEve);
		return true;
	}
	case QEvent::FocusIn:
	{
		QFocusEvent *focusEve = dynamic_cast<QFocusEvent *>(event);
		focusInEvent(focusEve);
		return true;
	}
	case QEvent::FocusOut:
	{
		QFocusEvent *focusEve = dynamic_cast<QFocusEvent *>(event);
		focusOutEvent(focusEve);
		return true;
	}
	default:
		break;
	}
	return __super::event(event);
}
