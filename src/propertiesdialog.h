#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog
{
Q_OBJECT

public:
explicit PropertiesDialog(QWidget *parent = 0);
~PropertiesDialog();
int GetSimulationTime();

private:
Ui::PropertiesDialog *ui;
};

#endif // PROPERTIESDIALOG_H
