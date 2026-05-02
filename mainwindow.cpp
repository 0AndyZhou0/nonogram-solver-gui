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

    connect(SizeSelect, &SizeSelect::nextButton_clicked, this, &MainWindow::showBoard);
    this->setCentralWidget(SizeSelect);
}

void MainWindow::showBoard()
{
    this->setCentralWidget(Board);
    // qDebug() << SizeSelect->getRows() << SizeSelect->getCols();
    Board->setRows(SizeSelect->getRows());
    Board->setCols(SizeSelect->getCols());
    Board->show();
    Board->createBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}
