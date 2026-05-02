#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"
#include "sizeselect.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void showBoard();

private:
    Ui::MainWindow *ui;
    class SizeSelect* SizeSelect;
    class Board* Board;
    QHBoxLayout* layout;
};
#endif // MAINWINDOW_H
