#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QColorDialog>
#include "fieldcontroller.h"
#include "fieldview.h"
#include "fieldscene.h"
#include "toolconfiguration.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QColor currentColor;

protected:
    // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    // FieldController* fieldController;

    FieldScene* scene;
    int pixelSize = 10;
    ToolConfiguration* config;

};
#endif // MAINWINDOW_H
