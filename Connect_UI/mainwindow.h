#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>

namespace Ui {
    class MainWindow;
}



//#define IMAGE_ICON "images/gomoku.png"
#define IMAGE_BLACK ":/images/black"
#define IMAGE_WHITE ":/images/white"


enum Player : int
{
    NO_PLAYER = 0,
    BLACK = 1,
    WHITE = 2,
};

static const int BOARD_LENGTH = 15;

static const int STONE_SIZE = 21;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    
    int fields[BOARD_LENGTH][BOARD_LENGTH];
    int remainingFields;
    
    QPixmap canvas;
    
    Player turn;
    int winner;
    
    QImage field_blk;
    QImage field_wht;
    
    void initialize(); // used to reset the game
    void make_a_move();
    void fieldClicked(int x, int y);
    int check(int x, int y, int step_x, int step_y, int* marker_x, int* marker_y);
    void showResult();
    
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    
    bool eventFilter(QObject* object, QEvent* event);
    
    public slots:
    void newGame();
    void saveScreenshot();
    void showAboutDialog();
    //TODO add save game
    //TODO add undo last move
};

#endif // MAINWINDOW_H
