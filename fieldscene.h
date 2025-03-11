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
    FieldScene(ToolConfiguration* config,  QObject *parent = nullptr);
    ~FieldScene() override;

    ToolConfiguration* m_config;
    void setTool(ToolForFieldInteractive *tool);
public slots:
    void OnPixelSizeChanged(int newSize);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void drawPixel(const QPointF &scenePos);
    void setupScene();
    bool checkBorders(const QPointF& point);
    int getOffsetXAndValidateTopLeftX(int &offsetX);
    int getOffsetYAndValidateTopLeftY(int &offsetY);
    void addSelectedArea(int topLeftX, int topLeftY, int selectedAreaWidth, int selectedAreaHeight);
    void paintSelectedArea(int, int, QGraphicsSceneMouseEvent*);

    ToolForFieldInteractive *m_tool;


    QRectF* selectedRect;
    QPointF* lastMouseCoord;
    QGraphicsRectItem* selectionArea = nullptr;
};

#endif // FIELDSCENE_H
