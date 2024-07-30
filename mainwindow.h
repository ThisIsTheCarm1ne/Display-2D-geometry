#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QMap>
#include <QVariant>

#include "figureinfodialog.h"

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

private slots:
    void on_addFigureButton_clicked();
    void on_clearCanvasButton_clicked();
    void on_showFigureInfoButton_clicked();
    void on_drawSelectedFigure(const QMap<QString, QVariant>& figure);
    void on_drawAllFiguresButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QMap<QString, QVariant>> figures;
    FigureInfoDialog *figureInfoDialog;
    void drawFigure(const QMap<QString, QVariant>& figure);
};
#endif // MAINWINDOW_H
