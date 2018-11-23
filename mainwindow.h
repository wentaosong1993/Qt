#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QLineEdit>
#include <QDialog>

namespace Ui {
class MainWindow;
}

//class QLineEdit;
//class QDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void newFile();   // 新建操作
    bool maybeSave(); // 判断是否需要保存
    bool save();      // 保存操作
    bool saveAs();    // 另存为操作
    bool saveFile(const QString &fileName); // 保存文件

    bool loadFile(const QString &fileName); // 加载文件
    ~MainWindow();

private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();


    void on_action_Quit_triggered();

    void on_action_Copy_triggered();

    void on_action_X_triggered();

    void on_action_Paste_triggered();

    void on_action_Z_triggered();

    void on_action_Open_triggered();

    void on_action_Close_triggered();

    void showFindText();

    void on_action_Find_triggered();

protected:
    void closeEvent(QCloseEvent *event);//

private:
    Ui::MainWindow *ui;
    // 为真表示文件没有保存过，为假表示文件已经被保存过了
    bool isUntitled;
    // 保存当前文件的路径
    QString curFile;
    QLineEdit *findLineEdit;
    QDialog *findDlg;

};

#endif // MAINWINDOW_H
