#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	FunctionConst func;
	func.getValue();
	func.getValue2();
}

Widget::~Widget()
{
}



FunctionConst::FunctionConst() :value(100) {
	// TODO Auto-generated constructor stub

}

FunctionConst::~FunctionConst() {
	// TODO Auto-generated destructor stub
}

const int FunctionConst::getValue() {
	return value;//返回值是 const, 使用指针时很有用.
}

int FunctionConst::getValue2() const {
	//此函数不能修改class FunctionConst的成员函数 value
	value = 15;//错误的, 因为函数后面加 const
	return value;
}

/*
1>widget.cpp(30): error C3490: 由于正在通过常量对象访问“value”，因此无法对其进行修改
========== 生成: 成功 0 个，失败 1 个，最新 0 个，跳过 0 个 ==========
*/


