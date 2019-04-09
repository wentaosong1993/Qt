#include "multithread1.h"
#include "QDebug"


MultiThread1::MultiThread1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_thread = new MyThread();	
	m_thread->setObjectName("Main:");
	qDebug() << QStringLiteral("���̣߳�") << m_thread->objectName() << m_thread->currentThread()->currentThreadId();

/*
	m_thread1 = new MyThread();
	m_thread1->setObjectName("child1:");
	m_thread1->run();
	m_thread2 = new MyThread();
	m_thread2->setObjectName("child2:");
	m_thread2->run();

	"���̣߳�" "Main:" 0x2c20
	name: "child1:" "���߳�ID��" 0x2c20
	name: "child2:" "���߳�ID��" 0x2c20
*/


	m_thread1 = new MyThread();
	m_thread1->setObjectName("child1:");
	m_thread1->start();

	m_thread2 = new MyThread();
	m_thread2->setObjectName("child2:");
	m_thread2->run();

/*
"���̣߳�" "Main:" 0x1404
name: "child2:" "���߳�ID��" 0x1404
name: "child1:" "���߳�ID��" 0x2ea8
*/

/*
---------------------------------------------------------------------------------
1��thread1��thread2���߳�ID��ͬ��thread2�����߳�ID��ͬ��˵��ͨ��run�������ò����ᴴ���µ��̣߳����������߳���ֱ������run����������ͨ�ķ�������û���κ�����

2����Ȼthread1��start����������thread2��run����ǰ����ã��������������thread2��run�������õ������Ϣ��˵�����̴߳����Ĺ��̲����������̵߳ĺ���ִ�С�
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
