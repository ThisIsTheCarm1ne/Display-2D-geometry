#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QGraphicsScene>
#include <QList>
#include <QMainWindow>
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
    void on_drawSelectedFigure(const QMap<QString, QVariant> &figure);
    void on_drawAllFiguresButton_clicked();
    void on_saveFiguresButton_clicked();
    void on_loadFiguresButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QMap<QString, QVariant>> figures;
    FigureInfoDialog *figureInfoDialog;
    void drawFigure(const QMap<QString, QVariant> &figure);
    void saveFiguresToFile(const QString &fileName);
    void loadFiguresFromFile(const QString &fileName);
};
#endif // MAINWINDOW_H
