#ifndef FIELDVIEW_H
#define FIELDVIEW_H
#include <QGraphicsView>
#include <QResizeEvent>
#include <QDebug>

#include "fieldscene.h"

class FieldView : public QGraphicsView {
    Q_OBJECT

public:
    FieldView(QWidget *parent = nullptr) : QGraphicsView(parent) {}

    void recalculatePixelSize() {
        FieldScene* m_scene = dynamic_cast<FieldScene*>(this->scene());
        if (!m_scene) return;

        QSize viewportSize = viewport()->size();
        if (viewportSize.width() <= 0 || viewportSize.height() <= 0) return;

        int newPixelSize = qMin(viewportSize.width() / m_scene->m_config->fieldSizeX, viewportSize.height() / m_scene->m_config->fieldSizeY);

        if (newPixelSize != m_scene->m_config->pixelSize) {
            emit pixelSizeChanged(newPixelSize);
        }
    }

signals:
    void pixelSizeChanged(int newSize);

protected:
    void resizeEvent(QResizeEvent *event) override {
        QGraphicsView::resizeEvent(event);
        recalculatePixelSize();
    }



};
#endif // FIELDVIEW_H

