#include "toolconfiguration.h"

ToolConfiguration::ToolConfiguration() {
    fieldSizeX = 32;
    fieldSizeY = 32;
    selectedRectSize = 2;
    pixelSize = 1;
    currentColor = new QColor(Qt::black);
}
