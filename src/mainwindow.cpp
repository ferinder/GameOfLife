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
        ui->actionSaveBoard->setEnabled(true);
        this->resize(game.GetBoardSizeX() * (cellSize + 1) + 10,
                     game.GetBoardSizeY() * (cellSize + 1) +
                     ui->centralWidget->geometry().y() + 10);
        game.ToggleCellState(2, 2);
        game.ToggleCellState(2, 3);
        game.ToggleCellState(2, 4);
        repaint();
    }
}

void MainWindow::on_actionRun_triggered()
{
    if(!game.IsContinouse()) {
        ui->actionRun->setIcon(QIcon(":/icons/src/icons/stop.png"));
        timer->start();
    }
    else{
        ui->actionRun->setIcon(QIcon(":/icons/src/icons/play.png"));
        timer->stop();
    }
    game.ToggleContinouse();
}

void MainWindow::runSimulation()
{
    game.RunSimulation(1);
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
            game.ToggleCellState(cellX, cellY);
            repaint();
        }
    }
    qDebug() << "Mouse position: X Y: " << posX << ' ' << posY
             << "\nCell: " << cellX << ' ' << cellY;

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
}

void MainWindow::on_actionSaveBoard_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save board"));
    this->game.SaveBoard(filePath.toStdString());
}

void MainWindow::on_actionChoose_rule_triggered()
{
    GetRuleDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        this->game.SetRule(dlg.GetRuleFromDialog());
    }
}

void MainWindow::on_actionWybierz_regu_triggered()
{
    RulesDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        if(dlg.GetRule() == "") return;
        this->game.SetRule(dlg.GetRule());
    }
}
