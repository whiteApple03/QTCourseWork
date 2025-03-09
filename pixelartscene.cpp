#include "pixelartscene.h"

PixelArtScene::PixelArtScene(QObject *parent) : PixelArtScene(32, 32, parent) {}

PixelArtScene::PixelArtScene(int width, int height, QObject *parent)
    : QGraphicsScene(parent)
    // m_pixelSize(10),
    // m_color(Qt::black),
    // m_image(width, height, QImage::Format_ARGB32)

{
    // m_image.fill(Qt::white);
    pixelSize = 10;
    setSceneRect(0, 0, width * pixelSize, height * pixelSize);
    // drawGrid();
}

void PixelArtScene::drawGrid() {
    QPen gridPen(Qt::black);
    gridPen.setWidth(1);
    for (int x = 0; x <= fieldSizeX; ++x) {
        this->addLine(x * pixelSize, 0, x * pixelSize, fieldSizeY * pixelSize, gridPen);

    }

    for (int y = 0; y <= fieldSizeY; ++y) {
        this->addLine(0, y * pixelSize, fieldSizeX * pixelSize, y * pixelSize, gridPen);
    }
}
