#ifndef FIELDSCENE_H
#define FIELDSCENE_H
#include <QGraphicsScene>

#include <QGraphicsScene>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

#include "toolforfieldinteractive.h"
#include "pixelitem.h"

class FieldScene : public QGraphicsScene {
    Q_OBJECT

public:
    FieldScene(int fieldSizeX, int fieldSizeY, QObject *parent = nullptr);
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
    // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:

    ToolForFieldInteractive *m_tool;
    void setupScene();

    void drawPixel(const QPoint &scenePos);
};

#endif // FIELDSCENE_H
