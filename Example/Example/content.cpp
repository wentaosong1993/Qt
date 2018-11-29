#include "content.h"


Content::Content(QWidget *parent)
    :QFrame(parent)
{
	// 上面（左+右）
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    baseInfo = new BaseInfo();
    contact = new Contact();
    detail = new Detail();
    stack->addWidget(baseInfo);
    stack->addWidget(contact);
    stack->addWidget(detail);


	//最小边
    amendBtn = new QPushButton(QStringLiteral("修改"));
    closeBtn = new QPushButton(QStringLiteral("关闭"));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(amendBtn);
    btnLayout->addWidget(closeBtn);

    QVBoxLayout *rightLayout = new QVBoxLayout(this);
    rightLayout->setMargin(10);
    rightLayout->setSpacing(6);
    rightLayout->addWidget(stack);
    rightLayout->addLayout(btnLayout);
}

Content::~Content()
{

}
