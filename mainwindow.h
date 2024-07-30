#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QMap<QString, QVariant>> figures;
    FigureInfoDialog *figureInfoDialog;
};
#endif // MAINWINDOW_H
