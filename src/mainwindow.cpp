#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionSaveBoard->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNewBoard_triggered()
{
    NewBoardDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        game.NewBoard(dlg.GetSizeX(), dlg.GetSizeY());
        ui->actionSaveBoard->setEnabled(true);
        this->resize(game.GetBoardSizeX() * (cellSize + 1) + 10,
                     game.GetBoardSizeY() * (cellSize + 1) + 65);
        repaint();
        game.ToggleCellState(2, 2);
        repaint();
        game.ToggleCellState(2, 3);
        repaint();
        game.ToggleCellState(2, 4);
        repaint();
    }
}

void MainWindow::on_actionRun_triggered()
{
    game.RunSimulation(1);
//    game.ToggleContinouse();
//    if(game.IsContinouse()) ui->actionRun->setIcon(QIcon(":/icons/src/icons/stop.png"));
//    else ui->actionRun->setIcon(QIcon(":/icons/src/icons/play.png"));
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!game.IsSet()) return;
    QPainter myPainter(this);
    int windowCoordinateY = 60;
    int windowCoordinateX = 5;
    for(int x = 0; x < game.GetBoardSizeX(); x++)
    {
        windowCoordinateY = 60;
        for( int y = 0; y < game.GetBoardSizeY(); y++)
        {
            if(game.IsCellAlive(x, y))
            {
                myPainter.fillRect(windowCoordinateX, windowCoordinateY,
                                   cellSize, cellSize, Qt::black);
            }
            else
            {
                myPainter.fillRect(windowCoordinateX, windowCoordinateY,
                                   cellSize, cellSize, Qt::white);
            }
            windowCoordinateY += cellSize + 1;
        }
        windowCoordinateX += cellSize + 1;
    }
}
