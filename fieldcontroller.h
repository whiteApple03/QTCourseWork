#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H
#include <QMouseEvent>
#include <QGraphicsView>
#include <QMainWindow>

#include "toolforfieldinteractive.h"
#include "fieldcontroller.h"
#include "pixelitem.h"
#include "pencil.h"
#include "fieldscene.h"
#include "fieldview.h"

class FieldController
{
public:
    FieldController(FieldView* fieldView, int fieldSizeX, int fieldSizeY, QMainWindow* parant);
    FieldScene* getScene();


protected:
    void mousePressEvent(QMouseEvent *event);

private:
    FieldView* fieldView;
    FieldScene *scene;  // Заменили QGraphicsScene на FieldScene
    void drawGrid();
    int fieldSizeX;
    int fieldSizeY;
    int pixelSize;
    ToolForFieldInteractive* tool;

};

#endif // FIELDCONTROLLER_H
