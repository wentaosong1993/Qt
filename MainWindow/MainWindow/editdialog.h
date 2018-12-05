#ifndef EDITDIALOG_H
#define EDITDIALOG_H
#include <QDialog>
#include <QtSql>
#include <Qtxml>
#include "ui_connectdlg.h"
#include <QtWidgets/QDialogButtonBox>

class EditDialog : public QDialog
{
public:
    EditDialog(QSqlRelationalTableModel *cars,QSqlTableModel *factory,QDomDocument details,QFile *output,QWidget *parent = 0);

private slots:
    void revert();
    void submit();

private:
    int addNewCar(const QString &name, int factoryId);
    int addNewFactory(const QString &factory,const QString &address);
    void addAttribs(int carId,QStringList attribs);
    QDialogButtonBox *createButtons();
    QGroupBox *createInputWidgets();
    int findFactoryId(const QString &factory);
    int generateCarId();
    int generateFactoryId();

    QSqlRelationalTableModel *carModel;
    QSqlTableModel *factoryModel;
    QDomDocument carDetails;
    QFile *outputFile;
    QLineEdit *factoryEditor;
    QLineEdit *addressEditor;
    QLineEdit *carEditor;
    QSpinBox *yearEditor;
    QLineEdit *attribEditor;
};

#endif // EDITDIALOG_H
