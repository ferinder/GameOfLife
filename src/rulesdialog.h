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

class RulesDialog : public QDialog
{
Q_OBJECT

public:
explicit RulesDialog(QWidget *parent = 0);
~RulesDialog();
std::string GetRule();

private slots:
void on_btn_add_clicked();

void on_btn_delete_clicked();

private:
Ui::RulesDialog *ui;
void populateList(QListWidget *view);
};

#endif // RULESDIALOG_H
