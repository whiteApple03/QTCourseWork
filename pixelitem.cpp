#include "pixelitem.h"
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QBrush>


PixelItem::PixelItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent), m_color(Qt::white) {
    setBrush(m_color);
    setPen(Qt::NoPen);
}

void PixelItem::setColor(const QColor &color) {
    m_color = color;
    setBrush(color);
}
void PixelItem::setColor(const QColor &color, int alpha) {
    m_color = color;
    QBrush brush(QColor(color.red(), color.green(), color.blue(), alpha));
    setBrush(brush);
}

QColor PixelItem::color() const {
    return m_color;
}
