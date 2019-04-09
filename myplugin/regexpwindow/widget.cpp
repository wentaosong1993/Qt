#include "widget.h"
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    ui->setupUi(this);
    if(!loadPlugin())
    {
        QMessageBox::information(this,"Error","Could not load the plugin");
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
}

Widget::~Widget()
{

}

bool Widget::loadPlugin()
{
    QDir pluginDir("D:/GitHubRepository/Qt/myplugin/plugins");
    //遍历插件目录
    foreach(QString fileName, pluginDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginDir.absoluteFilePath(fileName));
        QObject  *plugin = pluginLoader.instance();
        if(plugin)
        {
            regExpInterface = qobject_cast<RegExpInterface *>(plugin);
            if(regExpInterface)
            {
                return true;
            }
        }
    }
    return false;
}

void Widget::on_pushButton_clicked()
{
    QString str = regExpInterface->regexp(ui->lineEdit->text());
    ui->label_3->setText(str);
}
