#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QVBoxLayout>
#include <QLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化文件为未保存状态
    isUntitled = true;
    // 初始化文件名为"未命名.txt"
    curFile = QString::fromUtf8("untitled.txt");
    // 初始化窗口标题为文件名
    setWindowTitle(curFile); //

    findDlg = new QDialog(this);
    findDlg->setWindowTitle(QStringLiteral("Find"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn= new QPushButton(QStringLiteral("Find Next"), findDlg);
    QVBoxLayout *layout= new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked, this, &MainWindow::showFindText);
}

void MainWindow::newFile()
{
    if(maybeSave()) //判断是否保存
    {
        isUntitled = true;
        curFile = QStringLiteral("untitled.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave()
{
    if(ui->textEdit->document()->isModified())
    {
        int ret = QMessageBox::warning(this,tr("Warning"),curFile + tr("尚未保存，是否保存？"),
                             QMessageBox::Yes | QMessageBox::Cancel);
        if(ret == QMessageBox::Yes)
        {
            return save();
        }
        else
        {
            return false;
        }
    }
    //如果文档没有被更改,则直接返回true
    return true;
}

bool MainWindow::save()
{
    if(isUntitled) //没有保存过
    {
        return saveAs();
    }
    else //已经保存过
    {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("saveAs"),curFile);
    if(fileName.isEmpty()) return false;

       return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,QStringLiteral("多文档编辑器"),QStringLiteral("无法写入文件 %1： \n %2 ").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    //指针变为原来的样子
    QApplication::restoreOverrideCursor();
    isUntitled = false;
    //获得文件标准路径
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,QStringLiteral("多文档编辑器"),QStringLiteral("无法写入文件 %1： \n %2 ").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    //设置当前文件
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    newFile();
}

void MainWindow::on_action_Save_triggered()
{
    save();
}

void MainWindow::on_action_SaveAs_triggered()
{
    saveAs();
}


void MainWindow::on_action_Quit_triggered()
{
    on_action_Close_triggered();
    qApp->quit();
}

void MainWindow::on_action_Copy_triggered() //
{
    ui->textEdit->copy();
}

void MainWindow::on_action_X_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_Paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_action_Z_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_Open_triggered()
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
        {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_action_Close_triggered()
{
    if(maybeSave())
    {
        ui->textEdit->setVisible(false);
    }
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if (!ui->textEdit->find(str, QTextDocument::FindBackward))
    {
       QMessageBox::warning(this, tr("查找"),
                tr("找不到%1").arg(str));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::on_action_Find_triggered()
{
    findDlg->show();
}
