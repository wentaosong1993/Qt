#include "plaintextedit.h"
#include "messagebox.h"
#include <QMenu>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QClipboard>
#include <QFlags>
#include <QKeySequence>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QDebug>
//#include <QScopedPointer>

TGPlainTextEdit::TGPlainTextEdit(QWidget *parent)
{
	initWindow();
}

TGPlainTextEdit::~TGPlainTextEdit()
{
	if (m_findWidget)
	{
		delete m_findWidget;
		m_findWidget = nullptr;
	}
	/*if (m_keyLabel)
	{
		delete m_keyLabel;
		m_keyLabel = nullptr;
	}
	if (m_keyLineEdit)
	{
		delete m_keyLineEdit;
		m_keyLineEdit = nullptr;
	}
	if (m_findAllButton)
	{
		delete m_findAllButton;
		m_findAllButton = nullptr;
	}*/
}

void TGPlainTextEdit::initWindow()
{
	m_findWidget = new QWidget(this);
	m_findWidget->setStyleSheet("QWidget{background: rgba(153,153,153,150);}");
	m_findWidget->resize(300, 50);
	m_findWidget->setObjectName("findWidget");
	m_findWidget->setWindowTitle(QStringLiteral("�ֶβ�ѯ"));
	m_findWidget->hide();
	m_keyLabel = new QLabel(QStringLiteral("�ؼ��֣�"));
	m_keyLabel->setStyleSheet("QLabel{background: transparent;border: none;}");
	m_keyLineEdit = new QLineEdit;
	m_keyLineEdit->setFixedHeight(28);
	m_keyLineEdit->setContextMenuPolicy(Qt::NoContextMenu);
	m_keyLineEdit->setPlaceholderText(QStringLiteral("�������ѯ�Ĺؼ���"));
	m_keyLineEdit->setStyleSheet("QLineEdit{background:#f9fafc;border:1px solid #d3dce6;padding:0px 4px 0px 4px;color:#222222;font:14px;} \
							      QLineEdit:focus{ background:#ffffff; border:1px solid #20a0ff; padding:0px 4px 0px 4px; color:#222222; font:14px; } \
							      QLineEdit:disabled{ background:#f3f5f7; border:1px solid #d3dce6; padding:0px 4px 0px 4px; color:#c9d0d5; font:14px; }"
								);
	m_findAllButton = new QPushButton(QStringLiteral("����"));
	m_findAllButton->setFixedSize(40, 28);
	m_findAllButton->setStyleSheet("QPushButton{font:14px;color:#ffffff;background-color:#29a1f7;border:0px;border-radius:2px;} \
									QPushButton:hover{ background-color:#4ab0fb; border:0px; border-radius:2px; } \
									QPushButton:pressed{ background-color:#2087d3; border:0px; border-radius:2px; } \
									QPushButton:disabled{ background-color:#c9d0d5; border:0px; border-radius:2px; }"
	);
	m_hLayout = new QHBoxLayout(m_findWidget);
	m_hLayout->addWidget(m_keyLabel);
	m_hLayout->addWidget(m_keyLineEdit);
	m_hLayout->addWidget(m_findAllButton);
	m_hLayout->setSpacing(4);
	m_hLayout->setContentsMargins(10, 10, 20, 10);
	m_findWidget->setLayout(m_hLayout);

	connect(m_keyLineEdit, &QLineEdit::returnPressed, this, &TGPlainTextEdit::findText);
	connect(m_findAllButton, &QPushButton::clicked, this, &TGPlainTextEdit::findText);
	connect(this, SIGNAL(textChanged()),this,SLOT(clearFormat()));

	this->installEventFilter(this);
	m_keyLineEdit->installEventFilter(this);
}


void TGPlainTextEdit::setOriginKeyword(QString keyStr)
{
	m_originKeyword = keyStr;
}

void TGPlainTextEdit::setNumToZero(int num)
{
	m_num = num;
}

void TGPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
 {
 	QMenu *menu = createStandardContextMenu();
	menu->clear();
	QAction *a;
	{
		a = menu->addAction(QString::fromLocal8Bit("����(&C)") + INSTALL_KEY(QKeySequence::Copy), this, SLOT(copy()));
		a->setEnabled(this->textCursor().hasSelection());
	}
	{
		a = menu->addAction(QString::fromLocal8Bit("����(&F)") + INSTALL_KEY(QKeySequence::Find), this, SLOT(findDlgShow()));
		a->setEnabled(!m_findWidget->isVisible());
	}
	{
		a = menu->addAction(QString::fromLocal8Bit("�رղ���(&W)") + INSTALL_KEY(QKeySequence::Close), this, SLOT(closeFindDlg()));
		a->setEnabled(m_findWidget->isVisible());
	}
	{
 		a = menu->addAction(QString::fromLocal8Bit("���(&Del)") + INSTALL_KEY(QKeySequence::Delete), this, SLOT(clear()));
	}
 	menu->exec(event->globalPos());
 	delete menu;
 }

