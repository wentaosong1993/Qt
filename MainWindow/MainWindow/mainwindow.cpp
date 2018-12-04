#include "mainwindow.h"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGroupBox *factory = createFactoryGroupBox();
    QGroupBox *cars = createCarGroupBox();
    QGroupBox *details = createDetailsGroupBox();

    //布局
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(factory,0,0);
    layout->addWidget(cars,1,0);
    layout->addWidget(details,0,1,2,1);
    layout->setColumnStretch(1,1);
    layout->setColumnMinimumWidth(0,500);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    createMenuBar();
    resize(850,400);
    setWindowTitle(QStringLiteral("主从视图"));

}

MainWindow::~MainWindow()
{

}

QGroupBox *MainWindow::createCarGroupBox()
{
    QGroupBox *box = new QGroupBox(QStringLiteral("汽车"));
    carView = new QTableView;
    carView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    carView->setSortingEnabled(true);
    carView->setSelectionBehavior(QAbstractItemView::SelectRows);
    carView->setSelectionMode(QAbstractItemView::SingleSelection);
    carView->setShowGrid(false);
    carView->verticalHeader()->hide();
    carView->setAlternatingRowColors(true);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(carView,0,0);
    box->setLayout(layout);
    return box;

}

QGroupBox *MainWindow::createFactoryGroupBox()
{
    factoryView = new QTableView;
    factoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    factoryView->setSortingEnabled(true);
    factoryView->setSelectionBehavior(QAbstractItemView::SelectRows);
    factoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    factoryView->setShowGrid(false);
    factoryView->setAlternatingRowColors(true);
    QGroupBox *box = new QGroupBox(QStringLiteral("汽车制造商"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(factoryView,0,0);
    box->setLayout(layout);
    return box;
}

QGroupBox *MainWindow::createDetailsGroupBox()
{
    QGroupBox *box = new QGroupBox(QStringLiteral("详细信息"));
    profileLabel = new QLabel;
    profileLabel->setWordWrap(true);
    profileLabel->setAlignment(Qt::AlignBottom);
    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignBottom);

    attribList = new QListWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(profileLabel,0,0,1,2);
    layout->addWidget(titleLabel,1,0,1,2);
    layout->addWidget(attribList,2,0,1,2);
    layout->setRowStretch(2,1);
    box->setLayout(layout);
    return box;
}

void MainWindow::createMenuBar()
{
    QAction *addAction = new QAction(QStringLiteral("添加"),this);
    QAction *deleteAction = new QAction(QStringLiteral("删除"),this);
    QAction *quitAction = new QAction(QStringLiteral("退出"),this);
    addAction->setShortcut(QStringLiteral("Ctrl+A"));
    deleteAction->setShortcut(QStringLiteral("Ctrl+D"));
    quitAction->setShortcut(QStringLiteral("Ctrl+Q"));

    QMenu *fileMenu = menuBar()->addMenu(QStringLiteral("操作菜单"));
    fileMenu->addAction(addAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addAction(quitAction);

}
