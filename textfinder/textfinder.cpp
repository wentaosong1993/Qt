
#include <QtUiTools>
#include <QtWidgets>
#include "textfinder.h"


TextFinder::TextFinder(QWidget *parent)
    : QWidget(parent)
{
    QWidget *formWidget = loadUiFile();

//! [1]
    ui_findButton = findChild<QPushButton*>("findButton");
    ui_textEdit = findChild<QTextEdit*>("textEdit");
    ui_lineEdit = findChild<QLineEdit*>("lineEdit");
//! [0] //! [1]

//! [2]
    QMetaObject::connectSlotsByName(this);
//! [2]

//! [3a]
    loadTextFile();
//! [3a]

//! [3b]
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    setLayout(layout);
//! [3b]

//! [3c]
    setWindowTitle(tr("Text Finder"));
    //isFirstTime = true;
}
//! [3c]

void TextFinder::setOriginText(QString str)
{
	m_originText = str;
}

//! [4]
    ui_findButton = findChild<QPushButton*>("findButton");
    ui_textEdit = findChild<QTextEdit*>("textEdit");
    ui_lineEdit = findChild<QLineEdit*>("lineEdit");



    QMetaObject::connectSlotsByName(this);



    loadTextFile();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    setLayout(layout);

    setWindowTitle(tr("Text Finder"));
    isFirstTime = true;
}

QWidget* TextFinder::loadUiFile()
{
    QUiLoader loader;

    QFile file(":/forms/textfinder.ui");
    file.open(QFile::ReadOnly);

    QWidget *formWidget = loader.load(&file, this);
    file.close();

    return formWidget;
}


void TextFinder::loadTextFile()
{
    QFile inputFile(":/forms/input.txt");
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui_textEdit->append(line);
    ui_textEdit->setUndoRedoEnabled(false);
    ui_textEdit->setUndoRedoEnabled(true);
}


void TextFinder::on_findButton_clicked()
{
    QString searchString = ui_lineEdit->text();
    QTextDocument *document = ui_textEdit->document();

	if (!document)
	{
		return;
	}

	m_lighter = new Highlighter(document);

#if 0 
	//�൱��������֮ǰ�����ĵ���ʽ
	if (!m_originText.isEmpty())
	{
		m_lighter->setSearthStr(m_originText);
		m_lighter->setNormalStyle();
	}
#endif

#if 1
// �൱����ʽ��������ģʽ��ƥ��ؼ��ֶ�
	if (searchString.isEmpty())
	{
		setOriginText("");
		QMessageBox::information(this, tr("Empty Search Field"),
			"The search field is empty. Please enter a word and click Find.");
	}
	else
	{
		//�ĵ��д��ڸ��ֶεĻ�������ͻ����ʾ�ĵ������еĸ��ֶΣ���������Ĭ�ϵ������ϵ�һ����λ��
		if (document->toPlainText().contains(searchString))
		{
			m_lighter->setSearthStr(searchString);
			m_lighter->setChocedStyle();
			setOriginText(searchString);
		}
		else
		{
			QMessageBox::information(this, tr("Word Not Found"),
			 "Sorry, the word cannot be found.");
		}
	}
#endif 
}


