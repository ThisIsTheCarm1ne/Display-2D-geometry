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

    connect(ui->tableWidget, &QTableWidget::itemClicked, this, &FigureInfoDialog::on_tableWidget_itemClicked);
}

FigureInfoDialog::~FigureInfoDialog()
{
    delete ui;
}

void FigureInfoDialog::updateTable(const QList<QMap<QString, QVariant>>& figures)
{
    this->figures = figures;
    ui->tableWidget->setRowCount(figures.size());

    for (int row = 0; row < figures.size(); ++row) {
        const QMap<QString, QVariant>& figure = figures[row];
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(figure["shape"].toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(figure["size"].toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(figure["rotation"].toString()));
    }
}
void FigureInfoDialog::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    emit figureSelected(figures[row]);
}
