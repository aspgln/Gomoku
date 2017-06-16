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



//void MainWindow::set_board(){
//    QPainter painter(&canvas);

//    //set background
//    QRect boardBackground(0,0, canvas.width(), canvas.height());
//    painter.fillRect(boardBackground, QColor(221, 163, 68));
//}

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


//    QPainter painter(this);

//    //create point of each intersection
//    //need to be integrated into a vector or other container

//    int n = 3;

//    //create a vector that contains all the points at intersections
//    QVector<QPoint> pointVector;

//    // IMPROVEMENT!!!
//    //could use iterator
//    for (int i = 0; i != n+1; i++){
//        for (int j  = 0; j != n+1; j++){

//            pointVector.append(QPoint(j*100, i*100));
//        }
//    }

//    //create a vector that contains all the rectangles on the board
//    QVector<QRect> rectVector;

//    // IMPROVEMENT!!!
//    // create a vector contains all the units on the board with QRect
//    //could use iterator
//    for (int i = 0; i != n; i++){
//        for (int j  = 0; j != n; j++){
//            rectVector.append(QRect(pointVector[n*i + j],
//                                     pointVector[(n+1)*(i+1) + (j)] ) );
//        }
//    }

//    //brush
//    QBrush brush(Qt::green, Qt::SolidPattern);
//    for (int i = 0; i != n*n; i++){

//        painter.fillRect(rectVector[i], brush);
////        painter.drawText(rectVector[i], Qt::AlignCenter, "X");
//    }


//    painter.drawText(rectVector[3], Qt::AlignCenter, "QWER");

////    for (int i = 0; i <n*n; i++){
////        painter.drawText(rectVector[i], Qt::AlignCenter, "QWER");
////    }

//    //framepen
//    QPen framepen(Qt::red);
//    framepen.setWidth(6);
//    painter.setPen(framepen);
//    for (int i = 0; i != n*n; i++){
//            painter.drawRect(rectVector[i]);
//    }

//    //pointpen
//    QPen pointpen(Qt::blue);
//    pointpen.setWidth(6);
//    painter.setPen(pointpen);
//    for (int i = 0; i != (n+1)*(n+1); i++){
//            painter.drawPoint(pointVector[i]);
//    }




}

