#include "sizeselect.h"
#include "ui_sizeselect.h"

#include <QDebug>
#include <QIntValidator>

SizeSelect::SizeSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SizeSelect)
{
    ui->setupUi(this);
    ui->rows_edit->setValidator(new QIntValidator(1, 99, this));
    ui->cols_edit->setValidator(new QIntValidator(1, 99, this));
}

SizeSelect::~SizeSelect()
{
    delete ui;
}

void SizeSelect::on_nextButton_clicked()
{
    rows = ui->rows_edit->text().toInt();
    cols = ui->cols_edit->text().toInt();
    if (!(rows > 0 && rows < 100) || !(cols > 0 && cols < 100)) {
        return; // !TODO: Add error message
    }
    emit nextButton_clicked();
}

int SizeSelect::getRows() {
    return rows;
}

int SizeSelect::getCols() {
    return cols;
}

