#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Square;
}

class Square : public QLabel
{
    Q_OBJECT

public:
    explicit Square(QWidget *parent = nullptr);
    ~Square();
    void Mark_Impossible();

private:
    Ui::Square *ui;
};

#endif // SQUARE_H
