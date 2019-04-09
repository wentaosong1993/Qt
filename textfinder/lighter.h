#pragma once
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE


class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	Highlighter(QTextDocument *parent = 0);
	void setChocedStyle();
	void setNormalStyle();
	QString getSearthStr();
	void setSearthStr(QString str);

protected:
	void highlightBlock(const QString &text) override;

private:
	/*struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};
	QVector<HighlightingRule> highlightingRules;

	QRegExp commentStartExpression;
	QRegExp commentEndExpression;

	
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;*/

	//QTextCharFormat m_keyNormalFormat;
	QTextCharFormat m_keyChocedFormat;
	QString m_keyword;
};
