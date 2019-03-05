#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QWidget>
#include <QLabel>
#include <QPainter>


enum ArrowDirection
{
    AD_LEFT,
    AD_TOP,
    AD_RIGHT,
    AD_BOTTOM
};

class ToolTip : public QWidget
{
    Q_OBJECT

public:
    ToolTip(ArrowDirection ad, const QString & text, QWidget *parent = nullptr);
    ~ToolTip();

    void setArrow(ArrowDirection ad);
    void setFont(const QFont &font);
    void setText(const QString &text);
    void setMaxWidth(int w);
    void showTip(QPoint pos);

protected:
    void InitWindow();
    void UpdateSize();
    virtual void paintEvent(QPaintEvent *event) override;

private:
    ArrowDirection m_ArrowDirection;
    QFont m_Font;
    QString m_Text;
    int m_ArrowSize = 6;
    int m_HMargin = 6;
    int m_VMargan = 4;
    int m_MaxWidth = 300;
};

#endif // TOOLTIP_H
