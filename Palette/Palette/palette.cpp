#include "palette.h"
#include <QHBoxLayout>
#include <QGridLayout>


Palette::Palette(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

Palette::~Palette()
{

}

void Palette::createCtrlFrame()
{
    ctrlFrame = new QFrame;
    windowLabel = new QLabel(QStringLiteral("QPalette::Window:"));
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox);
    connect(windowComboBox,SIGNAL(activated(int)),this,SLOT(showWindow()));

    windowTextLabel = new QLabel(QStringLiteral("QPalette::WindowText:"));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox,SIGNAL(activated(int)),this,SLOT(showWindowText()));
    buttonLabel = new QLabel(QStringLiteral("QPalette::Button"));
    buttonComboBox = new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox,SIGNAL(activated(int)),this,SLOT(showButton()));
    buttonTextLabel = new QLabel(QStringLiteral("QPalette::ButtonText:"));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox,SIGNAL(activated(int)),this,SLOT(showButtonText()));
    baseLabel = new QLabel(QStringLiteral("QPalette::Base"));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox,SIGNAL(activated(int)),this,SLOT(showBase()));
    QGridLayout *mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel,0,0);
    mainLayout->addWidget(windowComboBox,0,1);
    mainLayout->addWidget(windowTextLabel,1,0);
    mainLayout->addWidget(windowTextComboBox,1,1);
    mainLayout->addWidget(buttonLabel,2,0);
    mainLayout->addWidget(buttonComboBox,2,1);
    mainLayout->addWidget(buttonTextLabel,3,0);
    mainLayout->addWidget(buttonTextComboBox,3,1);
    mainLayout->addWidget(baseLabel,4,0);
    mainLayout->addWidget(baseComboBox,4,1);
}

void Palette::createContentFrame()
{
    contentFrame = new QFrame;
    label1 = new QLabel(QStringLiteral("请选择一个值:"));
    comboBox1 = new QComboBox;
    label2 = new QLabel(QStringLiteral("请输入字符串"));
    lineEdit2 = new QLineEdit;
    textEdit = new QTextEdit;
    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(label1,0,0);
    topLayout->addWidget(comboBox1,0,1);
    topLayout->addWidget(label2,1,0);
    topLayout->addWidget(lineEdit2,1,1);
    topLayout->addWidget(textEdit,2,0,1,2);
    okBtn = new QPushButton(QStringLiteral("确认"));
    cancelBtn = new QPushButton(QStringLiteral("取消"));
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(okBtn);
    bottomLayout->addWidget(cancelBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout(contentFrame);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

}

void Palette::fillColorList(QComboBox * comboBox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach (color, colorList) {
        QPixmap pix(QSize(70,20));
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix),NULL);
        comboBox->setIconSize(QSize(70,20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

void Palette::showWindow()
{
    //获取当前选择的颜色值
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Window,color);
    //把修改后的调色板信息应用到conetentFrame窗体中，更新显示
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showWindowText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText,color);
    contentFrame->setPalette(p);
}

void Palette::showButton()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[buttonComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button,color);
    contentFrame->setPalette(p);
}

void Palette::showButtonText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[buttonTextComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText,color);
    contentFrame->setPalette(p);
}

void Palette::showBase()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[baseComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base,color);
    contentFrame->setPalette(p);
}
