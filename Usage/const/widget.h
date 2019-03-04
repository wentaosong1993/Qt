#ifndef WIDGET_H
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





