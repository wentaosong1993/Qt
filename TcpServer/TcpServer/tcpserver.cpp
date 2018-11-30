#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent,f)
{
    setWindowTitle(QStringLiteral("Tcp Server"));
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel(QStringLiteral("端口"));
    PortLineEdit = new QLineEdit;
    CreateBtn = new QPushButton(QStringLiteral("创建聊天室"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(CreateBtn,2,0,1,2);
}

TcpServer::~TcpServer()
{

}