bool TGPlainTextEdit::eventFilter(QObject *obj, QEvent *eve)
{
	if (m_keyLineEdit == obj)
	{
		QMouseEvent *mouseEve = static_cast<QMouseEvent *>(eve);
		if (eve->type() == QEvent::MouseButtonPress)
		{
			const QMimeData *mimeData = QApplication::clipboard()->mimeData();
			if (mimeData->hasText())
			{
				m_keyLineEdit->setText(mimeData->text());
			}
			else
			{
				m_keyLineEdit->setText("");
			}
			return __super::eventFilter(obj, eve);
		}
	}

	if (eve->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(eve);
		if (keyEvent->modifiers() == Qt::ControlModifier)
		{
			int key = keyEvent->key();
			if (key == Qt::Key_F)
			{
				QApplication::clipboard()->clear(QClipboard::Clipboard);
				m_findWidget->show();
				return true;
			}
			if (key == Qt::Key_W)
			{
				m_keyLineEdit->setText("");
				m_findWidget->close();
				QApplication::clipboard()->clear(QClipboard::Clipboard);
				return true;
			}
			if (key == Qt::Key_C)
			{
				copy();
				return __super::eventFilter(obj, eve);
			}
			if (key == Qt::Key_Delete)
			{
				clear();
				QApplication::clipboard()->clear(QClipboard::Clipboard);
				return __super::eventFilter(obj, eve);
			}
			return __super::eventFilter(obj, eve);
		}
		return __super::eventFilter(obj, eve);
	}
	return __super::eventFilter(obj, eve);
}

void TGPlainTextEdit::resizeEvent(QResizeEvent *eve)
{
	m_findWidget->move(this->width() - m_findWidget->width(), 0);
	__super::resizeEvent(eve);
}

void TGPlainTextEdit::findText()
{
	//�����һ�β��ҵĸ�ʽ
	QFlags<QTextDocument::FindFlag> options = QTextDocument::FindWholeWords;//default insensitive
	if (!m_originKeyword.isEmpty())
	{
		QTextDocument *document = this->document();
		QTextCursor highlightCursor(document);

		//��Ҫ�����α�,���ûᵼ����ͨ�ı�������ý������ʾ�������ݵ�bug
		QTextCursor cursor(document);
		cursor.beginEditBlock();
		//cursor.setKeepPositionOnInsert(true);
		QTextCharFormat colorFormat1 = highlightCursor.charFormat();
		colorFormat1.setForeground(Qt::black);
		colorFormat1.setBackground(Qt::white);

		while (!highlightCursor.isNull() && !highlightCursor.atEnd())
		{
			highlightCursor = document->find(m_originKeyword, highlightCursor, options);
			if (!highlightCursor.isNull())
			{
				highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
				highlightCursor.mergeCharFormat(colorFormat1);
			}
		}
		cursor.endEditBlock();
		setOriginKeyword("");
	}

	//���ҹؼ���
	bool find = false;
	QString searchString = m_keyLineEdit->text().trimmed();
	if (searchString.isEmpty())
	{
		CMessageBox::warning(this, QStringLiteral("����ʧ��"), QStringLiteral("�Բ���,��Ĳ�ѯ����Ϊ��,����������!"));
	}
	else
	{
		QTextDocument *document = this->document();
		QTextCursor highlightCursor(document);

		QTextCursor cursor(document);
		cursor.beginEditBlock();
		//cursor.setKeepPositionOnInsert(true);
		QTextCharFormat colorFormat = highlightCursor.charFormat();
		colorFormat.setForeground(Qt::red);
		colorFormat.setBackground(Qt::yellow);

		while (!highlightCursor.isNull() && !highlightCursor.atEnd())
		{
			highlightCursor = document->find(searchString, highlightCursor, options);
			if (!highlightCursor.isNull())
			{
				find = true;
				setOriginKeyword(searchString);
				highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
				highlightCursor.mergeCharFormat(colorFormat);
				//ʵ��slider����������ֶ�position
				if (++m_num == 1)
				{
					this->verticalScrollBar()->setValue(highlightCursor.position());
				}
			}
		}
		//QTextCharFormat colorFormat2 = highlightCursor.charFormat();
		//colorFormat2.setForeground(Qt::black);
		//colorFormat2.setBackground(Qt::white);
		//cursor.endEditBlock();
		//highlightCursor.setCharFormat(colorFormat2);
		//highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::MoveAnchor);
		//highlightCursor.mergeCharFormat(colorFormat2);
		//highlightCursor.clearSelection();
		//highlightCursor.setPosition(highlightCursor.anchor());

		if (!find)
		{
			CMessageBox::warning(this, QStringLiteral("��ѯʧ��"), QStringLiteral("�Բ�������û���ҵ����ֶ�."));
		}
		setNumToZero(0);
	}
}

void TGPlainTextEdit::findDlgShow()
{
	QApplication::clipboard()->clear(QClipboard::Clipboard);
	m_findWidget->show();
}

void TGPlainTextEdit::closeFindDlg()
{
	m_keyLineEdit->setText("");
	m_findWidget->close();
	QApplication::clipboard()->clear(QClipboard::Clipboard);
}

void TGPlainTextEdit::clearFormat()
{
	QFlags<QTextDocument::FindFlag> options = QTextDocument::FindWholeWords;//default insensitive
	QTextDocument *document = this->document();
	QTextCursor highlightCursor(document);

	QTextCursor cursor(document);
	QTextCharFormat colorFormat = highlightCursor.charFormat();
	colorFormat.setForeground(Qt::white);
	colorFormat.setBackground(Qt::black);

	while (!highlightCursor.isNull() && highlightCursor.atEnd())
	{
		highlightCursor = document->find("", highlightCursor, options);
		if (!highlightCursor.isNull())
		{
			highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
			highlightCursor.mergeCharFormat(colorFormat);
		}
	}
	//QTextCharFormat colorFormat2 = highlightCursor.charFormat();
	//colorFormat2.setForeground(Qt::black);
	//colorFormat2.setBackground(Qt::white);
	//cursor.endEditBlock();
	//highlightCursor.setCharFormat(colorFormat2);
	//highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::MoveAnchor);
	//highlightCursor.mergeCharFormat(colorFormat2);
	//highlightCursor.clearSelection();
	//highlightCursor.setPosition(highlightCursor.anchor());
}

