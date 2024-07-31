#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(R"(
        QWidget {
            border-radius: 0px;
        }
        QTableWidget::item:nth-child(odd) {
            background-color: #F4F6FF;
        }
        QTableWidget::item:nth-child(even) {
            background-color: #CBD4FF;
        }
        QSpinBox, QListWidget, QGraphicsView, QPushButton {
            border: 1px solid #AEAEAE;
        }
        QPushButton:focus {
            font-weight: bold;
        }
    )");
    //Removed this style because it's ugly
    /*
    QPushButton {
        background-color: #03353E;
        color: white;
    }
    */

    MainWindow w;
    w.show();
    return a.exec();
}
