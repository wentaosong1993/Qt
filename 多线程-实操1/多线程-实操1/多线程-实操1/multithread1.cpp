#include "multithread1.h"
#include "QDebug"


MultiThread1::MultiThread1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_thread = new MyThread();	
	m_thread->setObjectName("Main:");
	qDebug() << QStringLiteral("主线程：") << m_thread->objectName() << m_thread->currentThread()->currentThreadId();

/*
	m_thread1 = new MyThread();
	m_thread1->setObjectName("child1:");
	m_thread1->run();
	m_thread2 = new MyThread();
	m_thread2->setObjectName("child2:");
	m_thread2->run();

	"主线程：" "Main:" 0x2c20
	name: "child1:" "子线程ID：" 0x2c20
	name: "child2:" "子线程ID：" 0x2c20
*/


	m_thread1 = new MyThread();
	m_thread1->setObjectName("child1:");
	m_thread1->start();

	m_thread2 = new MyThread();
	m_thread2->setObjectName("child2:");
	m_thread2->run();

/*
"主线程：" "Main:" 0x1404
name: "child2:" "子线程ID：" 0x1404
name: "child1:" "子线程ID：" 0x2ea8
*/

/*
---------------------------------------------------------------------------------
1）thread1和thread2的线程ID不同，thread2和主线程ID相同，说明通过run方法调用并不会创建新的线程，而是在主线程中直接运行run方法，跟普通的方法调用没有任何区别；

2）虽然thread1的start方法调用在thread2的run方法前面调用，但是先输出的是thread2的run方法调用的相关信息，说明新线程创建的过程不会阻塞主线程的后续执行。
---------------------------------------------------------------------------------
*/


}

MultiThread1::~MultiThread1()
{
	if (m_thread)
	{
		delete m_thread;
		m_thread = nullptr;
	}
	if (m_thread1)
	{
		delete m_thread1;
		m_thread1 = nullptr;
	}
	if (m_thread2)
	{
		delete m_thread2;
		m_thread2 = nullptr;
	}
}
