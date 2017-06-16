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

#define CIRCLE_ICON "circle.png"
#define CROSS_ICON "cross.png"
#define ICON_SIZE 40
static const int length = 10;

enum Player : int{
    NO_PLAYER = 0,
    CIRCLE = 1,
    CROSS = 2,
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
    QImage cross;
    QImage circle;


    int board[length][length];
    int blockRemain;
    Player turn;
    int winner;



protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
