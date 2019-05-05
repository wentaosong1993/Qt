#include "mytextedit.h"


DropTextEdit::DropTextEdit(QWidget *parent /*= nullptr*/)
{
	setAcceptDrops(true);
}

//有文件拖动到窗口上时，触发此dragEnterEvent事件
void DropTextEdit::dragEnterEvent(QDragEnterEvent *e)
{
	if (e->mimeData()->hasUrls())
	{
		e->acceptProposedAction();
	}
	else
	{
		e->ignore();
	}
}


void DropTextEdit::dropEvent(QDropEvent *e)
{
	const QMimeData* mimeData = e->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();
		QString fileName = urlList.at(0).toLocalFile();
		if (!fileName.isEmpty())
		{
			QFile file(fileName);
			if (!file.open(QIODevice::ReadOnly))
				return;
			else
			{
				QTextStream textStream(&file);
				QString str = textStream.readAll();
				this->setText(str);
			}
		}
	}
}

