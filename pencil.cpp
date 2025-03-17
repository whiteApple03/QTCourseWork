#include "pencil.h"
#include <QDebug>
#include <pixelitem.h>
Pencil::Pencil()   {}

void Pencil::draw(QList<QGraphicsItem *> items,  const ToolConfiguration* config) const {
    for(auto item : items) {

        if (PixelItem* rectItem = dynamic_cast<PixelItem*>(item)) {
            rectItem->setColor(config->currentColor);
        }

    }
}
