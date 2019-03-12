#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <stdio.h>
const int DataSize = 1000;
const int BufferSize = 80;
int buffer[BufferSize];
QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes(0);


class Producer: public QThread
{
public:
    Producer();
    ~Producer();
    virtual  void run() override;
};

Producer::Producer()
{

}
Producer::~Producer()
{

}

void Producer::run()
{
    for(int i = 0; i < DataSize; i++)
    {
        freeBytes.acquire();//生产者线程首先获取一个空闲单元，如果此时缓冲区被消费者尚未读取的数据填满，对此函数的调用就会阻塞，直到消费者读取了这些数据为止。
        buffer[i % BufferSize] = (i % BufferSize);// 一旦生产者获取了某个空闲单元，就是用当前的缓冲区单元序号填写这个缓冲区单元。
        usedBytes.release();//调用该函数将可用资源加1，表示消费者此时可以读取这个刚刚填写的单元了
    }
}


class Consumer : public QThread
{
public:
    Consumer();
    ~Consumer();
    virtual void run() override;
};

Consumer::Consumer()
{

}

Consumer::~Consumer()
{

}


void Consumer::run()
{
    for(int i = 0; i < DataSize;i++)
    {
        usedBytes.acquire();//消费者线程获取一个可被读取的单元，如果没有包含任何可以读取的数据，对此函数的调用就会阻塞，直到生产者生产了一些数据为止
        fprintf(stderr,"%d",buffer[i%BufferSize]);
        if(i%16 == 0 && i != 0)
            fprintf(stderr,"\n");
        freeBytes.release();//调用该函数使得这个单元变为空闲，以备生产者下次填充
    }
    fprintf(stderr,"\n");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Producer producer;
    Consumer consumer;

	/*启动生产者和消费者线程*/
    producer.start();
    consumer.start();

	/*等待生产者和消费者各自执行完毕之后自动退出*/
    producer.wait();
    consumer.wait();

    return a.exec();
}
