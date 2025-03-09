#ifndef PIXELITEM_H
#define PIXELITEM_H
#include <QGraphicsRectItem>

class PixelItem : public QGraphicsRectItem {
public:
    PixelItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void setColor(const QColor &color);
    void setColor(const QColor &color, int alpha);
    QColor color() const;




private:
    QColor m_color;
};

#endif // PIXELITEM_H
