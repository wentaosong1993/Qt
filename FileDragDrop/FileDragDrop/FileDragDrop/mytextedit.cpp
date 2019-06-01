#include "mytextedit.h"
#include <QFileIconProvider>
#include <QTextCursor>

TemplateWidget::TemplateWidget(QString fileName, QWidget *parent /*= nullptr*/)
{
	m_Button = new QPushButton(this);
	m_Button->setObjectName("m_Button");
	m_Button->setFixedSize(270, 50);
	m_Button->setStyleSheet("QPushButton#m_Button{background-color: white;color: black;border: 1px solid grey;}");

	QFileIconProvider iconProvider;
	QFileInfo file(fileName);
	QString fileShortName = fileName.mid(fileName.lastIndexOf("/") + 1);//文件名
	double fileSize = (double)file.size();//文件大小

	m_fileImg = new QLabel;
	m_fileImg->setFixedSize(30, 40);
	QIcon icon = iconProvider.icon(file);//应用程序的图片
	QPixmap pixmap = icon.pixmap(30, 40);
	m_fileImg->setPixmap(pixmap);
	m_fileNameLabel = new QLabel;
	m_fileNameLabel->setText(fileShortName);

	m_fileSize = new QLabel;
	if (fileSize > 1024)
	{
		fileSize = fileSize / 1024.0;
		m_fileSize->setText(QString::number(fileSize) + "K");
	}
	else
	{
		m_fileSize->setText(QString::number(fileSize) + "B");
	}
	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->addWidget(m_fileImg, 1, 1, 2, 1/*, Qt::AlignLeft*/);
	gridLayout->addWidget(m_fileNameLabel, 1, 2, 1, 1/*, Qt::AlignLeft*/);
	gridLayout->addWidget(m_fileSize, 2, 2, 1, 1/*, Qt::AlignLeft*/);
	gridLayout->setContentsMargins(5, 5, 5, 5);
	gridLayout->setHorizontalSpacing(5);
	m_Button->setLayout(gridLayout);
	//m_Button->show();
}

TemplateWidget::~TemplateWidget()
{
	if (m_fileImg)
	{
		delete m_fileImg;
		m_fileImg = nullptr;
	}
	if (m_fileNameLabel)
	{
		delete m_fileNameLabel;
		m_fileNameLabel = nullptr;
	}
	if (m_fileSize)
	{
		delete m_fileSize;
		m_fileSize = nullptr;
	}
}

void TemplateWidget::focusInEvent(QFocusEvent *event)
{
	this->setStyleSheet("QPushButton#m_Button{border: 1px solid black;}");
}

void TemplateWidget::focusOutEvent(QFocusEvent *event)
{
	this->setStyleSheet("QPushButton#m_Button{border: 1px solid grey;}");
}



DropTextEdit::DropTextEdit(QWidget *parent /*= nullptr*/)
{
	setAcceptDrops(true);
}

DropTextEdit::~DropTextEdit()
{
	if (m_templateWidget)
	{
		delete m_templateWidget;
		m_templateWidget = nullptr;
	}
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

void DropTextEdit::dragMoveEvent(QDragMoveEvent *e)
{
	e->setDropAction(Qt::MoveAction);
}

void DropTextEdit::dropEvent(QDropEvent *e)
{
	const QMimeData* mimeData = e->mimeData();
	if (mimeData->hasUrls())
    {
		QList<QUrl> urlList = mimeData->urls();
		QString fileName = QString("");
		//m_flowLayout = new FlowLayout(this,4,10,3);
		//m_flowLayout->setParent(this);
		for (int i = 0; i < urlList.size(); i++)
		{
			fileName = urlList.at(i).toLocalFile();
			if (!fileName.isEmpty())
			{
				//m_templateWidget = new TemplateWidget(fileName,(QWidget*)m_flowLayout);
				//m_templateWidget->show();

				m_templateWidget = new TemplateWidget(fileName, this);
				m_templateWidget->setParent(this);
				m_templateWidget->show();
			}
		}
	}
}


