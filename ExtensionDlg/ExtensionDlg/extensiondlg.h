#ifndef EXTENSIONDLG_H
#define EXTENSIONDLG_H

#include <QDialog>

class ExtensionDlg : public QDialog
{
    Q_OBJECT

public:
    ExtensionDlg(QWidget *parent = 0);
    ~ExtensionDlg();
private slots:
    void showDetailInfo();
private:
    void createBaseInfo();
    void createDetailInfo();
    QWidget *baseWidget;
    QWidget *detailWidget;

};

#endif // EXTENSIONDLG_H
