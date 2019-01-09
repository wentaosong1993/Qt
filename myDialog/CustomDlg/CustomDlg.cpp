#include "CustomDlg.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>

CustomDlg::CustomDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setWindowOpacity(0.99);
	setAttribute(Qt::WA_AlwaysShowToolTips);

	ui.labelTitle->setText(QStringLiteral("2019£¬ÐÂÄê¿ìÀÖ"));
	ui.frameTitle->installEventFilter(this);
	connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	
}

bool CustomDlg::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::MouseButtonPress:
		if (obj == ui.frameTitle)
		{
			QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
			if (mouseEvent && mouseEvent->button() == Qt::LeftButton)
			{
				m_drag = true;
				m_DragPosition = mouseEvent->globalPos() - this->pos();
				return true;
			}
		}
		break;
	case QEvent::MouseMove:
	{
		QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
		if (m_drag && mouseEvent && mouseEvent->buttons() && Qt::LeftButton)
		{
			QRect rect = QApplication::desktop()->availableGeometry();
			QPoint topLeftDlgPoint = mouseEvent->globalPos() - m_DragPosition;
			if (!rect.contains(topLeftDlgPoint))
			{
				QPoint topLeftPoint = rect.topLeft();
				if (topLeftDlgPoint.y() < topLeftPoint.y())
				{
					topLeftDlgPoint.setY(topLeftPoint.y());
				}
			}
			move(topLeftDlgPoint);
			return true;
		}
	}
	break;
		
	case QEvent::MouseButtonRelease:
	{
		m_drag = false;
		return true;
	}
	break;
		
	default:
		break;
	}
	return QDialog::eventFilter(obj, event);
}

void CustomDlg::okClicked()
{
	accept();
}
