#ifndef FIELDSCENE_H
#define FIELDSCENE_H
#include <QGraphicsScene>

#include <QGraphicsScene>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

#include "toolforfieldinteractive.h"
#include "toolconfiguration.h"
#include "pixelitem.h"

class FieldScene : public QGraphicsScene {
    Q_OBJECT

public:
    FieldScene(int fieldSizeX, int fieldSizeY, ToolConfiguration* config,  QObject *parent = nullptr);
    ~FieldScene() override;

    // int pixelSize() const;

    void setTool(ToolForFieldInteractive *tool);
    int m_fieldSizeX;
    int m_fieldSizeY;
    int m_pixelSize;
public slots:
    void OnPixelSizeChanged(int newSize);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void drawPixel(const QPoint &scenePos);
    void setupScene();
    bool checkBorders(const QPointF& point);

    ToolForFieldInteractive *m_tool;
    ToolForFieldInteractive* tool;
    ToolConfiguration* m_config;

    QRectF* selectedRect;
    QPointF* lastMouseCoord;
    QGraphicsRectItem* selectionArea = nullptr;
};

#endif // FIELDSCENE_H
