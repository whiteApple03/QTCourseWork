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
#include "pixelartdatabasemanager.h"
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
    void on_pencil_clicked();

    void on_eraser_clicked();

    void on_actionsave_image_triggered();


    void on_selectedAreaSize_valueChanged(int value);

    void on_FieldSizeConfig_clicked();

    void on_actionimport_to_database_triggered();

    void on_actionexport_from_database_triggered();

private:
    QImage getImageOfField();
    void saveImageToDb();
    int getImageIdFromUser();

    Ui::MainWindow *ui;
    // FieldController* fieldController;
    FieldView* graphicsView;
    FieldScene* scene;
    int pixelSize = 10;
    ToolConfiguration* config;
    const QString dbPath = "./pixelArt.db";
    const QString tableName = "images";
    PixelArtDatabaseManager* dbManager;

    void savePixelArt();

};
#endif // MAINWINDOW_H
