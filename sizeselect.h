#ifndef SIZESELECT_H
#define SIZESELECT_H

#include <QWidget>

namespace Ui {
class SizeSelect;
}

class SizeSelect : public QWidget
{
    Q_OBJECT

public slots:
    void on_nextButton_clicked();

public:
    explicit SizeSelect(QWidget *parent = nullptr);
    ~SizeSelect();
    int getRows();
    int getCols();

signals:
    void nextButton_clicked();

private:
    Ui::SizeSelect *ui;
    int rows;
    int cols;
};

#endif // SIZESELECT_H
