#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();

    QButtonGroup *pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(ui->productImport,0);
    pButtonGroup->addButton(ui->publishManage,1);
    pButtonGroup->addButton(ui->modelSetting,2);

    connect(pButtonGroup,SIGNAL(buttonClicked(int)),ui->tabWidget,SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


