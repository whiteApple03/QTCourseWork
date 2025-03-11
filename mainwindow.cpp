#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolconfiguration.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentColor(Qt::black)
{
    ui->setupUi(this);
    config = new ToolConfiguration();
    FieldView* graphicsView = new FieldView(this);
    ui->FieldLayout->addWidget(graphicsView);
    // fieldController = new FieldController(graphicsView, config, this);
    scene = new FieldScene(config, graphicsView);
    graphicsView->setScene(scene);
    graphicsView->setMouseTracking(true);
    connect(graphicsView, &FieldView::pixelSizeChanged, scene, &FieldScene::OnPixelSizeChanged);
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

