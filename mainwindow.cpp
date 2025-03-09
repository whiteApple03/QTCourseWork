#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentColor(Qt::black)
{
    ui->setupUi(this);
    FieldView* graphicsView = new FieldView(this);
    ui->FieldLayout->addWidget(graphicsView);
    fieldController = new FieldController(graphicsView, 32, 32, this);
    connect(graphicsView, &FieldView::pixelSizeChanged, fieldController->getScene(), &FieldScene::OnPixelSizeChanged);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(currentColor, this, "Select Color");
    if (color.isValid()) {
        currentColor = color;
    }
}

