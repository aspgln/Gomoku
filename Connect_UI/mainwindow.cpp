#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //create point of each intersection
    //need to be integrated into a vector or other container

    int n = 10;

    //create a vector that contains all the points at intersections
    QVector<QPoint> pointVector;

    // IMPROVEMENT!!!
    //could use iterator
    for (int i = 0; i != n+1; i++){
        for (int j  = 0; j != n+1; j++){

            pointVector.append(QPoint(j*100, i*100));
        }
    }

    //create a vector that contains all the rectangles on the board
    QVector<QRect> rectVector;

    // IMPROVEMENT!!!
    // create a vector contains all the units on the board with QRect
    //could use iterator
    for (int i = 0; i != n; i++){
        for (int j  = 0; j != n; j++){
            rectVector.append(QRect(pointVector[n*i + j],
                                     pointVector[(n+1)*(i+1) + (j)] ) );
        }
    }


    QBrush brush(Qt::green, Qt::SolidPattern);
    for (int i = 0; i != n*n; i++){
        painter.fillRect(rectVector[i], brush);
    }



    QPen framepen(Qt::red);
    framepen.setWidth(6);
    painter.setPen(framepen);
    for (int i = 0; i != n*n; i++){
            painter.drawRect(rectVector[i]);
    }

    QPen pointpen(Qt::blue);
    pointpen.setWidth(6);
    painter.setPen(pointpen);
    for (int i = 0; i != (n+1)*(n+1); i++){
            painter.drawPoint(pointVector[i]);
    }


}
