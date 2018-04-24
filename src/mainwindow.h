#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
Ui::MainWindow *ui;
Game game;
};

#endif // MAINWINDOW_H
