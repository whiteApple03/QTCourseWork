#ifndef TOOLCONFIGURATION_H
#define TOOLCONFIGURATION_H

#include<QColor>

class ToolConfiguration
{
public:
    ToolConfiguration();
    int fieldSizeX;
    int fieldSizeY;
    int pixelSize;
    int selectedRectSize;
    QColor* currentColor;

};

#endif // TOOLCONFIGURATION_H
