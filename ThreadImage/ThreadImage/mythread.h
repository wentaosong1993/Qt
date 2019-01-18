﻿#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    void drawImage();
signals:
    void updateImage(QImage image);

public slots:

};

#endif // MYTHREAD_H
