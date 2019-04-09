#pragma once
#include <qplaintextedit.h>
#include "qwidget.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QPlainTextEdit;

class TGPlainTextEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	TGPlainTextEdit(QWidget *parent = Q_NULLPTR);
	~TGPlainTextEdit();

	void initWindow();
	void setOriginKeyword(QString keyStr);
	void setNumToZero(int num);

 protected:
 	void contextMenuEvent(QContextMenuEvent *event) override;
	void resizeEvent(QResizeEvent *eve) override;
	bool eventFilter(QObject *obj, QEvent *eve) override;

public slots:
	void findText();
	void findDlgShow();
	void closeFindDlg();
	void clearFormat();

private:
	bool m_isFirstTime = false;
	int m_num = 0;
	QString m_originKeyword = QString("");
	QWidget *m_findWidget = nullptr;
	QLabel *m_keyLabel = nullptr;
	QLineEdit *m_keyLineEdit = nullptr;
	QPushButton *m_findAllButton = nullptr;
	QHBoxLayout *m_hLayout = nullptr;
	QTextDocument *m_document = nullptr;
};
