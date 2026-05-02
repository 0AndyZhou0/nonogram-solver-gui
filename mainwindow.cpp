#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SizeSelect = new class SizeSelect();
    Board = new class Board();

    layout = new QGridLayout(centralWidget());
    // Add expanding spacers in the corners or sides
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0);
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 2);
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0);
    layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 2);

    // Center widget in the middle cell (1,1)
    layout->addWidget(SizeSelect, 1, 1);

    connect(SizeSelect, &SizeSelect::nextButton_clicked, this, &MainWindow::showBoard);
    // this->setCentralWidget(SizeSelect);
}

void MainWindow::showBoard()
{
    // this->setCentralWidget(Board);
    // qDebug() << SizeSelect->getRows() << SizeSelect->getCols();
    Board->setRows(SizeSelect->getRows());
    Board->setCols(SizeSelect->getCols());
    Board->show();
    Board->createBoard();

    SizeSelect->hide();
    layout->replaceWidget(SizeSelect, Board);
}

MainWindow::~MainWindow()
{
    delete ui;
}
