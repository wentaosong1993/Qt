#ifndef TIMESERVER_H
#define TIMESERVER_H

#include <QTcpServer>

class Dialog;

class TimeServer : public QTcpServer
{
public:
    TimeServer(QObject *parent = Q_NULLPTR);
protected:
    void incomingConnection(int socketDescriptor);

private:
    Dialog *dlg;
};

#endif // TIMESERVER_H
