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



void FieldScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int x = (int)(event->scenePos().x() / m_pixelSize) * m_pixelSize;
    int y = (int)(event->scenePos().y() / m_pixelSize) * m_pixelSize;

    paintSelectedArea(x, y, event);
}

void FieldScene::paintSelectedArea(int x, int y, QGraphicsSceneMouseEvent* event) {
    if ((lastMouseCoord->x() != x || lastMouseCoord->y() != y) && checkBorders(event->scenePos())) {
        delete selectionArea;
        selectionArea = nullptr;
        lastMouseCoord->setX(x);
        lastMouseCoord->setY(y);

        int topLeftX = (x - (m_config->selectedRectSize/2 * m_pixelSize));

        int topLeftY = y - (m_config->selectedRectSize/2 * m_pixelSize);

        int offsetX = getOffsetXAndValidateTopLeftX(topLeftX);
        int offsetY = getOffsetYAndValidateTopLeftY(topLeftY);

        int selectedAreaWidth = m_config->selectedRectSize*m_pixelSize + offsetX;
        int selectedAreaHeight = m_config->selectedRectSize * m_pixelSize + offsetY;
        addSelectedArea(topLeftX, topLeftY, selectedAreaWidth, selectedAreaHeight);
    }
}
bool FieldScene::checkBorders(const QPointF &point) {
    return point.x() >= 0 && point.y() >= 0 && point.x() < m_config->fieldSizeX * m_pixelSize && point.y() < m_config->fieldSizeY*m_pixelSize;
}

int FieldScene::getOffsetXAndValidateTopLeftX(int& topLeftX) {
    int offsetX = 0;
    if (topLeftX < 0) {
        offsetX = topLeftX;
        topLeftX = 0;
    }
    if (topLeftX + m_config->selectedRectSize*m_pixelSize > m_config->fieldSizeX * m_pixelSize) {
        offsetX = m_config->fieldSizeX * m_pixelSize - m_config->selectedRectSize*m_pixelSize - topLeftX;
    }
    return offsetX;
}

int FieldScene::getOffsetYAndValidateTopLeftY(int &topLeftY) {
    int offsetY = 0;
    if (topLeftY < 0) {
        offsetY = topLeftY;
        topLeftY = 0;
    }
    if (topLeftY + m_config->selectedRectSize*m_pixelSize > m_config->fieldSizeY * m_pixelSize) {
        offsetY = m_config->fieldSizeY * m_pixelSize - m_config->selectedRectSize*m_pixelSize - topLeftY;
    }
    return offsetY;
}

void FieldScene::addSelectedArea(int topLeftX, int topLeftY, int selectedAreaWidth, int selectedAreaHeight ) {
    selectionArea = new QGraphicsRectItem(topLeftX, topLeftY, selectedAreaWidth, selectedAreaHeight);
    selectionArea->setPen(Qt::NoPen);
    QColor semiBlack(0, 0, 0, 128);
    selectionArea->setBrush(semiBlack);
    addItem(selectionArea);
}

void FieldScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    drawPixel(event->scenePos());
}

void FieldScene::drawPixel(const QPointF &scenePos) {
    qDebug() << "press " << scenePos.x() <<  ' ' <<  scenePos.y();

    // if (PixelItem* rectItem = dynamic_cast<PixelItem*>(itemAt(scenePos.toPoint(), QTransform()))) {
    //     rectItem->setColor(Qt::black);
    // } else if (QGraphicsRectItem* area = dynamic_cast<QGraphicsRectItem*>(itemAt(scenePos, QTransform()))) {
    if (selectionArea != nullptr) {
        QList<QGraphicsItem *> items = items(selectionArea->rect(), Qt::IntersectsItemShape, Qt::AscendingOrder,  QTransform());
        for(auto item : items) {
            PixelItem* rectItem = dynamic_cast<PixelItem*>(item);
            rectItem->setColor(Qt::black);
        }
    }
    // }
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
