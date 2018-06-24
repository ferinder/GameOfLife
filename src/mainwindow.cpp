#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionSaveBoard->setDisabled(true);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(runSimulation()));
    timer->setInterval(500);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
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
        game.NewBoard(dlg.GetSizeX(),dlg.GetSizeY());
        game.SetColorRule(dlg.GetColorRule());
        ui->actionSaveBoard->setEnabled(true);
        if(dlg.GetColorRule() != ColorRule::Default)
        {
            ui->actionChooseRule->setEnabled(false);
            game.SetRule("23/3");
            game.ToggleCellState(2, 2);
            game.SetCellColor(2, 2, Qt::red);
            game.ToggleCellState(2, 3);
            game.SetCellColor(2, 3, Qt::red);
            game.ToggleCellState(2, 4);
            game.SetCellColor(2, 4, Qt::red);
        }
        else
        {
            ui->actionChooseRule->setEnabled(true);
            game.ToggleCellState(2, 2);
            game.SetCellColor(2, 2, Qt::black);
            game.ToggleCellState(2, 3);
            game.SetCellColor(2, 3, Qt::black);
            game.ToggleCellState(2, 4);
            game.SetCellColor(2, 4, Qt::black);
        }
        this->resize(game.GetBoardSizeX() * (cellSize + 1) + 10,
                     game.GetBoardSizeY() * (cellSize + 1) +
                     ui->centralWidget->geometry().y() + 10);
        repaint();
    }
}

void MainWindow::on_actionRun_triggered()
{
    if(!game.IsSet()) return;
    if(!timer->isActive()) {
        ui->actionRun->setIcon(QIcon(":/icons/src/icons/stop.png"));
        timer->start();
    }
    else{
        ui->actionRun->setIcon(QIcon(":/icons/src/icons/play.png"));
        timer->stop();
    }
}

void MainWindow::runSimulation()
{
    game.RunSimulation();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!game.IsSet()) return;
    QPainter myPainter(this);
    int windowCoordinateY = 0;
    int widgetCoordinateStartY = ui->centralWidget->geometry().y() + 5;
    int windowCoordinateX = ui->centralWidget->geometry().x() + 5;
    for(int x = 0; x < game.GetBoardSizeX(); x++)
    {
        windowCoordinateY = widgetCoordinateStartY;
        for( int y = 0; y < game.GetBoardSizeY(); y++)
        {
            myPainter.fillRect(windowCoordinateX, windowCoordinateY,
                               cellSize, cellSize, game.GetCellColor(x,y));
            windowCoordinateY += cellSize + 1;
        }
        windowCoordinateX += cellSize + 1;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    int posX = ev->x() - ui->centralWidget->geometry().x() - 5;
    int posY = ev->y() - ui->centralWidget->geometry().y() - 5;
    int cellX = posX/(cellSize + 1);
    int cellY = posY/(cellSize + 1);
    if(posX%(cellSize + 1) != 5 && posY%(cellSize + 1) != 5)
    {
        if(game.IsSet())
        {
            switch (game.GetColorRule()) {
            case ColorRule::Default:
                if(game.IsCellAlive(cellX, cellY))
                    game.SetCellColor(cellX, cellY, Qt::white);
                else
                    game.SetCellColor(cellX, cellY, Qt::black);
                game.ToggleCellState(cellX, cellY);
                break;
            case ColorRule::Immigration:
                if(!game.IsCellAlive(cellX, cellY))
                {
                    game.ToggleCellState(cellX, cellY);
                    game.SetCellColor(cellX, cellY, Qt::red);
                }
                else
                {
                    if(game.GetCellColor(cellX, cellY) == Qt::red)
                    {
                        game.SetCellColor(cellX,cellY, Qt::blue);
                    }
                    else
                    {
                        game.SetCellColor(cellX, cellY, Qt::white);
                        game.ToggleCellState(cellX, cellY);
                    }
                }
                break;
            case ColorRule::QuadLife:
                if(!game.IsCellAlive(cellX, cellY))
                {
                    game.ToggleCellState(cellX, cellY);
                    game.SetCellColor(cellX, cellY, Qt::red);
                }
                else
                {
                    QColor cellColor = game.GetCellColor(cellX, cellY);
                    if(cellColor == Qt::red)
                        game.SetCellColor(cellX, cellY, Qt::blue);
                    else if(cellColor == Qt::blue)
                        game.SetCellColor(cellX, cellY, Qt::green);
                    else if(cellColor == Qt::green)
                        game.SetCellColor(cellX, cellY, Qt::magenta);
                    else
                    {
                        game.ToggleCellState(cellX, cellY);
                        game.SetCellColor(cellX, cellY, Qt::white);
                    }
                }
                break;
            default:
                break;
            }
            repaint();
        }
    }
    qDebug() << "Mouse position: X Y: " << posX << ' ' << posY
             << "\nCell: " << cellX << ' ' << cellY;

}

void MainWindow::setSimulationInterval(int interval)
{
    timer->setInterval(interval);
}


void MainWindow::on_actionLoadBoard_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open board"));
    if(!this->game.LoadBoard(filePath.toStdString())) return;
    this->resize(game.GetBoardSizeX() * (cellSize + 1) + 10,
                 game.GetBoardSizeY() * (cellSize + 1) +
                 ui->centralWidget->geometry().y() + 10);
    repaint();
    ui->actionSaveBoard->setEnabled(true);
    if(game.GetColorRule()!=ColorRule::Default)
        ui->actionChooseRule->setEnabled(false);
    else
        ui->actionChooseRule->setEnabled(true);
}

void MainWindow::on_actionSaveBoard_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save board"));
    this->game.SaveBoard(filePath.toStdString());
}

void MainWindow::on_actionSetting_triggered()
{
    PropertiesDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        setSimulationInterval(dlg.GetSimulationTime());
    }
}

void MainWindow::on_actionChooseRule_triggered()
{
    RulesDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(dlg.GetRule() == "") return;
        this->game.SetRule(dlg.GetRule());
    }
}
