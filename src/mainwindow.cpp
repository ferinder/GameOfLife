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
        game.NewBoard(dlg.GetSizeXFromDialog(), dlg.GetSizeYFromDialog());
        ui->actionSaveBoard->setEnabled(true);
    }
}

void MainWindow::on_actionRun_triggered()
{
    game.ToggleSimulation();
    if(game.IsContinouse()) ui->actionRun->setIcon(QIcon(":/icons/src/icons/stop.png"));
    else ui->actionRun->setIcon(QIcon(":/icons/src/icons/play.png"));

}
