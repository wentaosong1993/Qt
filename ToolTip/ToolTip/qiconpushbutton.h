#ifndef QICONPUSHBUTTON_H
#define QICONPUSHBUTTON_H

#include <QPushButton>
#include "tooltip.h"

class QIconPushButton : public QPushButton
{
    Q_OBJECT
public:
    QIconPushButton(QWidget *parent = nullptr);
    QIconPushButton(bool bIsIconLeft = true, QWidget *parent = nullptr);
    ~QIconPushButton();

    void SetIcon(const QString &iconNormal, const QString &iconHover, const QString &iconPressed, int iconsize);
    void SetText(const QString &text, const QString &styleNormal, const QString &styleHover, const QString &stylePressed);
    void setText(const QString &text);

    void SetToolTip(ArrowDirection ad, const QString& tip, int maxW = 300);

protected:
    void InitWidget(bool bIsIconLeft = true);
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

signals:
    void sgMouseEnter(QPoint pos, const QString& tooltip);
	void sgMouseLeave();

private:
    QLabel *m_pLabelIcon = nullptr;
    QLabel *m_pLabelText = nullptr;

    QString m_IconNormal;
    QString m_IconHover;
    QString m_IconPressed;
    int m_IconSize = 20;

    QString m_TextStyleNormal;
    QString m_TextStyleHover;
    QString m_TextStylePressed;

    ToolTip *m_pToolTip = nullptr;
    ArrowDirection m_TipDirection;
};

#endif // QICONPUSHBUTTON_H
