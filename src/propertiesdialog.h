#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "gamesettings.h"

namespace Ui {
class PropertiesDialog;
}
/*!
 * \brief The PropertiesDialog class
 */
class PropertiesDialog : public QDialog
{
Q_OBJECT

public:
/*!
 * \brief PropertiesDialog constructor.
 * \param parent - pointer to parent object.
 */
explicit PropertiesDialog(QWidget *parent = 0);
~PropertiesDialog();
/*!
 * \brief Get simulation time from dialog.
 * \return simulation time from properties dialog.
 */
int GetSimulationTime();

bool GetBoardWrapingSetting();

private:
Ui::PropertiesDialog *ui;
};

#endif // PROPERTIESDIALOG_H
