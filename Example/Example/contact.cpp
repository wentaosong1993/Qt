#include "contact.h"

Contact::Contact(QWidget *parent)
    :QWidget(parent)
{
    emailLabel = new QLabel(QStringLiteral("电子邮件:"));
    emailLineEdit = new QLineEdit;
    addrLabel = new QLabel(QStringLiteral("联系地址"));
    addrLineEdit = new QLineEdit;
    codeLabel = new QLabel(QStringLiteral("邮政编码:"));
    codeLineEdit = new QLineEdit;

    movieLabel = new QLabel(QStringLiteral("移动电话:"));
    movieLineEdit  = new QLineEdit;
    movieTelCheckBox = new QCheckBox(QStringLiteral("接受留言"));
    protelLabel = new QLabel(QStringLiteral("办公电话"));
    proTelLineEdit = new QLineEdit;

    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(emailLabel,0,0);
    mainLayout->addWidget(emailLineEdit,0,1);
    mainLayout->addWidget(addrLabel,1,0);
    mainLayout->addWidget(addrLineEdit,1,1);
    mainLayout->addWidget(codeLabel,2,0);
    mainLayout->addWidget(codeLineEdit,2,1);
    mainLayout->addWidget(movieLabel,3,0);
    mainLayout->addWidget(movieLineEdit,3,1);
    mainLayout->addWidget(movieTelCheckBox,3,2);
    mainLayout->addWidget(protelLabel,4,0);
    mainLayout->addWidget(proTelLineEdit,4,1);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}
