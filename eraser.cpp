#include "eraser.h"
#include "pixelitem.h"
Eraser::Eraser() {}

void Eraser::draw(QList<QGraphicsItem *> items,  const ToolConfiguration* config) const {
    for(auto item : items) {

        if (PixelItem* rectItem = dynamic_cast<PixelItem*>(item)) {
            int x = rectItem->rect().x() / config->pixelSize;
            int y = rectItem->rect().y() / config->pixelSize;
            if (y % 2 == 0 && x % 2 == 0) {
                rectItem->setColor(Qt::gray, 128);

            } else if (y % 2 != 0 && x % 2 != 0) {
                rectItem->setColor(Qt::gray, 128);
            } else {
                rectItem->setColor(Qt::white);
            }
        }

    }
}
