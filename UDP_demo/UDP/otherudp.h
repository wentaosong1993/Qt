#ifndef OTHERUDP_H
#define OTHERUDP_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class OtherUdp;
}

class OtherUdp : public QWidget
{
    Q_OBJECT

public:
    explicit OtherUdp(QWidget *parent = 0);
    ~OtherUdp();

    void dealMsg();

private slots:
    void on_otherSendBtn_clicked();

    void on_otherCloseBtn_clicked();

private:
    Ui::OtherUdp *ui;
    QUdpSocket *otherUdpSocket;
};

#endif // OTHERUDP_H
