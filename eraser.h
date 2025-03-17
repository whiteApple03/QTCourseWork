#ifndef ERASER_H
#define ERASER_H

#include "toolforfieldinteractive.h"

class Eraser : public ToolForFieldInteractive
{
public:
    Eraser();
    void draw(QList<QGraphicsItem *> items,  const ToolConfiguration* config) const override;

};

#endif // ERASER_H
