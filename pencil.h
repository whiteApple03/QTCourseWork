#ifndef PENCIL_H
#define PENCIL_H
#include "toolforfieldinteractive.h"
class Pencil : public ToolForFieldInteractive
{
public:
    Pencil();
    void draw() const override;
};

#endif // PENCIL_H
