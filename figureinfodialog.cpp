#include "figureinfodialog.h"
#include "ui_figureinfodialog.h"

FigureInfoDialog::FigureInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FigureInfoDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    QStringList headers = {"Shape", "Size", "Rotation"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

FigureInfoDialog::~FigureInfoDialog()
{
    delete ui;
}

void FigureInfoDialog::updateTable(const QList<QMap<QString, QVariant>>& figures)
{
    ui->tableWidget->setRowCount(figures.size());

    for (int row = 0; row < figures.size(); ++row) {
        const QMap<QString, QVariant>& figure = figures[row];
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(figure["shape"].toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(figure["size"].toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(figure["rotation"].toString()));
    }
}
