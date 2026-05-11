#include "square.h"
#include "ui_square.h"
#include <QPainter>

Square::Square(QWidget *parent)
    : QLabel(parent)
    , ui(new Ui::Square)
{
    ui->setupUi(this);
}

void Square::Mark_Impossible()
{
    QPixmap pixmap(this->width(),this->height());
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);
    QPen pen(Qt::black, 5);
    painter.setPen(pen);

    painter.drawLine(0, 0, this->width(), this->height());
    painter.drawLine(this->width(), 0, 0, this->height());

    this->setPixmap(pixmap);
}

Square::~Square()
{
    delete ui;
}
