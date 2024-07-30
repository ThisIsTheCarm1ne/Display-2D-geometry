#ifndef FIGUREINFODIALOG_H
#define FIGUREINFODIALOG_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QVariant>

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

private:
    Ui::FigureInfoDialog *ui;
};

#endif // FIGUREINFODIALOG_H
