#include "fieldscene.h"
#include "pencil.h"


FieldScene::FieldScene(int fieldSizeX, int fieldSizeY, QObject *parent)
    : QGraphicsScene(parent),
    m_fieldSizeX(fieldSizeX),
    m_fieldSizeY(fieldSizeY),
    m_pixelSize(10) // Default pixel size
{
    m_tool = new Pencil();
    setSceneRect(0, 0, fieldSizeX * m_pixelSize, fieldSizeY * m_pixelSize);
    setupScene();
}

void FieldScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    drawPixel(event->scenePos().toPoint());
}

void FieldScene::drawPixel(const QPoint &scenePos) {

    if (PixelItem* rectItem = dynamic_cast<PixelItem*>(itemAt(scenePos, QTransform()))) {
        rectItem->setColor(Qt::black);
    }
}
void FieldScene::OnPixelSizeChanged(int newSize) {
    setSceneRect(0, 0, m_fieldSizeX * newSize, m_fieldSizeY * newSize);
    for (auto item : items()) {
        if (PixelItem* rectItem = dynamic_cast<PixelItem*>(item)) {
            int x = rectItem->rect().x() / m_pixelSize;
            int y = rectItem->rect().y() / m_pixelSize;
            rectItem->setRect(x*newSize, y*newSize, newSize, newSize);
        }
    }
    m_pixelSize = newSize;

}

void FieldScene::setupScene() {
    clear();
    setSceneRect(0, 0, m_fieldSizeX * m_pixelSize, m_fieldSizeY * m_pixelSize);

    for (int y = 0; y < m_fieldSizeY; ++y) {
        for (int x = 0; x < m_fieldSizeX; ++x) {
            PixelItem *pixel = new PixelItem(x * m_pixelSize, y * m_pixelSize, m_pixelSize, m_pixelSize);
            if (y % 2 == 0 && x % 2 == 0) {
                 pixel->setColor(Qt::gray, 128);

            } else if (y % 2 != 0 && x % 2 != 0) {
                pixel->setColor(Qt::gray, 128);
            }
            addItem(pixel);
        }
    }
}

FieldScene::~FieldScene() {
    delete m_tool;
}
