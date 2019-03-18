#pragma once

#include <QtWidgets/QWidget>
#include "ui_multithread1.h"
#include "mythread.h"

class MultiThread1 : public QWidget
{
	Q_OBJECT

public:
	MultiThread1(QWidget *parent = Q_NULLPTR);
	~MultiThread1();

private:
	Ui::MultiThread1Class ui;
	MyThread *m_thread;
	MyThread *m_thread1;
	MyThread *m_thread2;


};
