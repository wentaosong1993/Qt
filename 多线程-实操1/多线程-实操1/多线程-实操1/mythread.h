#pragma once
#include <QThread>

class MyThread :public QThread
{
public:
	MyThread();
	~MyThread();
	
	virtual void run() override;
};