#include "lighter.h"
#include <QRegExp>

Highlighter::Highlighter(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{

}

void Highlighter::setChocedStyle()
{
	m_keyChocedFormat.setFontWeight(QFont::Bold);
	m_keyChocedFormat.setForeground(Qt::red);
	m_keyChocedFormat.setBackground(Qt::yellow);
}	

void Highlighter::setNormalStyle()
{
	m_keyChocedFormat.setForeground(Qt::black);	
	m_keyChocedFormat.setFontWeight(QFont::Bold);
	m_keyChocedFormat.setBackground(Qt::white);
}

QString Highlighter::getSearthStr()
{
	return m_keyword;
}

void Highlighter::setSearthStr(QString str)
{
	m_keyword = str;
}

void Highlighter::highlightBlock(const QString & text)
{
	int i = 0; 
	QString keyword = getSearthStr();
	QRegExp expression(keyword);
	int index = expression.indexIn(text);
	while (index >= 0) 
	{
		int length = expression.matchedLength();
		setFormat(index, length, m_keyChocedFormat);
		if (++i == 1)
		{
			//�ҵ���һ���ֶε�λ��
			//��һ���û�����λ��ȥ
		}
		index = expression.indexIn(text, index + length);
	}
}
