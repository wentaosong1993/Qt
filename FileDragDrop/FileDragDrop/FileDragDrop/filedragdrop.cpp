#include "filedragdrop.h"

FileDragDrop::FileDragDrop(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//setAcceptDrops(true);
}

//void FileDragDrop::dragEnterEvent(QDragEnterEvent *e)
//{
//	if (e->mimeData()->hasUrls())
//	{
//		e->acceptProposedAction();
//	}
//	else
//	{
//		e->ignore();
//	}
//}


//void FileDragDrop::dropEvent(QDropEvent *e)
//{
//	const QMimeData* mimeData = e->mimeData();
//	if (mimeData->hasUrls())
//	{
//		QList<QUrl> urlList = mimeData->urls();
//		QString fileName = urlList.at(0).toLocalFile();
//		if (!fileName.isEmpty())
//		{
//			QFile file(fileName);
//			if (!file.open(QIODevice::ReadOnly))
//				return;
//			else
//			{
//				QTextStream textStream(&file);
//				QString str = textStream.readAll();
//				//ui.textEdit->setText();
//			}
//		}
//	}
//}
