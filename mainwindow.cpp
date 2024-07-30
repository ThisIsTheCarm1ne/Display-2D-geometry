#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , figureInfoDialog(new FigureInfoDialog(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    // Connect the button click signal to the slot
    connect(ui->addAShape, &QPushButton::clicked, this, &MainWindow::on_addFigureButton_clicked);
    connect(ui->clearCanvas, &QPushButton::clicked, this, &MainWindow::on_clearCanvasButton_clicked);
    connect(ui->showFigureInfoButton, &QPushButton::clicked, this, &MainWindow::on_showFigureInfoButton_clicked);
    connect(figureInfoDialog, &FigureInfoDialog::figureSelected, this, &MainWindow::on_drawSelectedFigure);
    connect(ui->drawAllFiguresButton, &QPushButton::clicked, this, &MainWindow::on_drawAllFiguresButton_clicked);
    connect(ui->saveFiguresButton, &QPushButton::clicked, this, &MainWindow::on_saveFiguresButton_clicked);
    connect(ui->loadFiguresButton, &QPushButton::clicked, this, &MainWindow::on_loadFiguresButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addFigureButton_clicked()
{
    QListWidgetItem *currentItem = ui->listOfShapes->currentItem();
    if (!currentItem) {
        return;
    }
    QString selectedShape = currentItem->text();
    int size = ui->size->value();
    int rotation = ui->rotation->value();

    QMap<QString, QVariant> figure;
    figure["shape"] = selectedShape;
    figure["size"] = size;
    figure["rotation"] = rotation;

    drawFigure(figure);
    figures.append(figure);
}

void MainWindow::on_clearCanvasButton_clicked()
{
    scene->clear();  // Clear all items from the scene
}

void MainWindow::on_showFigureInfoButton_clicked()
{
    figureInfoDialog->updateTable(figures); // Update the table with stored figure information
    figureInfoDialog->exec(); // Show the dialog modally
}

void MainWindow::on_drawSelectedFigure(const QMap<QString, QVariant>& figure)
{
    drawFigure(figure);
}

void MainWindow::on_drawAllFiguresButton_clicked()
{
    for (const auto& figure : figures) {
        drawFigure(figure);
    }
}

void MainWindow::drawFigure(const QMap<QString, QVariant>& figure)
{
    QString selectedShape = figure["shape"].toString();
    int size = figure["size"].toInt();
    int rotation = figure["rotation"].toInt();

    QGraphicsItem *item = nullptr;

    if (selectedShape == "Circle") {
        item = scene->addEllipse(0, 0, size, size);
    } else if (selectedShape == "Square") {
        item = scene->addRect(0, 0, size, size);
    } else if (selectedShape == "Triangle") {
        QPolygonF triangle;
        triangle << QPointF(0, 0) << QPointF(size, 0) << QPointF(0, size);
        item = scene->addPolygon(triangle);
    } else if (selectedShape == "N-gon") {
        int n = 5;
        QPolygonF polygon;
        for (int i = 0; i < n; ++i) {
            double angle = (i * 2 * M_PI) / n;
            polygon << QPointF(size * cos(angle), size * sin(angle));
        }
        item = scene->addPolygon(polygon);
    }

    if (item) {
        item->setTransformOriginPoint(size / 2, size / 2);
        item->setRotation(rotation);
    }
}

void MainWindow::on_saveFiguresButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Figures"), "", tr("CSV Files (*.csv)"));
    if (!fileName.isEmpty()) {
        saveFiguresToFile(fileName);
    }
}

void MainWindow::on_loadFiguresButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Figures"), "", tr("CSV Files (*.csv)"));
    if (!fileName.isEmpty()) {
        loadFiguresFromFile(fileName);
    }
}

void MainWindow::saveFiguresToFile(const QString &fileName)
{
    QString finalFileName = fileName;
    if (!finalFileName.endsWith(".csv", Qt::CaseInsensitive)) {
        finalFileName += ".csv";
    }

    QFile file(finalFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (const auto &figure : figures) {
            out << figure["shape"].toString() << ","
                << figure["size"].toInt() << ","
                << figure["rotation"].toInt() << "\n";
        }
        file.close();
    } else {
        qDebug() << "Could not open file for writing";
    }
}

void MainWindow::loadFiguresFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        figures.clear();
        scene->clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3) {
                QMap<QString, QVariant> figure;
                figure["shape"] = parts[0];
                figure["size"] = parts[1].toInt();
                figure["rotation"] = parts[2].toInt();
                figures.append(figure);
                drawFigure(figure);
            }
        }
        file.close();
    } else {
        qDebug() << "Could not open file for reading";
    }
}
