#ifndef PIXELARTSCENE_H
#define PIXELARTSCENE_H
#include <QGraphicsScene>
#include <QImage>
#include <QColor>
#include <QGraphicsView>
#include <QMouseEvent>

class PixelArtScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PixelArtScene(QObject *parent = nullptr);
    PixelArtScene(int width, int height, QObject *parent = nullptr);
    void drawGrid();


private:
    // QImage m_image;
    int pixelSize;
    QColor color;
    int fieldSizeX;
    int fieldSizeY;

    // void drawPixel(const QPoint &pos);
};

#endif // PIXELARTSCENE_H
