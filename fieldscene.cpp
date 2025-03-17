#include <QList>
#include <QPointF>


#include "fieldscene.h"
#include "pencil.h"
#include "fieldview.h"


FieldScene::FieldScene(ToolConfiguration* config, QObject *parent)
    : QGraphicsScene(parent),
    m_config(config)
{
    m_tool = new Pencil();
    lastMouseCoord = new QPointF(-1, -1);
    selectedRect = new QRectF(0, 0, config->selectedRectSize, config->selectedRectSize);
    setSceneRect(0, 0, m_config->fieldSizeX * m_config->pixelSize, m_config->fieldSizeY * m_config->pixelSize);
    setupScene();
}



void FieldScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int x = (int)(event->scenePos().x() / m_config->pixelSize) * m_config->pixelSize;
    int y = (int)(event->scenePos().y() / m_config->pixelSize) * m_config->pixelSize;
    if (event->buttons() & Qt::LeftButton) {
        drawPixel();
    }
    paintSelectedArea(x, y, event);



}

void FieldScene::paintSelectedArea(int x, int y, QGraphicsSceneMouseEvent* event) {
    if (!checkBorders(event->scenePos())) {
        delete selectionArea;
        selectionArea = nullptr;
        lastMouseCoord->setX(-1);
        lastMouseCoord->setY(-1);
    }
    if ((lastMouseCoord->x() != x || lastMouseCoord->y() != y) && checkBorders(event->scenePos())) {
        delete selectionArea;
        selectionArea = nullptr;
        lastMouseCoord->setX(x);
        lastMouseCoord->setY(y);

        int topLeftX = (x - (m_config->selectedRectSize/2 * m_config->pixelSize));

        int topLeftY = y - (m_config->selectedRectSize/2 * m_config->pixelSize);

        int offsetX = getOffsetXAndValidateTopLeftX(topLeftX);
        int offsetY = getOffsetYAndValidateTopLeftY(topLeftY);

        int selectedAreaWidth = m_config->selectedRectSize*m_config->pixelSize + offsetX;
        int selectedAreaHeight = m_config->selectedRectSize * m_config->pixelSize + offsetY;
        addSelectedArea(topLeftX, topLeftY, selectedAreaWidth, selectedAreaHeight);
    }
}
bool FieldScene::checkBorders(const QPointF &point) {
    return point.x() >= 0 && point.y() >= 0 && point.x() < m_config->fieldSizeX * m_config->pixelSize && point.y() < m_config->fieldSizeY*m_config->pixelSize;
}

int FieldScene::getOffsetXAndValidateTopLeftX(int& topLeftX) {
    int offsetX = 0;
    if (topLeftX < 0) {
        offsetX = topLeftX;
        topLeftX = 0;
    }
    if (topLeftX + m_config->selectedRectSize*m_config->pixelSize > m_config->fieldSizeX * m_config->pixelSize) {
        offsetX = m_config->fieldSizeX * m_config->pixelSize - m_config->selectedRectSize*m_config->pixelSize - topLeftX;
    }
    return offsetX;
}

int FieldScene::getOffsetYAndValidateTopLeftY(int &topLeftY) {
    int offsetY = 0;
    if (topLeftY < 0) {
        offsetY = topLeftY;
        topLeftY = 0;
    }
    if (topLeftY + m_config->selectedRectSize*m_config->pixelSize > m_config->fieldSizeY * m_config->pixelSize) {
        offsetY = m_config->fieldSizeY * m_config->pixelSize - m_config->selectedRectSize*m_config->pixelSize - topLeftY;
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
    if (event->buttons() & Qt::LeftButton) {
        drawPixel();
    }
}

void FieldScene::drawPixel() {
    if (selectionArea != nullptr) {
        QList<QGraphicsItem *> items = this->items(selectionArea->rect(), Qt::IntersectsItemShape, Qt::AscendingOrder,  QTransform());
        m_tool->draw(items, m_config);
    }
}
void FieldScene::OnPixelSizeChanged(int newSize) {
    setSceneRect(0, 0, m_config->fieldSizeX * newSize, m_config->fieldSizeY * newSize);
    for (auto item : items()) {
        if (PixelItem* rectItem = dynamic_cast<PixelItem*>(item)) {
            int x = rectItem->rect().x() / m_config->pixelSize;
            int y = rectItem->rect().y() / m_config->pixelSize;
            rectItem->setRect(x*newSize, y*newSize, newSize, newSize);
        }
    }
    m_config->pixelSize = newSize;
}

void FieldScene::setupScene() {
    clear();
    setSceneRect(0, 0, m_config->fieldSizeX * m_config->pixelSize, m_config->fieldSizeY * m_config->pixelSize);

    for (int y = 0; y < m_config->fieldSizeY; ++y) {
        for (int x = 0; x < m_config->fieldSizeX; ++x) {
            PixelItem *pixel = new PixelItem(x * m_config->pixelSize, y * m_config->pixelSize, m_config->pixelSize, m_config->pixelSize);
            if (y % 2 == 0 && x % 2 == 0) {
                pixel->setColor(Qt::gray, 128);

            } else if (y % 2 != 0 && x % 2 != 0) {
                pixel->setColor(Qt::gray, 128);
            }
            addItem(pixel);
        }
    }
}

void FieldScene::setupScene(QImage& image) {

    clear();
    QPixmap pixmap = QPixmap::fromImage(image);
    m_config->fieldSizeX = image.width();
    m_config->fieldSizeY = image.height();
    setSceneRect(0, 0, m_config->fieldSizeX * m_config->pixelSize, m_config->fieldSizeY * m_config->pixelSize);
    // Итерируемся по всем пикселям изображения
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QColor pixelColor = image.pixelColor(x, y);

            PixelItem *pixel = new PixelItem(x * m_config->pixelSize, y * m_config->pixelSize, m_config->pixelSize, m_config->pixelSize);
            pixel->setColor(pixelColor);
            addItem(pixel);
        }
    }
}

void FieldScene::setTool(ToolForFieldInteractive* tool) {
    if (m_tool != nullptr) {
        delete m_tool;
        m_tool = nullptr;
    }
    m_tool = tool;
}

FieldScene::~FieldScene() {
    delete m_tool;
}
