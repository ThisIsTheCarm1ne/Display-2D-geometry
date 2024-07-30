#ifndef FIGUREINFODIALOG_H
#define FIGUREINFODIALOG_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QTableWidgetItem>

namespace Ui {
class FigureInfoDialog;
}

class FigureInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FigureInfoDialog(QWidget *parent = nullptr);
    ~FigureInfoDialog();

    void updateTable(const QList<QMap<QString, QVariant>>& figures); // Function to update the table

signals:
    void figureSelected(const QMap<QString, QVariant>& figure);

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::FigureInfoDialog *ui;
    QList<QMap<QString, QVariant>> figures;
};

#endif // FIGUREINFODIALOG_H
