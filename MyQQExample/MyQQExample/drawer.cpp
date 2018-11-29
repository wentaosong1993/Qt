#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>


Drawer::Drawer(QWidget *parent, Qt::WindowFlags f)
    :QToolBox(parent,f)
{
    setWindowTitle(QStringLiteral("My QQ"));
    toolBtn1_1 = new QToolButton;
    toolBtn1_1->setText(QStringLiteral("张三"));
    toolBtn1_1->setIcon(QPixmap(":/add-hover.png"));
    toolBtn1_1->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn1_1->setAutoRaise(true);
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_2 = new QToolButton;
    toolBtn1_2->setText(QStringLiteral("李四"));
    toolBtn1_2->setIcon(QPixmap(":/add-hover.png"));
    toolBtn1_2->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_3 = new QToolButton;
    toolBtn1_3->setText(QStringLiteral("王二"));
    toolBtn1_3->setIcon(QPixmap(":/add-hover.png"));
    toolBtn1_3->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_4 = new QToolButton;
    toolBtn1_4->setText(QStringLiteral("李四"));
    toolBtn1_4->setIcon(QPixmap(":/add-hover.png"));
    toolBtn1_4->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_5 = new QToolButton;
    toolBtn1_5->setText(QStringLiteral("小二"));
    toolBtn1_5->setIcon(QPixmap(":/add-hover.png"));
    toolBtn1_5->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox1 = new QGroupBox;
    QVBoxLayout *layout1 = new QVBoxLayout(groupBox1);
    layout1->setMargin(10);
    layout1->setAlignment(Qt::AlignHCenter);

    //加入抽屉各个按钮
    layout1->addWidget(toolBtn1_1);
    layout1->addWidget(toolBtn1_2);
    layout1->addWidget(toolBtn1_3);
    layout1->addWidget(toolBtn1_4);
    layout1->addWidget(toolBtn1_5);

    //插入一个占位符
    layout1->addStretch();

    toolBtn2_1 = new QToolButton;
    toolBtn2_1->setText(QStringLiteral("小张"));
    toolBtn2_1->setIcon(QPixmap(":/add-hover.png"));
    toolBtn2_1->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2_2 = new QToolButton;
    toolBtn2_2->setText(QStringLiteral("老张"));
    toolBtn2_2->setIcon(QPixmap(":/add-hover.png"));
    toolBtn2_2->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox2 = new QGroupBox;
    QVBoxLayout *layout2 = new QVBoxLayout(groupBox2);
    layout2->setMargin(10);
    layout2->setAlignment(Qt::AlignHCenter);
    //加入抽屉各个按钮
    layout2->addWidget(toolBtn2_1);
    layout2->addWidget(toolBtn2_2);


    toolBtn3_1 = new QToolButton;
    toolBtn3_1->setText(QStringLiteral("小张"));
    toolBtn3_1->setIcon(QPixmap(":/add-hover.png"));
    toolBtn3_1->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3_2 = new QToolButton;
    toolBtn3_2->setText(QStringLiteral("老张"));
    toolBtn3_2->setIcon(QPixmap(":/add-hover.png"));
    toolBtn3_2->setIconSize(QPixmap(":/add-hover.png").size());
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox3 = new QGroupBox;
    QVBoxLayout *layout3 = new QVBoxLayout(groupBox3);
    layout3->setMargin(10);
    layout3->setAlignment(Qt::AlignHCenter);
    //加入抽屉各个按钮
    layout3->addWidget(toolBtn3_1);
    layout3->addWidget(toolBtn3_2);

    this->addItem((QWidget*)groupBox1,QStringLiteral("我的好友"));
    this->addItem((QWidget*)groupBox2,QStringLiteral("陌生人"));
    this->addItem((QWidget*)groupBox3,QStringLiteral("黑名单"));
}
