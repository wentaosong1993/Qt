#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("UserInfo"));
    //左侧
    userNameLabel = new QLabel(QStringLiteral("用户名:"));
    userNameLineEdit = new QLineEdit;
    nameLabel = new QLabel(QStringLiteral("姓名:"));
    nameLineEdit = new QLineEdit;
    sexLabel = new QLabel(QStringLiteral("性别"));
    sexCombobox = new QComboBox;
    sexCombobox->addItem(QStringLiteral("女"));
    sexCombobox->addItem(QStringLiteral("男"));
    departmentLabel = new QLabel(QStringLiteral("部门:"));
    departmentTextEdit = new QTextEdit;
    ageLabel = new QLabel(QStringLiteral("年龄:"));
    ageLineEdit = new QLineEdit;
    otherLabel = new QLabel(QStringLiteral("备注:"));
    otherLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    leftLayout = new QGridLayout();

    //向布局中加入需要布局的控件
    leftLayout->addWidget(userNameLabel, 0, 0);
    leftLayout->addWidget(userNameLineEdit, 0, 1);
    leftLayout->addWidget(nameLabel, 1, 0);
    leftLayout->addWidget(nameLineEdit, 1, 1);
    leftLayout->addWidget(sexLabel, 2, 0);
    leftLayout->addWidget(sexCombobox, 2, 1);
    leftLayout->addWidget(departmentLabel, 3, 0);
    leftLayout->addWidget(departmentTextEdit, 3, 1);
    leftLayout->addWidget(ageLabel, 4, 0);
    leftLayout->addWidget(ageLineEdit, 4, 1);
    leftLayout->addWidget(otherLabel, 5, 0, 1, 2);
    leftLayout->setColumnStretch(0,1);
    leftLayout->setColumnStretch(1,3);

    //右侧
    headLabel = new QLabel(QStringLiteral("头像:"));
    headIconLabel = new QLabel;
    QPixmap icon(":/add-press.png");
    headIconLabel->setPixmap(icon);
    headIconLabel->resize(icon.width(), icon.height());
    updateHeadBtn = new QPushButton(QStringLiteral("更新"));

    //完成右上侧头像选择区的布局
    topRightLayout = new QHBoxLayout();
    topRightLayout->setSpacing(20);
    topRightLayout->addWidget(headLabel);
    topRightLayout->addWidget(headIconLabel);
    topRightLayout->addWidget(updateHeadBtn);
    introductionLabel = new QLabel(QStringLiteral("个人说明"));
    introductionTextEdit = new QTextEdit;

    //完成右侧的布局
    rightLayout = new QVBoxLayout();
    rightLayout->setMargin(10);
    rightLayout->addLayout(topRightLayout);
    rightLayout->addWidget(introductionLabel);
    rightLayout->addWidget(introductionTextEdit);

    //底部
    okBtn = new QPushButton(QStringLiteral("确定"));
    cancelBtn = new QPushButton(QStringLiteral("取消"));

    //完成下方的按钮布局
    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);

    //
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    mainLayout->addLayout(buttonLayout, 1, 0, 1, 2);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(okButtonClick()));

}

Dialog::~Dialog()
{

}
