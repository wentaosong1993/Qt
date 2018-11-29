#include "extensiondlg.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHBoxLayout>

ExtensionDlg::ExtensionDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QStringLiteral("Extension Dialog"));
    createBaseInfo();
    createDetailInfo();
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(10);
}

ExtensionDlg::~ExtensionDlg()
{

}

void ExtensionDlg::createBaseInfo()
{
    baseWidget = new QWidget;
    QLabel *nameLabel = new QLabel(QStringLiteral("姓名:"));
    QLineEdit *nameLineEdit = new QLineEdit;
    QLabel *sexLabel = new QLabel(QStringLiteral("性别"));
    QComboBox *sexComboBox = new QComboBox;
    sexComboBox->insertItem(0,QStringLiteral("女"));
    sexComboBox->insertItem(1,QStringLiteral("男"));

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(nameLabel,0,0);
    leftLayout->addWidget(nameLineEdit,0,1);
    leftLayout->addWidget(sexLabel);
    leftLayout->addWidget(sexComboBox);
    QPushButton *okBtn = new QPushButton(QStringLiteral("确定"));
    QPushButton *detailBtn = new QPushButton(QStringLiteral("详细"));
    QDialogButtonBox *btnBox = new QDialogButtonBox(Qt::Vertical);
    btnBox->addButton(okBtn,QDialogButtonBox::ActionRole);
    btnBox->addButton(detailBtn,QDialogButtonBox::ActionRole);
    QHBoxLayout *mainLayout = new QHBoxLayout(baseWidget);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(btnBox);
    connect(detailBtn,SIGNAL(clicked()),this,SLOT(showDetailInfo()));
}

void ExtensionDlg::createDetailInfo()
{
    detailWidget = new QWidget;
    QLabel *ageLabel = new QLabel(QStringLiteral("年龄:"));
    QLineEdit *ageLineEdit = new QLineEdit;
    ageLineEdit->setText(QStringLiteral("30"));
    QLabel *departmentLabel = new QLabel(QStringLiteral("部门"));
    QComboBox *departmentComboBox = new QComboBox;
    departmentComboBox->addItem(QStringLiteral("部门1"));
    departmentComboBox->addItem(QStringLiteral("部门2"));
    departmentComboBox->addItem(QStringLiteral("部门3"));
    departmentComboBox->addItem(QStringLiteral("部门4"));

    QLabel *emailLabel = new QLabel(QStringLiteral("email:"));
    QLineEdit *emailLineEdit = new QLineEdit;
    QGridLayout *mainLayout = new  QGridLayout(detailWidget);
    mainLayout->addWidget(ageLabel,0,0);
    mainLayout->addWidget(ageLineEdit,0,1);
    mainLayout->addWidget(departmentLabel,1,0);
    mainLayout->addWidget(departmentComboBox,1,1);
    mainLayout->addWidget(emailLabel,2,0);
    mainLayout->addWidget(emailLineEdit,2,1);
    detailWidget->hide();
}

void ExtensionDlg::showDetailInfo()
{
    if(detailWidget->isHidden())
    {
        detailWidget->show();
    }
    else
    {
        detailWidget->hide();
    }
}
