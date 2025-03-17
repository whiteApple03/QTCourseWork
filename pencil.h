#ifndef PENCIL_H
#define PENCIL_H
#include "toolforfieldinteractive.h"
#include <QList>
#include <QGraphicsScene>
class Pencil : public ToolForFieldInteractive
{
public:
    Pencil();
    void draw(QList<QGraphicsItem *> items,  const ToolConfiguration* config) const override;
};

#endif // PENCIL_H
