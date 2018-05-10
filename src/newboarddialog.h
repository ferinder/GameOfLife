#ifndef NEWBOARDDIALOG_H
#define NEWBOARDDIALOG_H

#include <QDialog>

namespace Ui {
class NewBoardDialog;
}

class NewBoardDialog : public QDialog
{
Q_OBJECT

public:
explicit NewBoardDialog(QWidget *parent = 0);
~NewBoardDialog();
int GetSizeXFromDialog();
int GetSizeYFromDialog();

private:
Ui::NewBoardDialog *ui;
};

#endif // NEWBOARDDIALOG_H