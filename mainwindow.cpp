#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QInputDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolconfiguration.h"
#include "pencil.h"
#include "eraser.h"
#include "inputfieldsize.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentColor(Qt::black)
{
    ui->setupUi(this);
    config = new ToolConfiguration();
    graphicsView = new FieldView(this);
    ui->FieldLayout->addWidget(graphicsView);
    // fieldController = new FieldController(graphicsView, config, this);
    scene = new FieldScene(config, graphicsView);
    graphicsView->setScene(scene);
    graphicsView->setMouseTracking(true);
    connect(graphicsView, &FieldView::pixelSizeChanged, scene, &FieldScene::OnPixelSizeChanged);

    dbManager = new PixelArtDatabaseManager(dbPath, this);
    qDebug() << config->pixelSize;


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(currentColor, this, "Select Color");
    if (color.isValid()) {
        config->currentColor = color;
    }
}

void MainWindow::saveImageToDb() {
    if (dbManager->createTable(tableName)) {
        qDebug() << "Table created successfully.";
    } else {
        qDebug() << "Failed to create table.";
    }
    QImage image = getImageOfField();
    if (dbManager->saveImage(image, tableName)) {
        qDebug() << "Image saved successfully.";
    } else {
        qDebug() << "Failed to save image.";
    }
}



void MainWindow::on_pencil_clicked()
{
    scene->setTool(new Pencil());
}


void MainWindow::on_eraser_clicked()
{
    scene->setTool(new Eraser());
}


void MainWindow::on_actionsave_image_triggered()
{
    savePixelArt();
}

QImage MainWindow::getImageOfField() {
    QImage image(config->fieldSizeX, config->fieldSizeY, QImage::Format_ARGB32);
    image.fill(Qt::transparent); // Заполняем прозрачным цветом

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, false); // Отключаем сглаживание для pixel art эффекта
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false); // Отключаем сглаживание трансформаций

    scene->render(&painter, QRectF(), scene->sceneRect());
    return image;
}

void MainWindow::savePixelArt() {

    QImage image = getImageOfField();
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Pixel Art", "", "PNG Image (*.png)");
    if (!fileName.isEmpty()) {
        if (image.save(fileName, "PNG")) {
            qDebug() << "Pixel art saved to" << fileName;
        } else {
            qDebug() << "Error saving pixel art to" << fileName;
        }
    }
}


void MainWindow::on_selectedAreaSize_valueChanged(int value)
{
    ui->selectedAreaSizeLabel->setText(QString::number(value));
    config->selectedRectSize = value;
}


void MainWindow::on_FieldSizeConfig_clicked()
{
    InputFieldSize fieldSizeDialog("size x", "size y");

    int result = fieldSizeDialog.exec();

    if (result == QDialog::Accepted) {
        QString text1 = fieldSizeDialog.getText1();
        QString text2 = fieldSizeDialog.getText2();
        config->fieldSizeX = text1.toInt();
        config->fieldSizeY = text2.toInt();
        scene->setupScene();
        graphicsView->recalculatePixelSize();

    } else {
        QMessageBox::information(nullptr, "Input", "Dialog cancelled");
    }
}


void MainWindow::on_actionimport_to_database_triggered()
{
    saveImageToDb();
}

int MainWindow::getImageIdFromUser() {
    bool ok;
    int imageId = QInputDialog::getInt(
        nullptr,
        "Enter Image ID",
        "Image ID:",
        1,
        1,
        1000,
        1,
        &ok
        );

    if (ok) {
        return imageId;
    } else {
        return -1;
    }
}


void MainWindow::on_actionexport_from_database_triggered()
{
    int imageId = getImageIdFromUser();
    QImage loadedImage = dbManager->loadImage(tableName, imageId);
    if (!loadedImage.isNull()) {
        scene->setupScene(loadedImage);
    } else {
        qDebug() << "Failed to load image.";
    }




}

