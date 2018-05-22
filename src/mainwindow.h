#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QFileDialog>
#include "game.h"
#include "newboarddialog.h"
#include "rulesdialog.h"
#include "propertiesdialog.h"

namespace Ui {
class MainWindow;
}
/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
/*!
 * \brief MainWindow constructor.
 * \param parent - pointer to parent object.
 */
explicit MainWindow(QWidget *parent = 0);
~MainWindow();

private slots:
void on_actionExit_triggered();
void on_actionNewBoard_triggered();
void on_actionRun_triggered();
void runSimulation();
void on_actionLoadBoard_triggered();
void on_actionSaveBoard_triggered();
void on_actionSetting_triggered();
void on_actionChooseRule_triggered();

private:
void paintEvent(QPaintEvent *);
void mouseReleaseEvent(QMouseEvent *ev);
void setSimulationInterval(int interval);

Ui::MainWindow *ui;
QTimer *timer = nullptr;

Game game;
static const int cellSize = 5;
};

#endif // MAINWINDOW_H
