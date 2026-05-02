#include "board.h"
#include "ui_board.h"

#include <QPushButton>
#include <QtGlobal>
#include <QStackedLayout>
#include <QPlainTextEdit>

Board::Board(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Board)
{
    ui->setupUi(this);
}

void Board::setRows(size_t rows)
{
    this->rows = rows;
}

void Board::setCols(size_t cols)
{
    this->cols = cols;
}

void Board::createBoard()
{
    layout = new QGridLayout(this);
    // layout->setRowStretch(0, 1);
    // layout->setRowStretch(1, 2);
    // layout->setColumnStretch(0, 1);
    // layout->setColumnStretch(1, 2);
    layout->setSpacing(0);

    int window_width = this->width();
    int window_height = this->height();
    qDebug() << "geometry:" << window_width << window_height;

    int max_size = qMin(window_width * 2 / 3, window_height * 2 / 3);
    int larger_size = qMax(rows, cols);
    int square_size = max_size / larger_size; // !TODO : Handle non symmetric board
    int max_height = square_size * rows;
    int max_width = square_size * cols;
    int font_size = 12; // !TODO: Calc font size using square size / 2;

    QWidget* empty = new QWidget(this);
    QGridLayout* box = new QGridLayout();
    empty->setLayout(box);
    empty->setStyleSheet("padding: 10px;");
    QPushButton* solve_button = new QPushButton("Solve", empty);
    connect(solve_button, &QPushButton::clicked, this, &Board::solve);

    layout->addWidget(empty, 0, 0);


    // !TODO: Change Font to Scale with Window
    // Row Restrictions
    rows_restrictions = new QWidget(this);
    rows_restrictions->setMinimumHeight(max_height);
    rows_restrictions->setMaximumHeight(max_height);
    rows_restrictions->setMinimumWidth(window_width - max_width);
    rows_restrictions_layout = new QVBoxLayout();
    rows_restrictions_layout->setSpacing(0);
    rows_restrictions_layout->setContentsMargins(0, 0, 0, 0);
    rows_restrictions->setLayout(rows_restrictions_layout);

    for (size_t r = 0; r < rows; r++) {
        Restrictions* text_edit = new Restrictions(Restrictions::Type::Row);
        text_edit->setObjectName(QString::number(r));
        text_edit->setWidth(window_width - max_width);
        text_edit->setHeight(square_size);
        text_edit->setStyleSheet("border: 2px solid black;");
        rows_restrictions_layout->addWidget(text_edit);
    }

    layout->addWidget(rows_restrictions, 1, 0);


    // Column Restrictions
    cols_restrictions = new QWidget(this);
    cols_restrictions->setMinimumWidth(max_width);
    cols_restrictions->setMaximumWidth(max_width);
    cols_restrictions->setMinimumHeight(window_height - max_height);
    cols_restrictions_layout = new QHBoxLayout();
    cols_restrictions_layout->setSpacing(0);
    cols_restrictions_layout->setContentsMargins(0, 0, 0, 0);
    cols_restrictions->setLayout(cols_restrictions_layout);

    for (size_t c = 0; c < cols; c++) {
        Restrictions* text_edit = new Restrictions(Restrictions::Type::Column);
        text_edit->setObjectName(QString::number(c));
        text_edit->setWidth(square_size);
        text_edit->setHeight(window_height - max_height);
        text_edit->setStyleSheet("border: 2px solid black;");
        cols_restrictions_layout->addWidget(text_edit);
    }

    layout->addWidget(cols_restrictions, 0, 1);


    // Squares / Actual Board
    board = new QWidget(this);
    board->setMinimumSize(max_width, max_height);
    board->setMaximumSize(max_width, max_height);
    board->setStyleSheet("border: 2px solid black;");
    board_layout = new QGridLayout();
    board_layout->setSpacing(0);
    board_layout->setContentsMargins(0, 0, 0, 0);
    board->setLayout(board_layout);

    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            QWidget* square = new QWidget();
            square->setObjectName(QString::number(r) + " " + QString::number(c));
            square->setStyleSheet("border: 1px solid black;");
            if (c % 2 == 1)
            {
                square->setStyleSheet("background-color: lightblue; border: 1px solid black;"); // !BUG: Stylesheet creates weird visual bug where borders appear smaller when lightblue with smaller squares
            }
            square->setMinimumSize(square_size, square_size);
            square->setMaximumSize(square_size, square_size);
            board_layout->addWidget(square, r, c);
        }
    }

    layout->addWidget(board, 1, 1);


}

void Board::solve()
{
    nonogram_board = new NonogramSolver::NonogramBoard((size_t)rows, (size_t)cols);
    for (size_t r = 0; r < rows; r++)
    {
        QList<int> restrictions = rows_restrictions->findChild<Restrictions*>(QString::number(r))->get_restrictions();
        nonogram_board->set_row_restriction(r, std::vector<u_int32_t>(restrictions.begin(), restrictions.end()));
    }

    for (size_t c = 0; c < cols; c++)
    {
        QList<int> restrictions = cols_restrictions->findChild<Restrictions*>(QString::number(c))->get_restrictions();
        nonogram_board->set_col_restriction(c, std::vector<u_int32_t>(restrictions.begin(), restrictions.end()));
    }
    NonogramSolver::solve(*nonogram_board);
    for (int r = 0; r < nonogram_board->get_height(); r++)
    {
        for (int c = 0; c < nonogram_board->get_width(); c++)
        {
            if (nonogram_board->get(r, c) == 1)
            {
                board->findChild<QWidget*>(QString::number(r) + " " + QString::number(c))->setStyleSheet("background-color: black; border: 1px solid black;");
            }
        }
    }
}

Board::~Board()
{
    delete ui;
}
