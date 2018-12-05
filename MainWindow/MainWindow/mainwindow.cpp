#include "mainwindow.h"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSqlRecord>

//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//{
//    QGroupBox *factory = createFactoryGroupBox();
//    QGroupBox *cars = createCarGroupBox();
//    QGroupBox *details = createDetailsGroupBox();

//    //布局
//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(factory,0,0);
//    layout->addWidget(cars,1,0);
//    layout->addWidget(details,0,1,2,1);
//    layout->setColumnStretch(1,1);
//    layout->setColumnMinimumWidth(0,500);
//    QWidget *widget = new QWidget;
//    widget->setLayout(layout);
//    setCentralWidget(widget);
//    createMenuBar();
//    resize(850,400);
//    setWindowTitle(QStringLiteral("主从视图"));

//}

MainWindow::MainWindow(const QString &factoryTable, const QString &carTable, QFile *carDetails, QWidget *parent)
	:QMainWindow(parent)
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

    file = carDetails;
    readCarData();
    carModel = new QSqlRelationalTableModel(this);
    carModel->setTable(carTable);
    carModel->setRelation(2,QSqlRelation(factoryTable,"id","manufactory"));
    carModel->select();
    factoryModel = new QSqlTableModel(this);
    factoryModel->setTable(factoryTable);
    factoryModel->select();
    //...
}

void MainWindow::addCar()
{

}

void MainWindow::changeFactory(QModelIndex index)
{
    QSqlRecord record = factoryModel->record(index.row());
    QString factoryId = record.value("id").toString();
    carModel->setFilter("id= '" + factoryId + "'");
    showFactoryProfile(index);
}

void MainWindow::delCar()
{
    QModelIndexList selection = carView->selectionModel()->selectedRows(0);
    if(!selection.empty())
    {
        QModelIndex idIndex = selection.at(0);
        int id = idIndex.data().toInt();
        QString name = idIndex.sibling(idIndex.row(),1).data().toString();
        QString factory = idIndex.sibling(idIndex.row(),2).data().toString();
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this,QStringLiteral("删除汽车记录"),QStringLiteral("确认删除由 '%1' 生产的 ‘%2’吗？").arg(factory).arg(name),QMessageBox::Yes | QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            removeCarFromFile(id);
            removeCarFromDatabase(idIndex);
            decreaseCarCount(indexOfFactory(factory));
        }
        else
        {
            QMessageBox::information(this,QStringLiteral("删除汽车记录"),QStringLiteral("请选择要删除的记录"));
        }
    }
}

void MainWindow::showCarDetails(QModelIndex index)
{
    QSqlRecord record = carModel->record(index.row());
    QString factory = record.value("manufactory").toString();

    QString name = record.value("name").toString();
    QString year = record.value("year").toString();
    QString carId = record.value("carId").toString();
    showFactoryProfile(indexOfFactory(factory));
    titleLabel->setText(QStringLiteral("品牌：%1 (%2)").arg(name).arg(year));

    titleLabel->show();
    QDomNodeList cars = carData.elementsByTagName("car");
    for(int i = 0; i < cars.count(); i++)
    {
        QDomNode car = cars.item(i);
        if(car.toElement().attribute("id") == carId)
        {
            getAttribList(car.toElement());
            break;
        }
    }
    if(!attribList->count() == 0)
    {
        attribList->show();
    }
}

void MainWindow::showFactoryProfile(QModelIndex index)
{
    QSqlRecord record = factoryModel->record(index.row());
    QString name = record.value("manufactory").toString();
    int count = carModel->rowCount();
    profileLabel->setText(QStringLiteral("汽车制造商: %1\n 产品数量： %2").arg(name).arg(count));
    profileLabel->show();
    titleLabel->hide();
    attribList->hide();
}


MainWindow::~MainWindow()
{

}

QGroupBox *MainWindow::createCarGroupBox()
{
    carView = new QTableView;
    carView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    carView->setSortingEnabled(true);
    carView->setSelectionBehavior(QAbstractItemView::SelectRows);
    carView->setSelectionMode(QAbstractItemView::SingleSelection);
    carView->setShowGrid(false);
    carView->verticalHeader()->hide();
    carView->setAlternatingRowColors(true);

    QVBoxLayout *layout = new QVBoxLayout;

    //carView->setModel(carModel);//mainwindow.cpp构造函数中功能待完善！！（目前这里会报错）
    connect(carView,SIGNAL(clicked(QModelIndex)),this,SLOT(showCarDetails(QModelIndex)));
    connect(carView,SIGNAL(activated(QModelIndex)),this,SLOT(showCarDetails(QModelIndex)));
    layout->addWidget(carView,0,0);
    QGroupBox *box = new QGroupBox(QStringLiteral("汽车"));
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

    factoryView->setModel(factoryModel);
    connect(factoryView,SIGNAL(clicked(QModelIndex)),this,SLOT(changeFactory(QModelIndex)));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(factoryView,0,0);
    QGroupBox *box = new QGroupBox(QStringLiteral("汽车制造商"));
    box->setLayout(layout);
    return box;
}

QGroupBox *MainWindow::createDetailsGroupBox()
{
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
    QGroupBox *box = new QGroupBox(QStringLiteral("详细信息"));
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

    connect(addAction,SIGNAL(triggered(bool)),this,SLOT(addCar));
    connect(deleteAction,SIGNAL(triggered(bool)),this,SLOT(delCar()));
    connect(quitAction,SIGNAL(triggered(bool)),this,SLOT(close()));

}

void MainWindow::decreaseCarCount(QModelIndex index)
{
    int row = index.row();
    int count = carModel->rowCount();
    if(count == 0)
    {
        factoryModel->removeRow(row);
    }
}

void MainWindow::getAttribList(QDomNode car)
{
    attribList->clear();
    QDomNodeList attrib = car.childNodes();
    QDomNode node;
    QString attribNumber;
    for(int j =0 ; j <attrib.count(); j++)
    {
        node = attrib.item(j);
        attribNumber = node.toElement().attribute("number");
        QListWidgetItem *item = new QListWidgetItem(attribList);
        QString showText(attribNumber + ":" + node.toElement().text());
        item->setText(QStringLiteral("%1").arg(showText));
    }
}

QModelIndex MainWindow::indexOfFactory(const QString &factory)
{
    for(int i = 0; i < factoryModel->rowCount(); i++)
    {
        QSqlRecord record = factoryModel->record(i);
        if(record.value("manufactory") == factory)
        {
            return factoryModel->index(i,1);
        }
    }
    return QModelIndex();
}

void MainWindow::readCarData()
{
    if(!file->open(QIODevice::ReadOnly))
    {
        return;
    }
    if(!carData.setContent(file))
    {
        file->close();
        return;
    }
    file->close();
}

void MainWindow::removeCarFromDatabase(QModelIndex index)
{
    carModel->removeRow(index.row());
}

void MainWindow::removeCarFromFile(int id)
{
    QDomNodeList cars = carData.elementsByTagName(QStringLiteral("car"));
    for(int i = 0; i < cars.count();i++)
    {
        QDomNode node = cars.item(i);
        if(node.toElement().attribute("id").toInt() == id)
        {
            carData.elementsByTagName(QStringLiteral("archive")).item(0).removeChild(node);
            break;
        }
    }
}
