#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
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

private:
void paintEvent(QPaintEvent *);

Ui::MainWindow *ui;
Game game;
int cellSize = 5;
};

#endif // MAINWINDOW_H
