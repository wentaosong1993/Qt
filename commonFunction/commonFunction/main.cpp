#include <QCoreApplication>
#include <QDebug>
#include <QFontMetrics>
#include <QFont>
#include <QDir>

QString GetBreakText(const QString & str, int lineLength)
{
    QString resultStr;
    int length = str.length();  // 计算字符串总长度
    if (length > lineLength)
    {
        resultStr.append(str.left(lineLength));
        length -= lineLength;
        while (length >= lineLength)  // 当字符串长度大于单行最大长度时进行换行
        {
            resultStr.append("\n" + str.right(length).left(lineLength));
            length -= lineLength;
        }
        if (length > 0)
        {
            resultStr.append("\n" + str.right(length));
        }
    }
    else
    {
        resultStr = str;
    }
    return resultStr;   // 返回处理后的字符串
}


QString GetElidedText(const QString &str, QFont font, int MaxWidth)
{
    QString resultStr = str;
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);  // 计算字符串宽度
    if (width >= MaxWidth)  // 当字符串宽度大于最大宽度时进行转换
    {
        resultStr = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);  // 右部显示省略号
    }
    return resultStr;   // 返回处理后的字符串
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    QString str = "kdkdkdkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
//    QString breakText = GetBreakText(str,15);
//    qDebug() << breakText;

//    QDir dir;
//    qDebug() << dir.mkdir(QString("../test"));
    auto i = 2^10;
    qDebug() << i;

    return a.exec();
}


