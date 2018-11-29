#include "progressdlg.h"
#include <QProgressDialog>

ProgressDlg::ProgressDlg(QWidget *parent)
    : QDialog(parent)
{
    QFont font("ZYSong18030",12);
    setFont(font);
    setWindowTitle(QStringLiteral("Progress"));
    fileNum = new QLabel;
    fileNum->setText(QStringLiteral("文件数目:"));
    fileNumLineEdit = new QLineEdit;
    fileNumLineEdit->setText(QStringLiteral("100000"));
    progressType = new QLabel;
    progressType->setText(QStringLiteral("显示类型:"));
    comboBox = new QComboBox;
    comboBox->addItem(QStringLiteral("progressBar"));
    comboBox->addItem(QStringLiteral("progressDialog"));
    progressBar = new QProgressBar;
    startBtn = new QPushButton();
    startBtn->setText(QStringLiteral("开始"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileNum,0,0);
    mainLayout->addWidget(fileNumLineEdit,0,1);
    mainLayout->addWidget(progressType,1,0);
    mainLayout->addWidget(comboBox,1,1);
    mainLayout->addWidget(progressBar,2,0,1,2);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(startBtn);
    horizontalLayout->addStretch();
    mainLayout->addLayout(horizontalLayout,3,2,1,1);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);

    connect(startBtn,SIGNAL(clicked()),this,SLOT(startProgress()));
}

ProgressDlg::~ProgressDlg()
{

}

void ProgressDlg::startProgress()
{
    bool ok;
    int num = fileNumLineEdit->text().toInt(&ok);
    if(comboBox->currentIndex() == 0)
    {
        progressBar->setRange(0,num);
        for(int i = 1; i < num + 1; i++)
        {
            progressBar->setValue(i);
        }
    }
    else if(comboBox->currentIndex() == 1)
    {
        QProgressDialog *progressDialog = new QProgressDialog(this);
        QFont font("ZYSong18030",12);
        progressDialog->setFont(font);
        progressDialog->setWindowModality(Qt::WindowModal);
        progressDialog->setMinimumDuration(5);
        progressDialog->setWindowTitle(QStringLiteral("Please Wait"));
        progressDialog->setLabelText(QStringLiteral("Copying"));
        progressDialog->setCancelButtonText(QStringLiteral("Cancel"));
        progressDialog->setRange(0,num);

        for(int i = 1; i < num + 1; i++)
        {
            progressDialog->setValue(i);
            if(progressDialog->wasCanceled())
                return ;
        }
    }
}
