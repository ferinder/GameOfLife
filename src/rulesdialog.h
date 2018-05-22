#ifndef RULESDIALOG_H
#define RULESDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include "getruledialog.h"


namespace Ui {
class RulesDialog;
}
/*!
 * \brief The RulesDialog class
 */
class RulesDialog : public QDialog
{
Q_OBJECT

public:
/*!
 * \brief RulesDialog constructor.
 * \param parent - pointer to parent object.
 */
explicit RulesDialog(QWidget *parent = 0);
~RulesDialog();
/*!
 * \brief Get rule from dialog list.
 * \return selected rule from list.
 */
std::string GetRule();

private slots:
void on_btn_add_clicked();
void on_btn_delete_clicked();

private:
Ui::RulesDialog *ui;
void populateList(QListWidget *view);
};

#endif // RULESDIALOG_H
