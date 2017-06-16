#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>

#define STATUS_BLACK "Black"
#define STATUS_WHITE "White"


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow),
canvas(BOARD_LENGTH * STONE_SIZE - 1, BOARD_LENGTH * STONE_SIZE - 1),

field_blk(IMAGE_WHITE),
field_wht(IMAGE_BLACK)
{
    ui->setupUi(this);
    
    
    ui->fieldLabel->installEventFilter(this);
    
    initialize();
}

void MainWindow::initialize()
{
    for(int x=0; x < BOARD_LENGTH; x++)
        for(int y=0; y < BOARD_LENGTH; y++)
            this->fields[x][y] = NO_PLAYER;
    
    turn = BLACK;
    ui->statusLabel->setText(STATUS_BLACK);
    remainingFields = BOARD_LENGTH * BOARD_LENGTH;
    
    ui->fieldLabel->setFixedSize(BOARD_LENGTH * STONE_SIZE, BOARD_LENGTH * STONE_SIZE);
    
    make_a_move();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    initialize();
}

bool MainWindow::eventFilter(QObject* object, QEvent* e)
{
    if(object != ui->fieldLabel || e->type() != QEvent::MouseButtonPress)
        return false;
    
    const QMouseEvent* event = static_cast<const QMouseEvent*>(e);
    
    int x = event->x() / STONE_SIZE;
    int y = event->y() / STONE_SIZE;
    
    this->fieldClicked(x, y);
    
    return false;
}

void MainWindow::make_a_move()
{
    QPainter painter(&canvas);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::NoPen);
    
    // background
    painter.fillRect(0, 0, canvas.width(), canvas.height(), QColor(221, 163, 68));
    
    
    // fields
    painter.setPen(Qt::black);
    for(int x = 0; x < BOARD_LENGTH; x++)
    {
        for(int y = 0; y < BOARD_LENGTH; y++)
        {
            painter.drawRect(x * STONE_SIZE - 1, y * STONE_SIZE - 1, STONE_SIZE, STONE_SIZE);
            
            if(fields[x][y] == BLACK)
            {
                painter.drawImage(QPoint(x * STONE_SIZE, y * STONE_SIZE), field_wht);
            }
            else if(fields[x][y] == WHITE)
            {
                painter.drawImage(QPoint(x * STONE_SIZE, y * STONE_SIZE), field_blk);
            }
            else
            {
                painter.fillRect(x * STONE_SIZE, y * STONE_SIZE, STONE_SIZE - 1, STONE_SIZE - 1, QColor(221, 163, 68));
            }
        }
    }
    
    ui->fieldLabel->setPixmap(canvas);
}

int MainWindow::check(int x, int y, int step_x, int step_y, int* marker_x, int* marker_y)
{
    *marker_x = x;
    *marker_y = y;
    
    if(x-step_x < 0 || x+step_x > BOARD_LENGTH)
        return 0;
    
    if(y-step_y < 0 || y+step_y > BOARD_LENGTH)
        return 0;
    
    if(fields[x][y] == fields[x + step_x][y + step_y])
    {
        return 1 + check(x + step_x, y + step_y, step_x, step_y, marker_x, marker_y);
    }
    return 0;
}

void MainWindow::fieldClicked(int x, int y)
{
    if(fields[x][y] > NO_PLAYER) // cannot reclaim claimed field
        return;
    
    if(turn == NO_PLAYER)
        return;
    
    fields[x][y] = turn;
    
    make_a_move();
    
    // check if the player has five in a row
    int x1;
    int y1;
    int x2;
    int y2;
    if(check(x, y, -1, 0, &x1, &y1) + check(x, y, 1, 0, &x2, &y2) == 4
       || check(x, y, 0, -1, &x1, &y1) + check(x, y, 0, 1, &x2, &y2) == 4
       
       || check(x, y, -1, 1, &x1, &y1) + check(x, y, 1, -1, &x2, &y2) == 4
       
       || check(x, y, -1, -1, &x1, &y1) + check(x, y, 1, 1, &x2, &y2) == 4)
    {
        // connect the row with a line
        QPainter p(&canvas);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(QPen(Qt::gray, 5));
        p.drawLine(STONE_SIZE * x1 + STONE_SIZE/2, STONE_SIZE * y1 + STONE_SIZE/2,
                   STONE_SIZE * x2 + STONE_SIZE/2, STONE_SIZE * y2 + STONE_SIZE/2);
        //TODO do this with one line only
        p.drawLine(STONE_SIZE * x1 + STONE_SIZE/2, STONE_SIZE * y1 + STONE_SIZE/2,
                   STONE_SIZE * x + STONE_SIZE/2, STONE_SIZE * y + STONE_SIZE/2);
        ui->fieldLabel->setPixmap(canvas);
        
        winner = turn;
        turn = NO_PLAYER;
        showResult();
        return;
    }
    
    // if all the fields are full, it's a tie
    remainingFields--;
    if(remainingFields <= 0)
    {
        turn = NO_PLAYER;
        winner = 0;
        showResult();
        return;
    }
    
    // swap turn
    if(turn == BLACK)
    {
        ui->statusLabel->setText(STATUS_WHITE);
        turn = WHITE;
    }
    else
    {
        ui->statusLabel->setText(STATUS_BLACK);
        turn = BLACK;
    }
}

void MainWindow::showResult()
{
    QMessageBox msgbox;
    QString text;
    if(winner == 0)
        text = "It's a tie!";
    else if(winner == BLACK)
        text = "Black wins!";
    else if(winner == WHITE)
        text = "White wins!";
    else
        text = "Unknown error. Could not showResult winner";
    
    ui->statusLabel->setText(text);
    msgbox.setWindowTitle("Game Over");
    msgbox.setText(text);
    msgbox.exec();
}


void MainWindow::saveScreenshot()
{
    QFileDialog fd(this);
    fd.setNameFilter("PNG Image (*.png);;All Files (*)");
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setConfirmOverwrite(true);
    if(!fd.exec())
        return;
    
    QMessageBox cmsgbox;
    if(canvas.save(fd.selectedFiles().first(), "png", 0))
        cmsgbox.setText("Screenshot saved!");
    else
        cmsgbox.setText("Failed to save screenshot!");
    cmsgbox.exec();
}

void MainWindow::showAboutDialog()
{
    QMessageBox msgbox;
    msgbox.setTextFormat(Qt::RichText);
    msgbox.setText("About Gomoku");
    msgbox.setMaximumSize(400, 600);
    msgbox.setStandardButtons(QMessageBox::Ok);
    msgbox.exec();
}
