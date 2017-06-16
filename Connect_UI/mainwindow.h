#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
namespace Ui {
class MainWindow;
}

//IMAGE ICON DIDN"T ADD
#define WHITE_STONE ":/images/white"
#define BLACK_STONE ":/images/black"
#define STONE_SIZE 21
static const int LENGTH = 10;

enum Player : int{
    NA = 0,
    WHITE = 1,
    BLACK = 2,
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPixmap canvas;
    QImage black;
    QImage white;


    int blocks[LENGTH][LENGTH];
    int blockRemain;
    Player turn;

    int winner;///////////char? String?


void initialize();
void set_board();
//void make_move();
//int check(int x, int y, int step_x, int step_y, int *markerX, int *markerY);
//void showWinner();

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
