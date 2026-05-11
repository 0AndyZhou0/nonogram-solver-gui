#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <qgridlayout.h>
#include "solver.hpp"
#include "square.h"
#include "restrictions.h"

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    void setRows(size_t rows);
    void setCols(size_t cols);
    void createBoard();

private:
    Ui::Board *ui;
    size_t rows;
    size_t cols;
    QWidget* rows_restrictions;
    QWidget* cols_restrictions;
    QWidget* board;
    QGridLayout* layout;
    QGridLayout* board_layout;
    QVBoxLayout* rows_restrictions_layout;
    QHBoxLayout* cols_restrictions_layout;
    NonogramSolver::NonogramBoard* nonogram_board;

private slots:
    void solve();
};

#endif // BOARD_H
