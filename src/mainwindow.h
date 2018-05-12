#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include "game.h"
#include "newboarddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = 0);
~MainWindow();

private slots:
void on_actionExit_triggered();

void on_actionNewBoard_triggered();

void on_actionRun_triggered();
void runSimulation();

private:
void paintEvent(QPaintEvent *);

Ui::MainWindow *ui;
QTimer *timer = nullptr;

Game game;
int cellSize = 5;
};

#endif // MAINWINDOW_H
