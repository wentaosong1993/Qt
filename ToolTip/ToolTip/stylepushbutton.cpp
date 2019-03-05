#include "stylepushbutton.h"
#include "ui_stylepushbutton.h"
#include "tooltip.h"
#include "qiconpushbutton.h"

StylePushButton::StylePushButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StylePushButton)
{
    ui->setupUi(this);
    QString iconNor = ":/Image/help_nor.png";
    QString iconHov = ":/Image/help_hov.png";
    QString iconPre = ":/Image/help_pre.png";
    ui->pushButton->SetIcon(iconNor, iconHov, iconPre, 14);
    QString normalStyle = QString("QLabel{border: 0px;background-color:transparent;color: #209ffc;font:12px;}");
    QString hoverStyle = QString("QLabel{ background-color:transparent; color: #209ffc; text-decoration:underline; font:12px;}");
    QString pressStyle = QString("QLabel{ background-color:transparent; color: #1d9efc; text-decoration:underline; font:12px;}");
    ui->pushButton->SetText(QStringLiteral("帮助中心"), normalStyle, hoverStyle, pressStyle);
    ui->pushButton->SetToolTip(AD_BOTTOM, QStringLiteral("扩大空间发的卡刷卡缴费卡三等奖防控技术开发接口设计"), 200);
    ui->pushButton->setFixedSize(100,30);
}

StylePushButton::~StylePushButton()
{
    delete ui;
}
