#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QMessageBox>

//#include <Q

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    canvas(LENGTH * STONE_SIZE - 1, LENGTH * STONE_SIZE - 1),
    black(BLACK_STONE), white(WHITE_STONE)
{
    ui->setupUi(this);
    ui->boardLabel->installEventFilter(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize(){
    for (int i = 0; i != LENGTH; i++){
        for (int j = 0; j!= LENGTH; j++){
            this->blocks[i][j] = NA;
        }
    }

    turn = BLACK;

    //Black first
    ui->statusLabel->setText("Black");

    blockRemain = LENGTH * LENGTH;

    ui->boardLabel->setFixedSize(LENGTH * STONE_SIZE, LENGTH * STONE_SIZE);

    set_board();
}



void MainWindow::set_board()
{
    QPainter painter(&canvas);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::NoPen);

    // background
    //set background
    QRect boardBackground(0,0, canvas.width(), canvas.height());
    painter.fillRect(boardBackground, QColor(221, 163, 68));

    // fields
    painter.setPen(Qt::black);
    for(int x = 0; x < LENGTH; x++)
    {
        for(int y = 0; y < LENGTH; y++)
        {
            painter.drawRect(x * STONE_SIZE - 1, y * STONE_SIZE - 1, STONE_SIZE, STONE_SIZE);

            if(blocks[x][y] == BLACK)
            {
                painter.drawImage(QPoint(x * STONE_SIZE, y * STONE_SIZE), black);
            }
            else if(blocks[x][y] == WHITE)
            {
                painter.drawImage(QPoint(x * STONE_SIZE, y * STONE_SIZE), white);
            }
            else
            {
                painter.fillRect(x * STONE_SIZE, y * STONE_SIZE, STONE_SIZE - 1, STONE_SIZE - 1, QColor(221, 163, 68));
            }
        }
    }

    ui->boardLabel->setPixmap(canvas);
}

int MainWindow::check(int i, int j, int step_i, int step_j, int* marker_i, int* marker_j)
{
    *marker_i = i;
    *marker_j = j;

    if(i-step_i < 0 || i+step_i > LENGTH)
        return 0;

    if(j-step_j < 0 || j+step_j > LENGTH)
            return 0;

    if(blocks[i][j] == blocks[i + step_i][j + step_j])
    {
        return 1 + check(i + step_i, j + step_j, step_i, step_j, marker_i, marker_j);
    }
    return 0;
}


void MainWindow::make_move(int i, int j)
{
    if(blocks[i][j] != NA) // cannot reclaim claimed field
        return;

    if(turn == NA)
        return;

    blocks[i][j] = turn;

    set_board();

    // check if the player has five in a row
    int i1;
    int j1;
    int i2;
    int j2;
    if(check(i, j, -1, 0, &i1, &j1) + check(i, j, 1, 0, &i2, &j2) == 4
        || check(i, j, 0, -1, &i1, &j1) + check(i, j, 0, 1, &i2, &j2) == 4

        || check(i, j, -1, 1, &i1, &j1) + check(i, j, 1, -1, &i2, &j2) == 4

        || check(i, j, -1, -1, &i1, &j1) + check(i, j, 1, 1, &i2, &j2) == 4)
    {
        // connect the row with a line
        QPainter p(&canvas);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(QPen(Qt::gray, 5));
        p.drawLine(STONE_SIZE * i1 + STONE_SIZE/2, STONE_SIZE * j1 + STONE_SIZE/2,
                STONE_SIZE * i2 + STONE_SIZE/2, STONE_SIZE * j2 + STONE_SIZE/2);
        //TODO do this with one line only
        p.drawLine(STONE_SIZE * i1 + STONE_SIZE/2, STONE_SIZE * j1 + STONE_SIZE/2,
                        STONE_SIZE * i + STONE_SIZE/2, STONE_SIZE * j + STONE_SIZE/2);
        ui->boardLabel->setPixmap(canvas);

        winner = turn;
        turn = NA;
//        showWinner();
        return;
    }

    // if all the fields are full, it's a tie
    blockRemain--;
    if(blockRemain <= 0)
    {
        turn = NA;
        winner = 0;
//        showWinner();
        return;
    }

    // swap player
    if(turn == BLACK)
    {
        ui->statusLabel->setText("White");
        turn = WHITE;
    }
    else
    {
        ui->statusLabel->setText("BLACK");
        turn = BLACK;
    }
}


void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap image(":/new/prefix1/circle_");

    QPoint p1(10, 10);

    QPen pointpen(Qt::blue);
        pointpen.setWidth(6);
        painter.setPen(pointpen);
    painter.drawPoint(p1);
    painter.drawPixmap(p1, image);


}

