#ifndef COMMONFUNC_H
#define COMMONFUNC_H
#include <QImage>
#include <QPainter>
#include <QBitmap>


QImage GetRoundedRectImage(const QImage &src, int w, int h, qreal xRadius, qreal yRadius)
{
    if (src.isNull()) return QImage();

    QBitmap mask(w, h);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(mask.rect(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(mask.rect(), xRadius, yRadius);

    QPixmap image(QPixmap::fromImage(src.scaled(w, h)));
    image.setMask(mask);

    return image.toImage();
}
#endif // COMMONFUNC_H
