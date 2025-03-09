#include "fieldcontroller.h"
FieldController::FieldController(FieldView* fieldView, int fieldSizeX, int fieldSizeY, QMainWindow* parent)
    : fieldView(fieldView),
    fieldSizeX(fieldSizeX),
    fieldSizeY(fieldSizeY)
{
    config = new ToolConfiguration();
    scene = new FieldScene(fieldSizeX, fieldSizeY, config, fieldView);
    fieldView->setScene(scene);
    fieldView->setMouseTracking(true); // Важно для получения событий перемещения мыши
}



void FieldController::drawGrid() {
    QPen gridPen(Qt::black);
    gridPen.setWidth(1);
    for (int x = 0; x <= fieldSizeX; ++x) {
        scene->addLine(x * pixelSize, 0, x * pixelSize, fieldSizeY * pixelSize, gridPen);

    }

    for (int y = 0; y <= fieldSizeY; ++y) {
        scene->addLine(0, y * pixelSize, fieldSizeX * pixelSize, y * pixelSize, gridPen);
    }
}

void FieldController::mousePressEvent(QMouseEvent* event) {
    qDebug() << "press\n";
}

FieldScene* FieldController::getScene() {
    return scene;
}
