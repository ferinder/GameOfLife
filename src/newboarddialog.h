#ifndef NEWBOARDDIALOG_H
#define NEWBOARDDIALOG_H

#include <QDialog>
#include "colorruleenum.h"
#include <string>

namespace Ui {
class NewBoardDialog;
}
/*!
 * \brief The NewBoardDialog class
 */
class NewBoardDialog : public QDialog
{
Q_OBJECT

public:
/*!
 * \brief NewBoardDialog constructor.
 * \param parent - pointer to parent object.
 */
explicit NewBoardDialog(QWidget *parent = 0);
~NewBoardDialog();
/*!
 * \brief Get board size x from dialog.
 * \return board size x from dialog.
 */
int GetSizeX();
/*!
 * \brief Get board size y from dialog.
 * \return board size y from dialog.
 */
int GetSizeY();

/*!
 * \brief Get choosen color rule from user input.
 * \return game color rule from ColorRule enum.
 */
int GetColorRule();

private:
Ui::NewBoardDialog *ui;
};

#endif // NEWBOARDDIALOG_H
