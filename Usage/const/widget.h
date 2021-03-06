﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H


/*
前面使用const 表示返回值为const
后面加 const表示函数不可以修改class的成员s
*/
#ifndef FUNCTIONCONST_H_
#define FUNCTIONCONST_H_

class FunctionConst {
public:
	int value;
	FunctionConst();
	virtual ~FunctionConst();
	const int getValue();
	int getValue2() const;
};

#endif /* FUNCTIONCONST_H_ */





