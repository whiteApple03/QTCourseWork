#include <QList>
#include <QPointF>

#include "fieldscene.h"
#include "pencil.h"


FieldScene::FieldScene(int fieldSizeX, int fieldSizeY, ToolConfiguration* config, QObject *parent)
    : QGraphicsScene(parent),
    m_fieldSizeX(fieldSizeX),
    m_fieldSizeY(fieldSizeY),
    m_pixelSize(10),
    m_config(config)
{
    m_tool = new Pencil();
    lastMouseCoord = new QPointF(-1, -1);
    selectedRect = new QRectF(0, 0, config->selectedRectSize, config->selectedRectSize);
    setSceneRect(0, 0, fieldSizeX * m_pixelSize, fieldSizeY * m_pixelSize);
    setupScene();
}

void FieldScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    drawPixel(event->scenePos().toPoint());
}

// void FieldScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {

//     int x = (int)(event->scenePos().x() / m_pixelSize) * m_pixelSize;
//     int y = (int)(event->scenePos().y() / m_pixelSize) * m_pixelSize;
//     qDebug() << x << ' ' << y;
//     QPointF topLeft(x - (m_config->selectedRectSize/2 * m_pixelSize)+1, y - (m_config->selectedRectSize/2 * m_pixelSize)+1);
//     QPointF bottomRight(x + (m_config->selectedRectSize/2 * m_pixelSize)-1, y + (m_config->selectedRectSize/2 * m_pixelSize)-1);

//     const QRectF rect(topLeft, bottomRight);
//     qDebug() << topLeft.x() << ' ' << topLeft.y();
//     qDebug() << bottomRight.x() << ' ' << bottomRight.y();

//     QList<QGraphicsItem*> items = this->items(rect, Qt::IntersectsItemShape, Qt::AscendingOrder, QTransform());
//     if (!items.isEmpty()) {
//         qDebug() << "start";
//         for (auto item : items) {
//             if (PixelItem* rectItem = dynamic_cast<PixelItem*>(item)) {
//                 qDebug() << rectItem->rect().x() / m_pixelSize << rectItem->rect().y() / m_pixelSize;
//                 rectItem->setColor(rectItem->color(), 64);
//             }
//         }
//         qDebug() << "end";
//     }
// }

bool FieldScene::checkBorders(const QPointF &point) {
    return point.x() >= 0 && point.y() >= 0 && point.x() < m_config->fieldSizeX * m_pixelSize && point.y() < m_config->fieldSizeY*m_pixelSize;
}

void FieldScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {



    int x = (int)(event->scenePos().x() / m_pixelSize) * m_pixelSize;
    int y = (int)(event->scenePos().y() / m_pixelSize) * m_pixelSize;



    if ((lastMouseCoord->x() != x || lastMouseCoord->y() != y) && checkBorders(event->scenePos())) {
        delete selectionArea;

        qDebug() << x << " = " << lastMouseCoord->x() << y << " = " << lastMouseCoord->y();

        lastMouseCoord->setX(x);
        lastMouseCoord->setY(y);
        QPointF topLeft(x - (m_config->selectedRectSize/2 * m_pixelSize), y - (m_config->selectedRectSize/2 * m_pixelSize));
        QPointF bottomRight(x + (m_config->selectedRectSize/2 * m_pixelSize), y + (m_config->selectedRectSize/2 * m_pixelSize));

        const QRectF rect(topLeft, bottomRight);
        qDebug() << topLeft.x() << ' ' << topLeft.y();
        qDebug() << bottomRight.x() << ' ' << bottomRight.y();
        selectionArea = new QGraphicsRectItem(topLeft.x(), topLeft.y(), m_config->selectedRectSize*m_pixelSize, m_config->selectedRectSize * m_pixelSize);
        selectionArea->setPen(Qt::NoPen);
        QColor semiBlack(0, 0, 0, 128);
        selectionArea->setBrush(semiBlack);
        addItem(selectionArea);

        QList<QGraphicsItem*> items = this->items(rect, Qt::IntersectsItemShape, Qt::AscendingOrder, QTransform());
        if (!items.isEmpty()) {
            qDebug() << "start";
            for (auto item : items) {
                if (PixelItem* rectItem = dynamic_cast<PixelItem*>(item)) {
                    qDebug() << rectItem->rect().x() / m_pixelSize << rectItem->rect().y() / m_pixelSize;
                    // rectItem->setColor(rectItem->color(), 64);
                }
            }
            qDebug() << "end";
        }
    }


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
