#ifndef TOOLFORFIELDINTERACTIVE_H
#define TOOLFORFIELDINTERACTIVE_H
#include <QList>
#include <QGraphicsScene>
#include "toolconfiguration.h"

class ToolForFieldInteractive
{
public:
    ToolForFieldInteractive();
    virtual void  draw(QList<QGraphicsItem *>items, const ToolConfiguration* config) const = 0;
};

#endif // TOOLFORFIELDINTERACTIVE_H
